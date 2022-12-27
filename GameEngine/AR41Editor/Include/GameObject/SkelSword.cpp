#include "SkelSword.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../Animation2D/SkelAnimation.h"
#include "../Animation2D/SkelSwordAnimation.h"
#include "Scene/Scene.h"
#include "MonsterDestroyEffect.h"
#include "Gold.h"

CSkelSword::CSkelSword()
{
	SetTypeID<CSkelSword>();

	m_ObjectTypeName = "SkelSword";
}

CSkelSword::CSkelSword(const CSkelSword& Obj) :
	CMonster(Obj)
{
	m_Skel = (CSpriteComponent*)FindComponent("Skel");
	m_Sword = (CSpriteComponent*)FindComponent("Sword");

	m_DetectDistance = Obj.m_DetectDistance;
	m_AttackDistance = Obj.m_AttackDistance;
}

CSkelSword::~CSkelSword()
{
}

void CSkelSword::Start()
{
	CMonster::Start();

	m_PlayerObject = m_Scene->GetSceneInfo()->GetPlayerObject();
}

bool CSkelSword::Init()
{
	CMonster::Init();

	m_Skel = CreateComponent<CSpriteComponent>("Skel");
	m_Skel->SetWorldScale(60.f, 80.f);
	m_Skel->SetRenderLayerName("Monster");

	// Pivot 설정
	m_Skel->SetPivot(0.5f, 0.f);

	m_Body->SetBoxSize(m_Skel->GetWorldScale().x, m_Skel->GetWorldScale().y);
	m_Body->SetWorldPosition(200.f, 300.f);

	m_Skel->SetAnimation<CSkelAnimation>("SkelAnimation");

	m_Sword = CreateComponent<CSpriteComponent>("Sword");
	m_Sword->SetPivot(0.5f, 0.5f);
	m_Sword->SetInheritScale(false);
	m_Sword->SetWorldScale(160.f, 200.f);
	m_Sword->SetRelativePosition(50.f, 35.f);
	m_Sword->SetRenderLayerName("Monster");

	m_Sword->SetAnimation<CSkelSwordAnimation>("SkelSwordAnimation");

	m_Body->AddChild(m_Skel);
	m_Body->AddChild(m_Sword);

	m_DetectDistance = 300.f;
	m_AttackDistance = 50.f;
	m_AttackTime = 0.f;

	m_HP = 50;

	return true;
}

void CSkelSword::Update(float DeltaTime)
{
	CMonster::Update(DeltaTime);

	if (m_Attacked)
		m_Skel->GetMaterial(0)->SetBaseColor(1.f, 0.f, 0.f, 1.f);

	else
		m_Skel->GetMaterial(0)->SetBaseColor(1.f, 1.f, 1.f, 1.f);


	if (m_AttackRange)
	{
		m_AttackTime += DeltaTime;

		if (m_AttackTime >= 1.f)
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

			// 감지거리 안에서 공격범위에 들어온 경우
			if (m_AttackDistance >= Vector2(m_PlayerObject->GetWorldPos().x, m_PlayerObject->GetWorldPos().y).Distance(GetWorldPos()))
				m_AttackRange = true;

			else
				m_AttackRange = false;
		}

		else
		{
			m_Detect = false;
			m_AttackRange = false;
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
			m_Sword->SetDir(EDirection::Right);
			m_Sword->SetRelativePosition(50.f, 35.f);
		}

		else
		{
			m_Skel->SetDir(EDirection::Left);
			m_Sword->SetDir(EDirection::Left);
			m_Sword->SetRelativePosition(-50.f, 35.f);
		}

		// Player를 따라간다.
		m_ActionType = EMonsterActionType::Move;

		if (m_Skel->GetDir() == EDirection::Right)
			m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * m_Speed * g_DeltaTime);

		else
			m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * -m_Speed * g_DeltaTime);
	}

	else
		m_ActionType = EMonsterActionType::Idle;


	if (m_HP <= 0)
		m_ActionType = EMonsterActionType::Die;
}

void CSkelSword::PostUpdate(float DeltaTime)
{
	CMonster::PostUpdate(DeltaTime);

	switch (m_ActionType)
	{
	case EMonsterActionType::Idle:
		m_Skel->GetAnimation()->ChangeAnimation("Idle");
		m_Sword->GetAnimation()->ResetFrame();
		m_Sword->GetAnimation()->SetPlay(false);
		break;
	case EMonsterActionType::Move:
		m_Skel->GetAnimation()->ChangeAnimation("Move");
		m_Sword->GetAnimation()->ResetFrame();
		m_Sword->GetAnimation()->SetPlay(false);
		break;
	case EMonsterActionType::Attack:
		m_Skel->GetAnimation()->ChangeAnimation("Idle");
		m_Sword->GetAnimation()->SetPlay(true);
		//m_Scene->GetResource()->FindSound("Swish")->Play();
		break;
	case EMonsterActionType::Die:
		m_Scene->CreateObject<CMonsterDestroyEffect>("MonsterDestroyEffect")->SetEffectInfo(Vector2(m_Body->GetWorldPos().x, m_Body->GetWorldPos().y + m_Skel->GetWorldScale().y / 2.f));
		m_Scene->GetResource()->FindSound("MonsterDie")->Play();
		m_Scene->CreateObject<CGold>("Gold")->SetGoldInfo(m_Body->GetWorldPos());
		Destroy();
		break;
	}
}

CSkelSword* CSkelSword::Clone() const
{
	return new CSkelSword(*this);
}