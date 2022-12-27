#include "BatBullet.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderSphere2D.h"
#include "../Animation2D/BatBulletAnimation.h"
#include "Scene/Scene.h"
#include "Character.h"

CBatBullet::CBatBullet() :
	m_Move(true),
	m_MoveWaitTime(-1.f)
{
	SetTypeID<CBatBullet>();

	m_ObjectTypeName = "BatBullet";
}

CBatBullet::CBatBullet(const CBatBullet& Obj) :
	CGameObject(Obj)
{
	m_Body = (CColliderSphere2D*)FindComponent("Body");
	m_Bullet = (CSpriteComponent*)FindComponent("Bullet");

	m_Move = Obj.m_Move;
}

CBatBullet::~CBatBullet()
{
}

void CBatBullet::SetBulletInfo(const Vector2& Position, float Angle)
{
	m_Body->SetWorldPosition(Position);
	m_Body->SetWorldRotationZ(Angle);

	m_InitPosition = Position;
}

void CBatBullet::SetBulletScale(const Vector2& Scale)
{
	m_Bullet->SetWorldScale(Scale);
	m_Body->SetRadius(Scale.x / 3.f);
}

void CBatBullet::Start()
{
	CGameObject::Start();

	m_Body->SetCollisionCallback<CBatBullet>(ECollision_Result::Collision, this, &CBatBullet::AttackCollision);
}

bool CBatBullet::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderSphere2D>("Body");
	m_Body->SetCollisionProfile("MonsterAttack");
	m_Body->SetInheritScale(true);

	m_Bullet = CreateComponent<CSpriteComponent>("Bullet");
	m_Bullet->SetAnimation<CBatBulletAnimation>("BatBulletAnimation");
	m_Bullet->SetWorldScale(30.f, 30.f);
	m_Bullet->SetRenderLayerName("Effect");
	m_Bullet->SetPivot(0.5f, 0.5f);

	m_Body->SetRadius(m_Bullet->GetWorldScale().x / 3.f);

	m_Body->AddChild(m_Bullet);

	 
	return true;
}

void CBatBullet::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_MoveWaitTime > 0.f)
	{
		m_MoveWaitTime -= DeltaTime;

		if (m_MoveWaitTime <= 0.f)
		{
			m_Move = true;
		}
	}

	if (m_Move)
		m_Body->AddWorldPosition(GetWorldAxis(AXIS_X) * 300.f * DeltaTime);

	if (m_InitPosition.Distance(GetWorldPos()) >= 1000.f)
	{
		// 터지는 이펙트 생성
		m_Bullet->GetAnimation()->ChangeAnimation("Destroy");
		m_Move = false;
	}
}

void CBatBullet::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBatBullet* CBatBullet::Clone() const
{
	return new CBatBullet(*this);
}

void CBatBullet::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CBatBullet::Load(FILE* File)
{
	CGameObject::Load(File);
}

void CBatBullet::AttackCollision(const CollisionResult& Result)
{
	// 캐릭터에게 데미지를 준다.
	((CCharacter*)Result.Dest->GetOwner())->InflictDamage(2);

	m_Bullet->GetAnimation()->ChangeAnimation("Destroy");
	m_Move = false;
}