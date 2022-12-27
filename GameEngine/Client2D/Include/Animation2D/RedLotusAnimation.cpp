#include "RedLotusAnimation.h"

CRedLotusAnimation::CRedLotusAnimation()
{
	m_ClassName = "RedLotusAnimation";
}

CRedLotusAnimation::CRedLotusAnimation(const CRedLotusAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CRedLotusAnimation::~CRedLotusAnimation()
{
}

bool CRedLotusAnimation::Init()
{
	AddAnimation("CharacterIdle", "CharacterIdle_RedLotus", 1.f, 1.f, true);
	AddAnimation("CharacterRun", "CharacterRun_RedLotus", 1.f, 1.f, true);
	AddAnimation("CharacterJump", "CharacterJump_RedLotus", 1.f, 1.f, true);
	AddAnimation("CharacterDie", "CharacterDie_RedLotus", 1.f, 1.f, true);

	return true;
}

void CRedLotusAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CRedLotusAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CRedLotusAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CRedLotusAnimation* CRedLotusAnimation::Clone()
{
	return new CRedLotusAnimation(*this);
}