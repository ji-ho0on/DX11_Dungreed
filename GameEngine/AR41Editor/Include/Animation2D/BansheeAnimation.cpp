#include "BansheeAnimation.h"
#include "Component/SpriteComponent.h"
#include "Scene/Scene.h"
#include "../GameObject/BansheeBullet.h"
#include "../GameObject/Banshee.h"

CBansheeAnimation::CBansheeAnimation()
{
	m_ClassName = "BansheeAnimation";
}

CBansheeAnimation::CBansheeAnimation(const CBansheeAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CBansheeAnimation::~CBansheeAnimation()
{
}

void CBansheeAnimation::Start()
{
	CAnimation2D::Start();

	CAnimation2DData* Attack = FindAnimation("Attack");

	if (Attack)
	{
		Attack->AddNotify<CBansheeAnimation>("SummonBullet", 1, this, &CBansheeAnimation::SummonBullet);
		Attack->SetEndFunction<CBansheeAnimation>(this, &CBansheeAnimation::AttackEnd);
	}
}

bool CBansheeAnimation::Init()
{
	AddAnimation("Idle", "Idle_Banshee", 1.f, 1.f, true);
	AddAnimation("Attack", "Attack_Banshee", 1.f, 1.5f, false);

	//////////////////////////////////////////////////////////////////////////////////////////
	// Banshee가 사용하는 Sound Load
	//////////////////////////////////////////////////////////////////////////////////////////

	// 공격 소리
	CResourceManager::GetInst()->LoadSound("Effect", "BansheeScream", false, "enemy/banshee/high_pitch_scream_gverb.wav");

	return true;
}

void CBansheeAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CBansheeAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CBansheeAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CBansheeAnimation* CBansheeAnimation::Clone()
{
	return new CBansheeAnimation(*this);
}

void CBansheeAnimation::SummonBullet()
{
	CBansheeBullet* BansheeBullet1 = m_Owner->GetScene()->CreateObject<CBansheeBullet>("BansheeBullet1");
	CBansheeBullet* BansheeBullet2 = m_Owner->GetScene()->CreateObject<CBansheeBullet>("BansheeBullet2");
	CBansheeBullet* BansheeBullet3 = m_Owner->GetScene()->CreateObject<CBansheeBullet>("BansheeBullet3");
	CBansheeBullet* BansheeBullet4 = m_Owner->GetScene()->CreateObject<CBansheeBullet>("BansheeBullet4");
	CBansheeBullet* BansheeBullet5 = m_Owner->GetScene()->CreateObject<CBansheeBullet>("BansheeBullet5");
	CBansheeBullet* BansheeBullet6 = m_Owner->GetScene()->CreateObject<CBansheeBullet>("BansheeBullet6");
	CBansheeBullet* BansheeBullet7 = m_Owner->GetScene()->CreateObject<CBansheeBullet>("BansheeBullet7");
	CBansheeBullet* BansheeBullet8 = m_Owner->GetScene()->CreateObject<CBansheeBullet>("BansheeBullet8");
	CBansheeBullet* BansheeBullet9 = m_Owner->GetScene()->CreateObject<CBansheeBullet>("BansheeBullet9");
	CBansheeBullet* BansheeBullet10 = m_Owner->GetScene()->CreateObject<CBansheeBullet>("BansheeBullet10");
	CBansheeBullet* BansheeBullet11 = m_Owner->GetScene()->CreateObject<CBansheeBullet>("BansheeBullet11");
	CBansheeBullet* BansheeBullet12 = m_Owner->GetScene()->CreateObject<CBansheeBullet>("BansheeBullet12");

	Vector2 InitPos = m_Owner->GetWorldPos();
	InitPos.y += m_Owner->GetWorldScale().y / 2.f;

	BansheeBullet1->SetBulletInfo(InitPos, 0.f);
	BansheeBullet2->SetBulletInfo(InitPos, 30.f);
	BansheeBullet3->SetBulletInfo(InitPos, 60.f);
	BansheeBullet4->SetBulletInfo(InitPos, 90.f);
	BansheeBullet5->SetBulletInfo(InitPos, 120.f);
	BansheeBullet6->SetBulletInfo(InitPos, 150.f);
	BansheeBullet7->SetBulletInfo(InitPos, 180.f);
	BansheeBullet8->SetBulletInfo(InitPos, 210.f);
	BansheeBullet9->SetBulletInfo(InitPos, 240.f);
	BansheeBullet10->SetBulletInfo(InitPos, 270.f);
	BansheeBullet11->SetBulletInfo(InitPos, 300.f);
	BansheeBullet12->SetBulletInfo(InitPos, 330.f);

	CResourceManager::GetInst()->FindSound("BansheeScream")->Play();
}

void CBansheeAnimation::AttackEnd()
{
	CBanshee* Banshee = (CBanshee*)m_Owner->GetOwner();

	Banshee->SetMonsterActionType(EMonsterActionType::Idle);
}
