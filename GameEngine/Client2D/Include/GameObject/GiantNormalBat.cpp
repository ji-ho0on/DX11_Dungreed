#include "GiantNormalBat.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../Animation2D/GiantNormalBatAnimation.h"
#include "Scene/Scene.h"
#include "MonsterDestroyEffect.h"
#include "Component/GravityAgent.h"
#include "Gold.h"

CGiantNormalBat::CGiantNormalBat()
{
	SetTypeID<CGiantNormalBat>();

	m_ObjectTypeName = "GiantNormalBat";
}

CGiantNormalBat::CGiantNormalBat(const CGiantNormalBat& Obj) :
	CMonster(Obj)
{
	m_GiantNormalBat = (CSpriteComponent*)FindComponent("GiantNormalBat");

	m_DetectDistance = Obj.m_DetectDistance;
}

CGiantNormalBat::~CGiantNormalBat()
{
}

void CGiantNormalBat::Start()
{
	CMonster::Start();

	m_PlayerObject = m_Scene->GetSceneInfo()->GetPlayerObject();
}

bool CGiantNormalBat::Init()
{
	CMonster::Init();

	m_GiantNormalBat = CreateComponent<CSpriteComponent>("GiantNormalBat");
	m_GiantNormalBat->SetWorldScale(240.f, 120.f);
	m_GiantNormalBat->SetRenderLayerName("Monster");

	// Pivot 설정
	m_GiantNormalBat->SetPivot(0.5f, 0.f);

	m_Body->SetBoxSize(m_GiantNormalBat->GetWorldScale().x, m_GiantNormalBat->GetWorldScale().y);
	m_Body->SetWorldPosition(150.f, 300.f);

	m_GiantNormalBat->SetAnimation<CGiantNormalBatAnimation>("GiantNormalBatAnimation");

	m_Body->AddChild(m_GiantNormalBat);

	m_Gravity->SetPhysicsSimulate(false);

	m_HP = 80;

	m_DetectDistance = 1000.f;

	return true;
}

void CGiantNormalBat::Update(float DeltaTime)
{
	CMonster::Update(DeltaTime);

	if (m_Attacked)
		m_GiantNormalBat->GetMaterial(0)->SetBaseColor(1.f, 0.f, 0.f, 1.f);

	else
		m_GiantNormalBat->GetMaterial(0)->SetBaseColor(1.f, 1.f, 1.f, 1.f);

	// Scene에 Player가 있으면 Player 방향을 바라본다.
	if (m_PlayerObject)
	{
		// 감지거리 안에 있는 경우
		if (m_DetectDistance >= Vector2(m_PlayerObject->GetWorldPos().x, m_PlayerObject->GetWorldPos().y).Distance(GetWorldPos()))
		{
			// Player를 바라본다.
			if (m_PlayerObject->GetWorldPos().x - GetWorldPos().x > 0.f)
			{
				if (m_GiantNormalBat->GetDir() == EDirection::Left)
					m_GiantNormalBat->SetDir(EDirection::Right);
			}

			else
			{
				if (m_GiantNormalBat->GetDir() == EDirection::Right)
					m_GiantNormalBat->SetDir(EDirection::Left);
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
}

void CGiantNormalBat::PostUpdate(float DeltaTime)
{
	CMonster::PostUpdate(DeltaTime);

	switch (m_ActionType)
	{
	case EMonsterActionType::Idle:
		m_GiantNormalBat->GetAnimation()->ChangeAnimation("Idle");
		break;
	case EMonsterActionType::Move:
	break;
	case EMonsterActionType::Attack:
		m_GiantNormalBat->GetAnimation()->ChangeAnimation("Attack");
		break;
	case EMonsterActionType::Die:
		m_Scene->CreateObject<CMonsterDestroyEffect>("MonsterDestroyEffect")->SetEffectInfo(Vector2(m_Body->GetWorldPos().x, m_Body->GetWorldPos().y + m_GiantNormalBat->GetWorldScale().y / 2.f));
		m_Scene->GetResource()->FindSound("MonsterDie")->Play();
		m_Scene->CreateObject<CGold>("Gold")->SetGoldInfo(m_Body->GetWorldPos());
		Destroy();
		break;
	}
}

CGiantNormalBat* CGiantNormalBat::Clone() const
{
	return new CGiantNormalBat(*this);
}