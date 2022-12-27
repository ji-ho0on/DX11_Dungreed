#include "SkelBowAnimation.h"
#include "Scene/Scene.h"
#include "Component/SpriteComponent.h"
#include "../GameObject/SkelBowAttack.h"
#include "../GameObject/SkelBow.h"

CSkelBowAnimation::CSkelBowAnimation()
{
	m_ClassName = "SkelBowAnimation";
}

CSkelBowAnimation::CSkelBowAnimation(const CSkelBowAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CSkelBowAnimation::~CSkelBowAnimation()
{
}

void CSkelBowAnimation::Start()
{
	CAnimation2D::Start();

	CAnimation2DData* Attack = FindAnimation("Attack");

	if (Attack)
	{
		Attack->AddNotify<CSkelBowAnimation>("Attack", 1, this, &CSkelBowAnimation::AttackStart);
		Attack->AddNotify<CSkelBowAnimation>("Attack", 4, this, &CSkelBowAnimation::AttackEnd);
	}
}

bool CSkelBowAnimation::Init()
{
	AddAnimation("Attack", "Attack_SkelBow", 2.f, 1.f, true);

	//////////////////////////////////////////////////////////////////////////////////////////
	// SkelBow 사용하는 Sound Load
	//////////////////////////////////////////////////////////////////////////////////////////

	// 활 당기는 소리
	CResourceManager::GetInst()->LoadSound("Effect", "CrossBowStretch", false, "enemy/skells/bow_crossbow_arrow_draw_stretch1_03.wav");

	// 활 쏘는 소리
	CResourceManager::GetInst()->LoadSound("Effect", "CrossBowShoot", false, "enemy/skells/etc-sound0034_Bow.wav");

	return true;
}

void CSkelBowAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CSkelBowAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CSkelBowAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CSkelBowAnimation* CSkelBowAnimation::Clone()
{
	return new CSkelBowAnimation(*this);
}

void CSkelBowAnimation::AttackStart()
{
	CResourceManager::GetInst()->FindSound("CrossBowStretch")->Play();
}

void CSkelBowAnimation::AttackEnd()
{
	CSkelBow* SkelBow = (CSkelBow*)m_Owner->GetOwner();

	SkelBow->GetScene()->CreateObject<CSkelBowAttack>("SkelBowAttack")->SetAttackInfo(Vector2(SkelBow->GetWorldPos().x, SkelBow->GetWorldPos().y + 30.f) , SkelBow->GetAttackDir(), SkelBow->GetAttackAngle());

	CResourceManager::GetInst()->FindSound("CrossBowShoot")->Play();
}
