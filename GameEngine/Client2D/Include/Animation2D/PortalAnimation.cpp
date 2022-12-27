#include "PortalAnimation.h"

CPortalAnimation::CPortalAnimation()
{
	m_ClassName = "DoorAnimation";
}

CPortalAnimation::CPortalAnimation(const CPortalAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CPortalAnimation::~CPortalAnimation()
{
}

void CPortalAnimation::Start()
{
	CAnimation2D::Start();

	CAnimation2DData* PortalCreate = FindAnimation("PortalCreate");

	if (PortalCreate)
	{
		PortalCreate->SetEndFunction<CPortalAnimation>(this, &CPortalAnimation::PortalCreateEnd);
	}
}

bool CPortalAnimation::Init()
{
	AddAnimation("PortalCreate", "PortalCreate", 1.f, 2.f, false);
	AddAnimation("Portal", "Portal", 1.f, 1.f, true);

	return true;
}

void CPortalAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CPortalAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CPortalAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CPortalAnimation* CPortalAnimation::Clone()
{
	return new CPortalAnimation(*this);
}

void CPortalAnimation::PortalCreateEnd()
{
	ChangeAnimation("Portal");
}
