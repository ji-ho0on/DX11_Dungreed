#include "SkelAnimation.h"

CSkelAnimation::CSkelAnimation()
{
	m_ClassName = "SkelAnimation";
}

CSkelAnimation::CSkelAnimation(const CSkelAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CSkelAnimation::~CSkelAnimation()
{
}

bool CSkelAnimation::Init()
{
	AddAnimation("Idle", "Idle_Skel", 1.f, 1.f, true);
	AddAnimation("Move", "Move_Skel", 1.f, 1.f, true);

	return true;
}

void CSkelAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CSkelAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CSkelAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CSkelAnimation* CSkelAnimation::Clone()
{
	return new CSkelAnimation(*this);
}
