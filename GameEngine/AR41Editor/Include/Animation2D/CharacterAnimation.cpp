#include "CharacterAnimation.h"

CCharacterAnimation::CCharacterAnimation()
{
	m_ClassName = "CharacterAnimation";
}

CCharacterAnimation::CCharacterAnimation(const CCharacterAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CCharacterAnimation::~CCharacterAnimation()
{
}

bool CCharacterAnimation::Init()
{
	AddAnimation("CharacterIdle", "CharacterIdle_Base", 1.f, 1.f, true);
	AddAnimation("CharacterRun", "CharacterRun_Base", 1.f, 1.f, true);
	AddAnimation("CharacterJump", "CharacterJump_Base", 1.f, 1.f, true);
	AddAnimation("CharacterDie", "CharacterDie_Base", 1.f, 1.f, true);

	return true;
}

void CCharacterAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CCharacterAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CCharacterAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CCharacterAnimation* CCharacterAnimation::Clone()
{
	return new CCharacterAnimation(*this);
}