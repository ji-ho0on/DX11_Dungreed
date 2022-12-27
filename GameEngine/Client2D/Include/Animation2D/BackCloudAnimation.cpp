#include "BackCloudAnimation.h"

CBackCloudAnimation::CBackCloudAnimation()
{
	m_ClassName = "BackCloudAnimation";
}

CBackCloudAnimation::CBackCloudAnimation(const CBackCloudAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CBackCloudAnimation::~CBackCloudAnimation()
{
}

bool CBackCloudAnimation::Init()
{
	AddAnimation("BackCloudIdle", "BackCloudIdle", 1.f, 1.f, true);

	return true;
}

void CBackCloudAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CBackCloudAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CBackCloudAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CBackCloudAnimation* CBackCloudAnimation::Clone()
{
	return new CBackCloudAnimation(*this);
}