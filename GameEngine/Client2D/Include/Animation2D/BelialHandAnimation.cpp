#include "BelialHandAnimation.h"
#include "Component/SpriteComponent.h"
#include "GameObject/GameObject.h"
#include "Scene/Scene.h"
#include "../GameObject/BelialLaser.h"

CBelialHandAnimation::CBelialHandAnimation()
{
	m_ClassName = "BelialHandAnimation";
}

CBelialHandAnimation::CBelialHandAnimation(const CBelialHandAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CBelialHandAnimation::~CBelialHandAnimation()
{
}

void CBelialHandAnimation::Start()
{
	CAnimation2D::Start();

	CAnimation2DData* Attack = FindAnimation("Attack");

	if (Attack)
	{
		Attack->AddNotify<CBelialHandAnimation>("Laser", 9, this, &CBelialHandAnimation::Attack);
		Attack->SetEndFunction<CBelialHandAnimation>(this, &CBelialHandAnimation::AttackEnd);
	}
}

bool CBelialHandAnimation::Init()
{
	AddAnimation("Idle", "BelialHand_Idle", 1.f, 1.f, true);
	AddAnimation("Attack", "BelialHand_Attack", 1.f, 1.f, false);

	// Laser 발사 소리
	CResourceManager::GetInst()->LoadSound("Effect", "AttackLaser", false, "enemy/belial/iceball.wav");

	return true;
}

void CBelialHandAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CBelialHandAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CBelialHandAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CBelialHandAnimation* CBelialHandAnimation::Clone()
{
	return new CBelialHandAnimation(*this);
}

void CBelialHandAnimation::Attack()
{
	// Laser 생성
	CBelialLaser* Laser = m_Owner->GetOwner()->GetScene()->CreateObject<CBelialLaser>("BelialLaser");

	// 오른손
	if (m_Owner->GetDir() == EDirection::Left)
		Laser->SetLaserInfo(m_Owner->GetWorldPos(), true);

	else
		Laser->SetLaserInfo(m_Owner->GetWorldPos(), false);

	CResourceManager::GetInst()->FindSound("AttackLaser")->Play();
}

void CBelialHandAnimation::AttackEnd()
{
	// 공격이 끝나면 Idle 모션으로 돌아감
	ChangeAnimation("Idle");
}
