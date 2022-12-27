#include "BirdAnimation.h"

CBirdAnimation::CBirdAnimation()
{
	m_ClassName = "BirdAnimation";
}

CBirdAnimation::CBirdAnimation(const CBirdAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CBirdAnimation::~CBirdAnimation()
{
}

bool CBirdAnimation::Init()
{
	AddAnimation("BirdIdle", "BirdIdle", 1.f, 1.8f, true);

	return true;
}

void CBirdAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CBirdAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CBirdAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CBirdAnimation* CBirdAnimation::Clone()
{
	return new CBirdAnimation(*this);
}
