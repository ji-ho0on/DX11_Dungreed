#include "AliceAnimation.h"

CAliceAnimation::CAliceAnimation()
{
	m_ClassName = "AliceAnimation";
}

CAliceAnimation::CAliceAnimation(const CAliceAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CAliceAnimation::~CAliceAnimation()
{
}

bool CAliceAnimation::Init()
{
	AddAnimation("CharacterIdle", "CharacterIdle_Alice", 1.f, 1.f, true);
	AddAnimation("CharacterRun", "CharacterRun_Alice", 1.f, 1.f, true);
	AddAnimation("CharacterJump", "CharacterJump_Alice", 1.f, 1.f, true);
	AddAnimation("CharacterDie", "CharacterDie_Alice", 1.f, 1.f, true);

	return true;
}

void CAliceAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CAliceAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CAliceAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CAliceAnimation* CAliceAnimation::Clone()
{
	return new CAliceAnimation(*this);
}