#include "SkelSwordAnimation.h"
#include "Scene/Scene.h"
#include "Component/SpriteComponent.h"
#include "../GameObject/SkelSwordAttack.h"
#include "../GameObject/SkelSword.h"

CSkelSwordAnimation::CSkelSwordAnimation()
{
	m_ClassName = "SkelSwordAnimation";
}

CSkelSwordAnimation::CSkelSwordAnimation(const CSkelSwordAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CSkelSwordAnimation::~CSkelSwordAnimation()
{
}

void CSkelSwordAnimation::Start()
{
	CAnimation2D::Start();

	CAnimation2DData* Attack = FindAnimation("Attack");

	if (Attack)
		Attack->AddNotify<CSkelSwordAnimation>("Attack", 6, this, &CSkelSwordAnimation::AttackEnd);
}

bool CSkelSwordAnimation::Init()
{
	AddAnimation("Attack", "Attack_SkelSword", 1.f, 1.f, true);

	//////////////////////////////////////////////////////////////////////////////////////////
	// SkelSword 사용하는 Sound Load
	//////////////////////////////////////////////////////////////////////////////////////////
	
	// 공격 소리
	CResourceManager::GetInst()->LoadSound("Effect", "Swish", false, "enemy/skells/swish-1.wav");

	return true;
}

void CSkelSwordAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CSkelSwordAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CSkelSwordAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CSkelSwordAnimation* CSkelSwordAnimation::Clone()
{
	return new CSkelSwordAnimation(*this);
}

void CSkelSwordAnimation::AttackEnd()
{
	CSkelSword* SkelSword = (CSkelSword*)m_Owner->GetOwner();

	if (((CSpriteComponent*)SkelSword->FindComponent("Skel"))->GetDir() == EDirection::Right)
		SkelSword->GetScene()->CreateObject<CSkelSwordAttack>("SkelSwordAttack")->SetAttackInfo(Vector2(SkelSword->GetWorldPos().x + 30.f, SkelSword->GetWorldPos().y + 30.f));

	else
		SkelSword->GetScene()->CreateObject<CSkelSwordAttack>("SkelSwordAttack")->SetAttackInfo(Vector2(SkelSword->GetWorldPos().x - 30.f, SkelSword->GetWorldPos().y + 30.f));

	CResourceManager::GetInst()->FindSound("Swish")->Play();
}
