#include "NormalBat.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../Animation2D/NormalBatAnimation.h"
#include "Scene/Scene.h"
#include "MonsterDestroyEffect.h"
#include "Component/GravityAgent.h"
#include "Gold.h"

CNormalBat::CNormalBat()	:
	m_MoveDirChangeTime(0.f)
{
	SetTypeID<CNormalBat>();

	m_ObjectTypeName = "NormalBat";
}

CNormalBat::CNormalBat(const CNormalBat& Obj) :
	CMonster(Obj)
{
	m_NormalBat = (CSpriteComponent*)FindComponent("NormalBat");

	m_DetectDistance = Obj.m_DetectDistance;
	m_MoveDirChangeTime = Obj.m_MoveDirChangeTime;
}

CNormalBat::~CNormalBat()
{
}

void CNormalBat::Start()
{
	CMonster::Start();

	m_PlayerObject = m_Scene->GetSceneInfo()->GetPlayerObject();
}

bool CNormalBat::Init()
{
	CMonster::Init();

	m_NormalBat = CreateComponent<CSpriteComponent>("NormalBat");
	m_NormalBat->SetWorldScale(90.f, 45.f);
	m_NormalBat->SetRenderLayerName("Monster");

	// Pivot 설정
	m_NormalBat->SetPivot(0.5f, 0.f);

	m_Body->SetBoxSize(m_NormalBat->GetWorldScale().x, m_NormalBat->GetWorldScale().y);
	m_Body->SetWorldPosition(150.f, 300.f);

	m_NormalBat->SetAnimation<CNormalBatAnimation>("NormalBatAnimation");

	m_Body->AddChild(m_NormalBat);

	m_Gravity->SetPhysicsSimulate(false);

	m_HP = 30;

	m_DetectDistance = 1000.f;

	return true;
}

void CNormalBat::Update(float DeltaTime)
{
	CMonster::Update(DeltaTime);

	if (m_Attacked)
		m_NormalBat->GetMaterial(0)->SetBaseColor(1.f, 0.f, 0.f, 1.f);

	else
		m_NormalBat->GetMaterial(0)->SetBaseColor(1.f, 1.f, 1.f, 1.f);

	// Scene에 Player가 있으면 Player 방향을 바라본다.
	if (m_PlayerObject)
	{
		// 감지거리 안에 있는 경우
		if (m_DetectDistance >= Vector2(m_PlayerObject->GetWorldPos().x, m_PlayerObject->GetWorldPos().y).Distance(GetWorldPos()))
		{
			// Player를 바라본다.
			if (m_PlayerObject->GetWorldPos().x - GetWorldPos().x > 0.f)
			{
				if (m_NormalBat->GetDir() == EDirection::Left)
					m_NormalBat->SetDir(EDirection::Right);
			}

			else
			{
				if (m_NormalBat->GetDir() == EDirection::Right)
					m_NormalBat->SetDir(EDirection::Left);
			}

			m_ActionType = EMonsterActionType::Move;
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

			ENormalBatMoveDir Dir = (ENormalBatMoveDir)(rand() % (int)ENormalBatMoveDir::End);

			switch (Dir)
			{
			case ENormalBatMoveDir::LT:
				m_MoveDir = Vector3(-1.f, 1.f, 0.f);
				break;
			case ENormalBatMoveDir::RT:
				m_MoveDir = Vector3(1.f, 1.f, 0.f);
				break;
			case ENormalBatMoveDir::LB:
				m_MoveDir = Vector3(-1.f, -1.f, 0.f);
				break;
			case ENormalBatMoveDir::RB:
				m_MoveDir = Vector3(1.f, -1.f, 0.f);
				break;
			}

			m_MoveDir.Normalize();
		}
	}
}

void CNormalBat::PostUpdate(float DeltaTime)
{
	CMonster::PostUpdate(DeltaTime);

	switch (m_ActionType)
	{
	case EMonsterActionType::Idle:
		m_NormalBat->GetAnimation()->ChangeAnimation("Idle");
		break;
	case EMonsterActionType::Move:
		m_NormalBat->GetAnimation()->ChangeAnimation("Idle");
		m_Body->AddWorldPosition(m_MoveDir * 50.f * DeltaTime);
		break;
	case EMonsterActionType::Attack:
		break;
	case EMonsterActionType::Die:
		m_Scene->CreateObject<CMonsterDestroyEffect>("MonsterDestroyEffect")->SetEffectInfo(Vector2(m_Body->GetWorldPos().x, m_Body->GetWorldPos().y + m_NormalBat->GetWorldScale().y / 2.f));
		m_Scene->GetResource()->FindSound("MonsterDie")->Play();
		m_Scene->CreateObject<CGold>("Gold")->SetGoldInfo(m_Body->GetWorldPos());
		Destroy();
		break;
	}
}

CNormalBat* CNormalBat::Clone() const
{
	return new CNormalBat(*this);
}