#include "ShortSwordEffect.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderOBB2D.h"
#include "../Animation2D/ShortSwordSwing.h"
#include "Creature.h"

CShortSwordEffect::CShortSwordEffect()
{
	SetTypeID<CShortSwordEffect>();

	m_ObjectTypeName = "ShortSwordEffect";
}

CShortSwordEffect::CShortSwordEffect(const CShortSwordEffect& Obj) :
	CGameObject(Obj)
{
	m_EffectBody = (CColliderOBB2D*)FindComponent("EffectBody");
	m_Effect = (CSpriteComponent*)FindComponent("Effect");
}

CShortSwordEffect::~CShortSwordEffect()
{
}

void CShortSwordEffect::SetEffectInfo(const Vector2& Position, float RotationZ)
{
	m_EffectBody->SetWorldRotationZ(RotationZ);
	m_EffectBody->SetWorldPosition(Position);
}

void CShortSwordEffect::Start()
{
	CGameObject::Start();

	m_EffectBody->SetCollisionCallback<CShortSwordEffect>(ECollision_Result::Collision, this, &CShortSwordEffect::EffectCollision);
}

bool CShortSwordEffect::Init()
{
	CGameObject::Init();

	// 충돌용 Collider 생성
	m_EffectBody = CreateComponent<CColliderOBB2D>("EffectBody");
	m_EffectBody->SetCollisionProfile("PlayerAttack");

	// Effect 생성
	m_Effect = CreateComponent<CSpriteComponent>("Effect");
	m_Effect->SetAnimation<CShortSwordSwing>("ShortSwordSwing");
	m_Effect->SetRenderLayerName("Weapon");

	m_EffectBody->AddChild(m_Effect);

	m_Effect->SetInheritScale(false);
	m_Effect->SetInheritRotZ(true);

	m_Effect->SetWorldScale(150.f, 200.f);
	m_Effect->SetPivot(0.f, 0.5f);

	m_EffectBody->SetBoxHalfSize(m_Effect->GetWorldScale().x / 2.f, m_Effect->GetWorldScale().y / 2.f);
	m_EffectBody->SetPivot(0.f, 0.5f);

	return true;
}

void CShortSwordEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CShortSwordEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CShortSwordEffect* CShortSwordEffect::Clone() const
{
	return new CShortSwordEffect(*this);
}

void CShortSwordEffect::EffectCollision(const CollisionResult& Result)
{
	// 몬스터에게 데미지를 준다.
	((CCreature*)Result.Dest->GetOwner())->InflictDamage(10);
}
