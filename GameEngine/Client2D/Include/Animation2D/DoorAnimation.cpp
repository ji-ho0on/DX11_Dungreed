#include "DoorAnimation.h"

CDoorAnimation::CDoorAnimation()
{
	m_ClassName = "DoorAnimation";
}

CDoorAnimation::CDoorAnimation(const CDoorAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CDoorAnimation::~CDoorAnimation()
{
}

void CDoorAnimation::Start()
{
	CAnimation2D::Start();
}

bool CDoorAnimation::Init()
{
	AddAnimation("DoorAnimation", "DoorAnimation", 1.f, 1.f, false);

	return true;
}

void CDoorAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CDoorAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CDoorAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CDoorAnimation* CDoorAnimation::Clone()
{
	return new CDoorAnimation(*this);
}