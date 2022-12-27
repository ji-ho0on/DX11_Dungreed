#include "ArrowHitAnimation.h"
#include "Component/SpriteComponent.h"
#include "GameObject/GameObject.h"

CArrowHitAnimation::CArrowHitAnimation()
{
	m_ClassName = "ArrowHitAnimation";
}

CArrowHitAnimation::CArrowHitAnimation(const CArrowHitAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CArrowHitAnimation::~CArrowHitAnimation()
{
}

void CArrowHitAnimation::Start()
{
	CAnimation2D::Start();

	CAnimation2DData* ArrowHit = FindAnimation("ArrowHit");

	if (ArrowHit)
		ArrowHit->SetEndFunction<CArrowHitAnimation>(this, &CArrowHitAnimation::ArrowHitEnd);
}

bool CArrowHitAnimation::Init()
{
	AddAnimation("ArrowHit", "ArrowHitEffect", 0.25f, 1.f, false);

	return true;
}

void CArrowHitAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CArrowHitAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CArrowHitAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CArrowHitAnimation* CArrowHitAnimation::Clone()
{
	return new CArrowHitAnimation(*this);
}

void CArrowHitAnimation::ArrowHitEnd()
{
	m_Owner->GetOwner()->Destroy();
}