#include "BelialBullet.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderSphere2D.h"
#include "../Animation2D/BelialBulletAnimation.h"
#include "Scene/Scene.h"
#include "Character.h"

CBelialBullet::CBelialBullet()	:
	m_Move(true)
{
	SetTypeID<CBelialBullet>();

	m_ObjectTypeName = "BelialBullet";
}

CBelialBullet::CBelialBullet(const CBelialBullet& Obj) :
	CGameObject(Obj)
{
	m_Body = (CColliderSphere2D*)FindComponent("Body");
	m_Bullet = (CSpriteComponent*)FindComponent("Bullet");

	m_Move = Obj.m_Move;
}

CBelialBullet::~CBelialBullet()
{
}

void CBelialBullet::SetBulletInfo(const Vector2& Position, float Angle)
{
	m_Body->SetWorldPosition(Position);
	m_Body->SetWorldRotationZ(Angle);

	m_InitPosition = Position;
}

void CBelialBullet::Start()
{
	CGameObject::Start();

	m_Body->SetCollisionCallback<CBelialBullet>(ECollision_Result::Collision, this, &CBelialBullet::AttackCollision);
}

bool CBelialBullet::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderSphere2D>("Body");
	m_Body->SetCollisionProfile("MonsterAttack");
	m_Body->SetInheritScale(true);

	m_Bullet = CreateComponent<CSpriteComponent>("Bullet");
	m_Bullet->SetAnimation<CBelialBulletAnimation>("BelialBulletAnimation");
	m_Bullet->SetWorldScale(50.f, 50.f);
	m_Bullet->SetRenderLayerName("Effect");
	m_Bullet->SetPivot(0.5f, 0.5f);

	m_Body->SetRadius(m_Bullet->GetWorldScale().x / 3.f);

	m_Body->AddChild(m_Bullet);


	return true;
}

void CBelialBullet::Update(float DeltaTime)
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

void CBelialBullet::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBelialBullet* CBelialBullet::Clone() const
{
	return new CBelialBullet(*this);
}

void CBelialBullet::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CBelialBullet::Load(FILE* File)
{
	CGameObject::Load(File);
}

void CBelialBullet::AttackCollision(const CollisionResult& Result)
{
	// 캐릭터에게 데미지를 준다.
	((CCharacter*)Result.Dest->GetOwner())->InflictDamage(2);

	m_Bullet->GetAnimation()->ChangeAnimation("Destroy");
	m_Move = false;
}