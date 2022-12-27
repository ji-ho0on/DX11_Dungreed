#include "MonsterDestroyAnimation.h"
#include "Component/SpriteComponent.h"
#include "GameObject/GameObject.h"

CMonsterDestroyAnimation::CMonsterDestroyAnimation()
{
	m_ClassName = "MonsterDestroyAnimation";
}

CMonsterDestroyAnimation::CMonsterDestroyAnimation(const CMonsterDestroyAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CMonsterDestroyAnimation::~CMonsterDestroyAnimation()
{
}

void CMonsterDestroyAnimation::Start()
{
	CAnimation2D::Start();

	CAnimation2DData* Effect = FindAnimation("Destroy");

	if (Effect)
		Effect->SetEndFunction<CMonsterDestroyAnimation>(this, &CMonsterDestroyAnimation::DestroyEnd);
}

bool CMonsterDestroyAnimation::Init()
{
	AddAnimation("Destroy", "MonsterDestroy", 0.5f, 1.f, false);

	return true;
}

void CMonsterDestroyAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CMonsterDestroyAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CMonsterDestroyAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CMonsterDestroyAnimation* CMonsterDestroyAnimation::Clone()
{
	return new CMonsterDestroyAnimation(*this);
}

void CMonsterDestroyAnimation::DestroyEnd()
{
	m_Owner->GetOwner()->Destroy();
}
