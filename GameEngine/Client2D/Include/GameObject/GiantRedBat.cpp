#include "GiantRedBat.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../Animation2D/GiantRedBatAnimation.h"
#include "Scene/Scene.h"
#include "MonsterDestroyEffect.h"
#include "Component/GravityAgent.h"
#include "BatBullet.h"
#include "Gold.h"

CGiantRedBat::CGiantRedBat()	:
	m_DetectDistance(1000.f),
	m_AttackAngle(0.f),
	m_AttackTime(0.f),
	m_Attack(false),
	m_BulletSummonTime(0.f),
	m_BulletCount(0),
	m_BulletAngle(0.f),
	m_BulletWaitTime(1.f)
{
	SetTypeID<CGiantRedBat>();

	m_ObjectTypeName = "GiantRedBat";
}

CGiantRedBat::CGiantRedBat(const CGiantRedBat& Obj) :
	CMonster(Obj)
{
	m_GiantRedBat = (CSpriteComponent*)FindComponent("GiantRedBat");

	m_DetectDistance = Obj.m_DetectDistance;

	m_AttackAngle = Obj.m_AttackAngle;
	m_AttackTime = Obj.m_AttackTime;
	m_Attack = Obj.m_Attack;

	m_BulletSummonTime = Obj.m_BulletSummonTime;
	m_BulletCount = Obj.m_BulletCount;
	m_BulletAngle = Obj.m_BulletAngle;
	m_BulletWaitTime = Obj.m_BulletWaitTime;
}

CGiantRedBat::~CGiantRedBat()
{
}

void CGiantRedBat::Start()
{
	CMonster::Start();

	m_PlayerObject = m_Scene->GetSceneInfo()->GetPlayerObject();
}

bool CGiantRedBat::Init()
{
	CMonster::Init();

	m_GiantRedBat = CreateComponent<CSpriteComponent>("GiantRedBat");
	m_GiantRedBat->SetWorldScale(240.f, 120.f);
	m_GiantRedBat->SetRenderLayerName("Monster");

	// Pivot 설정
	m_GiantRedBat->SetPivot(0.5f, 0.f);

	m_Body->SetBoxSize(m_GiantRedBat->GetWorldScale().x, m_GiantRedBat->GetWorldScale().y);
	m_Body->SetWorldPosition(150.f, 300.f);

	m_GiantRedBat->SetAnimation<CGiantRedBatAnimation>("GiantRedBatAnimation");

	m_Body->AddChild(m_GiantRedBat);

	m_Gravity->SetPhysicsSimulate(false);

	m_HP = 80;

	m_DetectDistance = 1000.f;


	if (m_Scene)
	{
		m_Scene->GetResource()->LoadSound("Effect", "Bat2", false, "enemy/bat/Bat2.wav");
	}

	else
	{
		CResourceManager::GetInst()->LoadSound("Effect", "Bat2", false, "enemy/bat/Bat2.wav");
	}


	return true;
}

