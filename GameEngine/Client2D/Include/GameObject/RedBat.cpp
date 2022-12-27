#include "RedBat.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../Animation2D/RedBatAnimation.h"
#include "Scene/Scene.h"
#include "MonsterDestroyEffect.h"
#include "Component/GravityAgent.h"
#include "Gold.h"

CRedBat::CRedBat()	:
	m_MoveDirChangeTime(0.f),
	m_AttackTime(0.f)
{
	SetTypeID<CRedBat>();

	m_ObjectTypeName = "RedBat";
}

CRedBat::CRedBat(const CRedBat& Obj) :
	CMonster(Obj)
{
	m_RedBat = (CSpriteComponent*)FindComponent("RedBat");

	m_DetectDistance = Obj.m_DetectDistance;

	m_MoveDirChangeTime = Obj.m_MoveDirChangeTime;
	m_AttackAngle = Obj.m_AttackAngle;
	m_AttackTime = Obj.m_AttackTime;
}

CRedBat::~CRedBat()
{
}

void CRedBat::Start()
{
	CMonster::Start();

	m_PlayerObject = m_Scene->GetSceneInfo()->GetPlayerObject();
}

bool CRedBat::Init()
{
	CMonster::Init();

	m_RedBat = CreateComponent<CSpriteComponent>("RedBat");
	m_RedBat->SetWorldScale(90.f, 45.f);
	m_RedBat->SetRenderLayerName("Monster");

	// Pivot 설정
	m_RedBat->SetPivot(0.5f, 0.f);

	m_Body->SetBoxSize(m_RedBat->GetWorldScale().x, m_RedBat->GetWorldScale().y);
	m_Body->SetWorldPosition(150.f, 300.f);

	m_RedBat->SetAnimation<CRedBatAnimation>("RedBatAnimation");

	m_Body->AddChild(m_RedBat);

	m_Gravity->SetPhysicsSimulate(false);

	m_HP = 30;

	m_DetectDistance = 1000.f;

	m_ActionType = EMonsterActionType::Move;

	return true;
}

void CRedBat::Update(float DeltaTime)
{
	CMonster::Update(DeltaTime);

	if (m_Attacked)
		m_RedBat->GetMaterial(0)->SetBaseColor(1.f, 0.f, 0.f, 1.f);

	else
		m_RedBat->GetMaterial(0)->SetBaseColor(1.f, 1.f, 1.f, 1.f);

	// Scene에 Player가 있으면 Player 방향을 바라본다.
	if (m_PlayerObject)
	{
		// 감지거리 안에 있는 경우
		if (m_DetectDistance >= Vector2(m_PlayerObject->GetWorldPos().x, m_PlayerObject->GetWorldPos().y).Distance(GetWorldPos()))
		{
			// Player를 바라본다.
			if (m_PlayerObject->GetWorldPos().x - GetWorldPos().x > 0.f)
			{
				if (m_RedBat->GetDir() == EDirection::Left)
					m_RedBat->SetDir(EDirection::Right);
			}

			else
			{
				if (m_RedBat->GetDir() == EDirection::Right)
					m_RedBat->SetDir(EDirection::Left);
			}

			m_AttackTime += DeltaTime;

			if (m_AttackTime >= 6.f)
			{
				m_ActionType = EMonsterActionType::Attack;
				m_AttackTime = 0.f;

				// 플레이어를 바라보는 방향을 구한다.
				m_AttackAngle = Vector2(GetWorldPos().x, GetWorldPos().y).Angle(m_PlayerObject->GetWorldPos());
			}
		}

		else
			m_ActionType = EMonsterActionType::Idle;
	}

	if (m_HP <= 0)
		m_ActionType = EMonsterActionType::Die;

	if (m_ActionType == EMonsterActionType::Move)
	{
		m_MoveDirChangeTime += DeltaTime;

		if (m_MoveDirChangeTime >= 1.f)
		{
			m_MoveDirChangeTime -= 1.f;

			ERedBatMoveDir Dir = (ERedBatMoveDir)(rand() % (int)ERedBatMoveDir::End);

			switch (Dir)
			{
			case ERedBatMoveDir::LT:
				m_MoveDir = Vector3(-1.f, 1.f, 0.f);
				break;
			case ERedBatMoveDir::RT:
				m_MoveDir = Vector3(1.f, 1.f, 0.f);
				break;
			case ERedBatMoveDir::LB:
				m_MoveDir = Vector3(-1.f, -1.f, 0.f);
				break;
			case ERedBatMoveDir::RB:
				m_MoveDir = Vector3(1.f, -1.f, 0.f);
				break;
			}

			m_MoveDir.Normalize();
		}
	}
}

void CRedBat::PostUpdate(float DeltaTime)
{
	CMonster::PostUpdate(DeltaTime);

	switch (m_ActionType)
	{
	case EMonsterActionType::Idle:
		m_RedBat->GetAnimation()->ChangeAnimation("Idle");
		break;
	case EMonsterActionType::Move:
	{
		m_RedBat->GetAnimation()->ChangeAnimation("Idle");
		// 무작위 방향으로 움직인다.
		m_Body->AddWorldPosition(m_MoveDir * 50.f * DeltaTime);
	}
		break;
	case EMonsterActionType::Attack:
		m_RedBat->GetAnimation()->ChangeAnimation("Attack");
		break;
	case EMonsterActionType::Die:
		m_Scene->CreateObject<CMonsterDestroyEffect>("MonsterDestroyEffect")->SetEffectInfo(Vector2(m_Body->GetWorldPos().x, m_Body->GetWorldPos().y + m_RedBat->GetWorldScale().y / 2.f));
		m_Scene->GetResource()->FindSound("MonsterDie")->Play();
		m_Scene->CreateObject<CGold>("Gold")->SetGoldInfo(m_Body->GetWorldPos());
		Destroy();
		break;
	}
}

CRedBat* CRedBat::Clone() const
{
	return new CRedBat(*this);
}