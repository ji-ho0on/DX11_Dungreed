#include "RedBatAnimation.h"
#include "Component/SpriteComponent.h"
#include "Scene/Scene.h"
#include "../GameObject/BatBullet.h"
#include "../GameObject/RedBat.h"

CRedBatAnimation::CRedBatAnimation()
{
	m_ClassName = "RedBatAnimation";
}

CRedBatAnimation::CRedBatAnimation(const CRedBatAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CRedBatAnimation::~CRedBatAnimation()
{
}

void CRedBatAnimation::Start()
{
	CAnimation2D::Start();

	CAnimation2DData* Attack = FindAnimation("Attack");

	if (Attack)
	{
		Attack->AddNotify<CRedBatAnimation>("SummonBullet", 4, this, &CRedBatAnimation::SummonBullet);
		Attack->SetEndFunction<CRedBatAnimation>(this, &CRedBatAnimation::AttackEnd);
	}
}

bool CRedBatAnimation::Init()
{
	AddAnimation("Idle", "Idle_RedBat", 1.f, 1.f, true);
	AddAnimation("Attack", "Attack_RedBat", 1.f, 1.5f, false);

	//////////////////////////////////////////////////////////////////////////////////////////
	// Bat가 사용하는 Sound Load
	//////////////////////////////////////////////////////////////////////////////////////////

	// 공격 소리
	CResourceManager::GetInst()->LoadSound("Effect", "Bat2", false, "enemy/bat/Bat2.wav");

	return true;
}

void CRedBatAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CRedBatAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CRedBatAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CRedBatAnimation* CRedBatAnimation::Clone()
{
	return new CRedBatAnimation(*this);
}

void CRedBatAnimation::SummonBullet()
{
	CBatBullet* BatBullet = m_Owner->GetScene()->CreateObject<CBatBullet>("BatBullet");

	Vector2 InitPos = m_Owner->GetWorldPos();
	InitPos.y += m_Owner->GetWorldScale().y / 2.f;

	CRedBat* RedBat = (CRedBat*)m_Owner->GetOwner();
	float AttackAngle = RedBat->GetAttackAngle();

	// 플레이어 바라보는 각도 가져와서 각도 넣어줘야함
	BatBullet->SetBulletInfo(InitPos, AttackAngle);

	CResourceManager::GetInst()->FindSound("Bat2")->Play();
}

void CRedBatAnimation::AttackEnd()
{
	CRedBat* RedBat = (CRedBat*)m_Owner->GetOwner();

	RedBat->SetMonsterActionType(EMonsterActionType::Move);
}