#include "MetalPlateAnimation.h"

CMetalPlateAnimation::CMetalPlateAnimation()
{
	m_ClassName = "MetalPlateAnimation";
}

CMetalPlateAnimation::CMetalPlateAnimation(const CMetalPlateAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CMetalPlateAnimation::~CMetalPlateAnimation()
{
}

bool CMetalPlateAnimation::Init()
{
	AddAnimation("CharacterIdle", "CharacterIdle_MetalPlate", 1.f, 1.f, true);
	AddAnimation("CharacterRun", "CharacterRun_MetalPlate", 1.f, 1.f, true);
	AddAnimation("CharacterJump", "CharacterJump_MetalPlate", 1.f, 1.f, true);
	AddAnimation("CharacterDie", "CharacterDie_MetalPlate", 1.f, 1.f, true);

	return true;
}

void CMetalPlateAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CMetalPlateAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CMetalPlateAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CMetalPlateAnimation* CMetalPlateAnimation::Clone()
{
	return new CMetalPlateAnimation(*this);
}