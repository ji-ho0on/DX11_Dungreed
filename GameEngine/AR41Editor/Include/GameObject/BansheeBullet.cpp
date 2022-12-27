#include "BansheeBullet.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderSphere2D.h"
#include "../Animation2D/BansheeBulletAnimation.h"
#include "Scene/Scene.h"
#include "Character.h"

CBansheeBullet::CBansheeBullet() :
	m_Move(true)
{
	SetTypeID<CBansheeBullet>();

	m_ObjectTypeName = "BansheeBullet";
}

CBansheeBullet::CBansheeBullet(const CBansheeBullet& Obj) :
	CGameObject(Obj)
{
	m_Body = (CColliderSphere2D*)FindComponent("Body");
	m_Bullet = (CSpriteComponent*)FindComponent("Bullet");

	m_Move = Obj.m_Move;
}

CBansheeBullet::~CBansheeBullet()
{
}

void CBansheeBullet::SetBulletInfo(const Vector2& Position, float Angle)
{
	m_Body->SetWorldPosition(Position);
	m_Body->SetWorldRotationZ(Angle);

	m_InitPosition = Position;
}

void CBansheeBullet::Start()
{
	CGameObject::Start();

	m_Body->SetCollisionCallback<CBansheeBullet>(ECollision_Result::Collision, this, &CBansheeBullet::AttackCollision);
}

bool CBansheeBullet::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderSphere2D>("Body");
	m_Body->SetCollisionProfile("MonsterAttack");
	m_Body->SetInheritScale(true);

	m_Bullet = CreateComponent<CSpriteComponent>("Bullet");
	m_Bullet->SetAnimation<CBansheeBulletAnimation>("BansheeBulletAnimation");
	m_Bullet->SetWorldScale(40.f, 50.f);
	m_Bullet->SetRenderLayerName("Effect");
	m_Bullet->SetPivot(0.5f, 0.5f);

	m_Body->SetRadius(m_Bullet->GetWorldScale().x / 3.f);

	m_Body->AddChild(m_Bullet);


	return true;
}

void CBansheeBullet::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_Move)
		m_Body->AddWorldPosition(GetWorldAxis(AXIS_X) * 200.f * DeltaTime);

	if (m_InitPosition.Distance(GetWorldPos()) >= 1000.f)
	{
		// 터지는 이펙트 생성
		m_Bullet->GetAnimation()->ChangeAnimation("Destroy");
		m_Move = false;
	}
}

void CBansheeBullet::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBansheeBullet* CBansheeBullet::Clone() const
{
	return new CBansheeBullet(*this);
}

void CBansheeBullet::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CBansheeBullet::Load(FILE* File)
{
	CGameObject::Load(File);
}

void CBansheeBullet::AttackCollision(const CollisionResult& Result)
{
	// 캐릭터에게 데미지를 준다.
	((CCharacter*)Result.Dest->GetOwner())->InflictDamage(2);

	m_Bullet->GetAnimation()->ChangeAnimation("Destroy");
	m_Move = false;
}