#include "SkelBow.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../Animation2D/SkelAnimation.h"
#include "../Animation2D/SkelBowAnimation.h"
#include "Scene/Scene.h"
#include "MonsterDestroyEffect.h"
#include "Gold.h"

CSkelBow::CSkelBow()
{
	SetTypeID<CSkelBow>();

	m_ObjectTypeName = "SkelBow";
}

CSkelBow::CSkelBow(const CSkelBow& Obj) :
	CMonster(Obj)
{
	m_Skel = (CSpriteComponent*)FindComponent("Skel");
	m_Bow = (CSpriteComponent*)FindComponent("Bow");

	m_DetectDistance = Obj.m_DetectDistance;
}

CSkelBow::~CSkelBow()
{
}

void CSkelBow::Start()
{
	CMonster::Start();

	m_PlayerObject = m_Scene->GetSceneInfo()->GetPlayerObject();
}

bool CSkelBow::Init()
{
	CMonster::Init();

	m_Skel = CreateComponent<CSpriteComponent>("Skel");
	m_Skel->SetWorldScale(60, 80.f);
	m_Skel->SetRenderLayerName("Monster");

	// Pivot 설정
	m_Skel->SetPivot(0.5f, 0.f);

	m_Body->SetBoxSize(m_Skel->GetWorldScale().x, m_Skel->GetWorldScale().y);
	m_Body->SetWorldPosition(200.f, 300.f);

	m_Skel->SetAnimation<CSkelAnimation>("SkelAnimation");

	m_Bow = CreateComponent<CSpriteComponent>("Bow");
	m_Bow->SetPivot(0.5f, 0.5f);
	m_Bow->SetInheritScale(false);
	m_Bow->SetInheritRotZ(true);
	m_Bow->SetWorldScale(60.f, 60.f);
	m_Bow->SetRelativePosition(20.f, 30.f);
	m_Bow->SetRenderLayerName("Weapon");
	m_Bow->Set2DZOffset(-150.f);

	m_Bow->SetAnimation<CSkelBowAnimation>("SkelBowAnimation");

	m_Body->AddChild(m_Skel);
	m_Body->AddChild(m_Bow);

	m_DetectDistance = 700.f;
	m_AttackTime = 0.f;

	m_HP = 40;

	return true;
}

void CSkelBow::Update(float DeltaTime)
{
	CMonster::Update(DeltaTime);

	if (m_Attacked)
		m_Skel->GetMaterial(0)->SetBaseColor(1.f, 0.f, 0.f, 1.f);

	else
		m_Skel->GetMaterial(0)->SetBaseColor(1.f, 1.f, 1.f, 1.f);

	if (m_AttackRange)
	{
		m_AttackTime += DeltaTime;

		if (m_AttackTime >= 2.f)
		{
			m_AttackRange = false;
			m_AttackTime = 0.f;
		}
	}

	// Scene에 Player가 있으면 Player 방향을 바라본다.
	else if (m_PlayerObject)
	{
		// 감지거리 안에 있는 경우
		if (m_DetectDistance >= Vector2(m_PlayerObject->GetWorldPos().x, m_PlayerObject->GetWorldPos().y).Distance(GetWorldPos()))
		{
			m_Detect = true;

			m_AttackAngle = Vector2(GetWorldPos().x, GetWorldPos().y).Angle(m_PlayerObject->GetWorldPos());

			m_AttackDir = m_PlayerObject->GetWorldPos() - GetWorldPos();
			m_AttackDir.Normalize();

			m_AttackWaitTime += DeltaTime;

			// 감지거리 안에서 2.5초가 지났다면 Attack이 되어야 한다.
			if (m_AttackWaitTime >= 2.5f)
			{
				m_AttackRange = true;
				m_AttackWaitTime = 0.f;
			}

			else
				m_AttackRange = false;
		}

		else
		{
			m_Detect = false;
			m_AttackRange = false;
			m_AttackWaitTime = 0.f;
		}
	}


	// 공격범위에 들어왔다면
	if (m_AttackRange)
	{
		// Plyaer를 공격한다.
		m_ActionType = EMonsterActionType::Attack;
	}

	// Player가 감지되었다면
	else if (m_Detect)
	{
		// Player를 바라본다.
		if (m_PlayerObject->GetWorldPos().x - GetWorldPos().x > 0.f)
		{
			m_Skel->SetDir(EDirection::Right);
			m_Bow->SetRelativePosition(20.f, 30.f);
		}

		else
		{
			m_Skel->SetDir(EDirection::Left);
			m_Bow->SetRelativePosition(-20.f, 30.f);
		}

		m_ActionType = EMonsterActionType::Idle;
	}

	else
		m_ActionType = EMonsterActionType::Idle;

	if (m_HP <= 0)
		m_ActionType = EMonsterActionType::Die;
}

void CSkelBow::PostUpdate(float DeltaTime)
{
	CMonster::PostUpdate(DeltaTime);

	// 활을 플레이어 방향으로 향한다.
	m_Bow->SetRelativeRotationZ(m_AttackAngle);


	switch (m_ActionType)
	{
	case EMonsterActionType::Idle:
		m_Skel->GetAnimation()->ChangeAnimation("Idle");
		m_Bow->GetAnimation()->ResetFrame();
		m_Bow->GetAnimation()->SetPlay(false);
		break;
	case EMonsterActionType::Move:
		m_Skel->GetAnimation()->ChangeAnimation("Move");
		m_Bow->GetAnimation()->ResetFrame();
		m_Bow->GetAnimation()->SetPlay(false);
		break;
	case EMonsterActionType::Attack:
		m_Skel->GetAnimation()->ChangeAnimation("Idle");
		m_Bow->GetAnimation()->SetPlay(true);
		break;
	case EMonsterActionType::Die:
		m_Scene->CreateObject<CMonsterDestroyEffect>("MonsterDestroyEffect")->SetEffectInfo(Vector2(m_Body->GetWorldPos().x, m_Body->GetWorldPos().y + m_Skel->GetWorldScale().y / 2.f));
		m_Scene->GetResource()->FindSound("MonsterDie")->Play();
		m_Scene->CreateObject<CGold>("Gold")->SetGoldInfo(m_Body->GetWorldPos());
		Destroy();
		break;
	}
}

CSkelBow* CSkelBow::Clone() const
{
	return new CSkelBow(*this);
}