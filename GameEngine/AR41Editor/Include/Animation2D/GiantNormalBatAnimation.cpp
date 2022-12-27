#include "GiantNormalBatAnimation.h"
#include "Component/SpriteComponent.h"
#include "Scene/Scene.h"
#include "../GameObject/BatBullet.h"
#include "../GameObject/GiantNormalBat.h"

CGiantNormalBatAnimation::CGiantNormalBatAnimation()
{
	m_ClassName = "GiantNormalBatAnimation";
}

CGiantNormalBatAnimation::CGiantNormalBatAnimation(const CGiantNormalBatAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CGiantNormalBatAnimation::~CGiantNormalBatAnimation()
{
}

void CGiantNormalBatAnimation::Start()
{
	CAnimation2D::Start();

	CAnimation2DData* Attack = FindAnimation("Attack");

	if (Attack)
	{
		Attack->AddNotify<CGiantNormalBatAnimation>("SummonBullet", 3, this, &CGiantNormalBatAnimation::SummonBullet);
		Attack->AddNotify<CGiantNormalBatAnimation>("SummonBullet", 6, this, &CGiantNormalBatAnimation::SummonBullet);
		Attack->AddNotify<CGiantNormalBatAnimation>("SummonBullet", 9, this, &CGiantNormalBatAnimation::SummonBullet);
		Attack->SetEndFunction<CGiantNormalBatAnimation>(this, &CGiantNormalBatAnimation::AttackEnd);
	}
}

bool CGiantNormalBatAnimation::Init()
{
	AddAnimation("Idle", "Idle_GiantNormalBat", 1.f, 1.f, true);
	AddAnimation("Attack", "Attack_GiantNormalBat", 1.f, 1.5f, false);

	//////////////////////////////////////////////////////////////////////////////////////////
	// Bat가 사용하는 Sound Load
	//////////////////////////////////////////////////////////////////////////////////////////

	// 공격 소리
	CResourceManager::GetInst()->LoadSound("Effect", "Bat2", false, "enemy/bat/Bat2.wav");

	return true;
}

void CGiantNormalBatAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CGiantNormalBatAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CGiantNormalBatAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CGiantNormalBatAnimation* CGiantNormalBatAnimation::Clone()
{
	return new CGiantNormalBatAnimation(*this);
}

void CGiantNormalBatAnimation::SummonBullet()
{
	CBatBullet* BatBullet1 = m_Owner->GetScene()->CreateObject<CBatBullet>("BatBullet1");
	CBatBullet* BatBullet2 = m_Owner->GetScene()->CreateObject<CBatBullet>("BatBullet2");
	CBatBullet* BatBullet3 = m_Owner->GetScene()->CreateObject<CBatBullet>("BatBullet3");

	Vector2 InitPos = m_Owner->GetWorldPos();
	InitPos.y += m_Owner->GetWorldScale().y / 2.f;

	BatBullet1->SetBulletScale(Vector2(60.f, 60.f));
	BatBullet2->SetBulletScale(Vector2(60.f, 60.f));
	BatBullet3->SetBulletScale(Vector2(60.f, 60.f));

	CGiantNormalBat* GiantNormalBat = (CGiantNormalBat*)m_Owner->GetOwner();
	float AttackAngle = GiantNormalBat->GetAttackAngle();


	// 플레이어 바라보는 각도 가져와서 +15도 -15도 0도 3개 발사
	BatBullet1->SetBulletInfo(InitPos, AttackAngle - 15.f);
	BatBullet2->SetBulletInfo(InitPos, AttackAngle);
	BatBullet3->SetBulletInfo(InitPos, AttackAngle + 15.f);

	CResourceManager::GetInst()->FindSound("Bat2")->Play();
}

void CGiantNormalBatAnimation::AttackEnd()
{
	CGiantNormalBat* GiantNormalBat = (CGiantNormalBat*)m_Owner->GetOwner();

	GiantNormalBat->SetMonsterActionType(EMonsterActionType::Idle);
}