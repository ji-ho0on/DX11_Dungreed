#include "HorseAnimation.h"

CHorseAnimation::CHorseAnimation()
{
	m_ClassName = "HorseAnimation";
}

CHorseAnimation::CHorseAnimation(const CHorseAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CHorseAnimation::~CHorseAnimation()
{
}

void CHorseAnimation::Start()
{
	CAnimation2D::Start();
}

bool CHorseAnimation::Init()
{
	AddAnimation("Horse", "Horse", 1.f, 1.f, true);

	return true;
}

void CHorseAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CHorseAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CHorseAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CHorseAnimation* CHorseAnimation::Clone()
{
	return new CHorseAnimation(*this);
}