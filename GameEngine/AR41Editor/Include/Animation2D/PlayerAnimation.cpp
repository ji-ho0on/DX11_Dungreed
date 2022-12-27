#include "PlayerAnimation.h"

CPlayerAnimation::CPlayerAnimation()
{
	m_ClassName = "PlayerAnimation";
}

CPlayerAnimation::CPlayerAnimation(const CPlayerAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CPlayerAnimation::~CPlayerAnimation()
{
}

bool CPlayerAnimation::Init()
{
	//AddAnimation("CharacterIdle", "PlayerBase_Idle", 1.f, 1.f, true);
	//AddAnimation("CharacterRun", "PlayerBase_Run", 1.f, 1.f, true);
	//AddAnimation("CharacterJump", "PlayerBase_Jump", 1.f, 1.f, true);
	//AddAnimation("CharacterDie", "PlayerBase_Die", 1.f, 1.f, true);
	//AddAnimation("PlayerIdle", "PlayerIdle", 1.f, 1.f, true);
	//AddAnimation("PlayerRun", "PlayerRun", 1.f, 1.f, true);
	//AddAnimation("PlayerTest", "Test", 1.f, 1.f, true);

	return true;
}

void CPlayerAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CPlayerAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CPlayerAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CPlayerAnimation* CPlayerAnimation::Clone()
{
	return new CPlayerAnimation(*this);
}