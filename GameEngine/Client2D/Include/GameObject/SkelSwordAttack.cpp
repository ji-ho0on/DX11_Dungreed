#include "SkelSwordAttack.h"
#include "Component/ColliderBox2D.h"
#include "Character.h"
#include "Scene/Scene.h"
#include "ArrowHitEffect.h"

CSkelSwordAttack::CSkelSwordAttack()
{
	SetTypeID<CSkelSwordAttack>();

	m_ObjectTypeName = "SkelSwordAttack";
}

CSkelSwordAttack::CSkelSwordAttack(const CSkelSwordAttack& Obj) :
	CGameObject(Obj)
{
	m_Body = (CColliderBox2D*)FindComponent("Body");
}

CSkelSwordAttack::~CSkelSwordAttack()
{
}

void CSkelSwordAttack::SetAttackInfo(const Vector2& Position)
{
	m_Body->SetWorldPosition(Position);
}

void CSkelSwordAttack::Start()
{
	CGameObject::Start();

	m_Body->SetCollisionCallback<CSkelSwordAttack>(ECollision_Result::Collision, this, &CSkelSwordAttack::AttackCollision);
}

bool CSkelSwordAttack::Init()
{
	CGameObject::Init();

	// 충돌용 Collider 생성
	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Body->SetCollisionProfile("MonsterAttack");

	m_Body->SetBoxSize(100.f, 150.f);
	m_Body->SetPivot(0.5f, 0.5f);

	return true;
}

void CSkelSwordAttack::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_AttackTime += DeltaTime;

	if (m_AttackTime >= 0.3f)
		Destroy();
}

void CSkelSwordAttack::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CSkelSwordAttack* CSkelSwordAttack::Clone() const
{
	return new CSkelSwordAttack(*this);
}

void CSkelSwordAttack::AttackCollision(const CollisionResult& Result)
{
	// 캐릭터에게 데미지를 준다.
	((CCharacter*)Result.Dest->GetOwner())->InflictDamage(10);

	Destroy();
}