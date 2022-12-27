#include "FrontCloudAnimation.h"

CFrontCloudAnimation::CFrontCloudAnimation()
{
	m_ClassName = "FrontCloudAnimation";
}

CFrontCloudAnimation::CFrontCloudAnimation(const CFrontCloudAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CFrontCloudAnimation::~CFrontCloudAnimation()
{
}

bool CFrontCloudAnimation::Init()
{
	AddAnimation("FrontCloudIdle", "FrontCloudIdle", 1.f, 1.f, true);

	return true;
}

void CFrontCloudAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CFrontCloudAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CFrontCloudAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CFrontCloudAnimation* CFrontCloudAnimation::Clone()
{
	return new CFrontCloudAnimation(*this);
}