void CGiantRedBat::Update(float DeltaTime)
{
	CMonster::Update(DeltaTime);

	if (m_Attacked)
		m_GiantRedBat->GetMaterial(0)->SetBaseColor(1.f, 0.f, 0.f, 1.f);

	else
		m_GiantRedBat->GetMaterial(0)->SetBaseColor(1.f, 1.f, 1.f, 1.f);

	// Scene에 Player가 있으면 Player 방향을 바라본다.
	if (m_PlayerObject)
	{
		// 감지거리 안에 있는 경우
		if (m_DetectDistance >= Vector2(m_PlayerObject->GetWorldPos().x, m_PlayerObject->GetWorldPos().y).Distance(GetWorldPos()))
		{
			// Player를 바라본다.
			if (m_PlayerObject->GetWorldPos().x - GetWorldPos().x > 0.f)
			{
				if (m_GiantRedBat->GetDir() == EDirection::Left)
					m_GiantRedBat->SetDir(EDirection::Right);
			}

			else
			{
				if (m_GiantRedBat->GetDir() == EDirection::Right)
					m_GiantRedBat->SetDir(EDirection::Left);
			}

			if (!m_Attack)
			{
				m_AttackTime += DeltaTime;

				if (m_AttackTime >= 6.f)
				{
					m_ActionType = EMonsterActionType::Attack;
					m_AttackTime = 0.f;
					m_Attack = true;

					m_BulletSummonTime = 0.f;
					m_BulletCount = 0;
					m_BulletAngle = 0.f;
					m_BulletWaitTime = 1.f;

					// 플레이어를 바라보는 방향을 구한다.
					m_AttackAngle = Vector2(GetWorldPos().x, GetWorldPos().y).Angle(m_PlayerObject->GetWorldPos());
				}
			}
		}

		else
			m_ActionType = EMonsterActionType::Idle;
	}

	if (m_HP <= 0)
		m_ActionType = EMonsterActionType::Die;

	if (m_Attack)
	{
		// 총알 20개를 18도씩 원형으로 추가해서 다 추가되면 한번에 발사
		m_BulletSummonTime += DeltaTime;

		if (m_BulletCount >= 20)
		{
			m_Attack = false;
			m_BulletCount = 0;
			m_BulletWaitTime = 1.f;
			m_BulletAngle = 0.f;
			m_ActionType = EMonsterActionType::Idle;
		}

		if (m_BulletCount == 1)
			m_Scene->GetResource()->FindSound("Bat2")->Play();

		//else if(m_BulletCount == 10)
		//	m_Scene->GetResource()->FindSound("Bat2")->Play();

		//else if (m_BulletCount == 19)
		//	m_Scene->GetResource()->FindSound("Bat2")->Play();

		if (m_BulletSummonTime >= 0.05f)
		{
			m_BulletSummonTime -= 0.05f;

			SummonBullet();

			++m_BulletCount;
			m_BulletWaitTime -= 0.05f;
			m_BulletAngle += 18.f;
		}
	}
}

void CGiantRedBat::PostUpdate(float DeltaTime)
{
	CMonster::PostUpdate(DeltaTime);

	switch (m_ActionType)
	{
	case EMonsterActionType::Idle:
		m_GiantRedBat->GetAnimation()->ChangeAnimation("Idle");
		break;
	case EMonsterActionType::Move:
	{
		// 무작위 방향으로 움직인다.
	}
	break;
	case EMonsterActionType::Attack:
	{
		m_GiantRedBat->GetAnimation()->ChangeAnimation("Attack");

		// 원형으로 Bullet을 생성해서 한번에 발사해야함 18도씩 20개 생성
	}
		break;
	case EMonsterActionType::Die:
		m_Scene->CreateObject<CMonsterDestroyEffect>("MonsterDestroyEffect")->SetEffectInfo(Vector2(m_Body->GetWorldPos().x, m_Body->GetWorldPos().y + m_GiantRedBat->GetWorldScale().y / 2.f));
		m_Scene->GetResource()->FindSound("MonsterDie")->Play();
		m_Scene->CreateObject<CGold>("Gold")->SetGoldInfo(m_Body->GetWorldPos());
		Destroy();
		break;
	}
}

CGiantRedBat* CGiantRedBat::Clone() const
{
	return new CGiantRedBat(*this);
}

void CGiantRedBat::SummonBullet()
{
	CBatBullet* BatBullet = m_Scene->CreateObject<CBatBullet>("BatBullet");
	BatBullet->SetBulletScale(Vector2(60.f, 60.f));

	Vector2 InitPos = m_GiantRedBat->GetWorldPos();
	InitPos.y += m_GiantRedBat->GetWorldScale().y / 2.f;

	Vector2 BulletPos = InitPos + Vector2(100.f * cosf(m_BulletAngle * PI / 180.f), 100.f * sinf(m_BulletAngle * PI / 180.f));

	BatBullet->SetBulletInfo(BulletPos, m_AttackAngle);
	BatBullet->SetMoveWaitTime(m_BulletWaitTime);
}
