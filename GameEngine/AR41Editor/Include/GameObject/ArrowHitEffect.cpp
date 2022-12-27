#include "ArrowHitEffect.h"
#include "Component/SpriteComponent.h"
#include "../Animation2D/ArrowHitAnimation.h"
#include "Monster.h"

CArrowHitEffect::CArrowHitEffect()
{
	SetTypeID<CArrowHitEffect>();

	m_ObjectTypeName = "ArrowHitEffect";
}

CArrowHitEffect::CArrowHitEffect(const CArrowHitEffect& Obj) :
	CGameObject(Obj)
{
	m_Effect = (CSpriteComponent*)FindComponent("Effect");
}

CArrowHitEffect::~CArrowHitEffect()
{
}

void CArrowHitEffect::SetEffectInfo(const Vector2& Position, float RotationZ)
{
	m_Effect->SetWorldRotationZ(RotationZ);
	m_Effect->SetWorldPosition(Position);
}

void CArrowHitEffect::Start()
{
	CGameObject::Start();
}

bool CArrowHitEffect::Init()
{
	CGameObject::Init();

	// Effect »ý¼º
	m_Effect = CreateComponent<CSpriteComponent>("Effect");
	m_Effect->SetAnimation<CArrowHitAnimation>("ArrowHitAnimation");
	m_Effect->SetRenderLayerName("Weapon");

	m_Effect->SetWorldScale(150.f, 200.f);
	m_Effect->SetPivot(0.f, 0.5f);

	return true;
}

void CArrowHitEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CArrowHitEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CArrowHitEffect* CArrowHitEffect::Clone() const
{
	return new CArrowHitEffect(*this);
}