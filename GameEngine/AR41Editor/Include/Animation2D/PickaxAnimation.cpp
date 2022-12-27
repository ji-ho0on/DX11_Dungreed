#include "PickaxAnimation.h"

CPickaxAnimation::CPickaxAnimation()
{
	m_ClassName = "PickaxAnimation";
}

CPickaxAnimation::CPickaxAnimation(const CPickaxAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CPickaxAnimation::~CPickaxAnimation()
{
}

bool CPickaxAnimation::Init()
{
	AddAnimation("CharacterIdle", "CharacterIdle_Pickax", 1.f, 1.f, true);
	AddAnimation("CharacterRun", "CharacterRun_Pickax", 1.f, 1.f, true);
	AddAnimation("CharacterJump", "CharacterJump_Pickax", 1.f, 1.f, true);
	AddAnimation("CharacterDie", "CharacterDie_Pickax", 1.f, 1.f, true);

	return true;
}

void CPickaxAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CPickaxAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CPickaxAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CPickaxAnimation* CPickaxAnimation::Clone()
{
	return new CPickaxAnimation(*this);
}