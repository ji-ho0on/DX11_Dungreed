#include "MonsterDestroyEffect.h"
#include "Component/SpriteComponent.h"
#include "../Animation2D/MonsterDestroyAnimation.h"

CMonsterDestroyEffect::CMonsterDestroyEffect()
{
	SetTypeID<CMonsterDestroyEffect>();

	m_ObjectTypeName = "MonsterDestroyEffect";
}

CMonsterDestroyEffect::CMonsterDestroyEffect(const CMonsterDestroyEffect& Obj) :
	CGameObject(Obj)
{
}

CMonsterDestroyEffect::~CMonsterDestroyEffect()
{
}

void CMonsterDestroyEffect::SetEffectInfo(const Vector2& Position)
{
	m_Effect->SetWorldPosition(Position);
}

void CMonsterDestroyEffect::Start()
{
	CGameObject::Start();
}

bool CMonsterDestroyEffect::Init()
{
	CGameObject::Init();

	m_Effect = CreateComponent<CSpriteComponent>("Effect");
	m_Effect->SetAnimation<CMonsterDestroyAnimation>("MonsterDestroyAnimation");
	m_Effect->SetRenderLayerName("Monster");
	m_Effect->SetWorldScale(100.f, 100.f);
	m_Effect->SetPivot(0.5f, 0.5f);

	return true;
}

void CMonsterDestroyEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CMonsterDestroyEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CMonsterDestroyEffect* CMonsterDestroyEffect::Clone() const
{
	return new CMonsterDestroyEffect(*this);
}

void CMonsterDestroyEffect::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CMonsterDestroyEffect::Load(FILE* File)
{
	CGameObject::Load(File);
}