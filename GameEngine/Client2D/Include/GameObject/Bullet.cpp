#include "Bullet.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderSphere2D.h"

CBullet::CBullet()
{
	SetTypeID<CBullet>();

	m_ObjectTypeName = "Bullet";
}

CBullet::CBullet(const CBullet& Obj)	:
	CGameObject(Obj)
{
	m_Body = (CColliderSphere2D*)FindComponent("Body");
	m_Bullet = (CSpriteComponent*)FindComponent("Bullet");

	m_MoveSpeed = Obj.m_MoveSpeed;
	m_Distance = Obj.m_Distance;
}

CBullet::~CBullet()
{
}

void CBullet::SetCollisionProfileName(const std::string& Name)
{
	m_Body->SetCollisionProfile(Name);
}

void CBullet::Start()
{
	CGameObject::Start();
}

bool CBullet::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderSphere2D>("Body");
	m_Body->SetCollisionCallback<CBullet>(ECollision_Result::Collision, this, &CBullet::CollisionBullet);

	m_Bullet = CreateComponent<CSpriteComponent>("Bullet");


	m_Body->AddChild(m_Bullet);
	m_Body->SetRadius(15.f);

	m_Bullet->SetRelativeScale(30.f, 30.f);

	m_MoveSpeed = 300.f;
	m_Distance = 1000.f;

	return true;
}

void CBullet::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	AddWorldPosition(GetWorldAxis(AXIS_Y) * m_MoveSpeed * DeltaTime);

	m_Distance -= m_MoveSpeed * g_DeltaTime;

	if (m_Distance <= 0.f)
	{
		Destroy();
	}
}

void CBullet::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBullet* CBullet::Clone() const
{
	return new CBullet(*this);
}

void CBullet::CollisionBullet(const CollisionResult& result)
{
	Destroy();
}
