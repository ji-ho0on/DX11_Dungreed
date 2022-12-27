#include "Banshee.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../Animation2D/BansheeAnimation.h"
#include "Scene/Scene.h"
#include "MonsterDestroyEffect.h"
#include "Component/GravityAgent.h"
#include "Gold.h"

CBanshee::CBanshee()
{
	SetTypeID<CBanshee>();

	m_ObjectTypeName = "Banshee";
}

CBanshee::CBanshee(const CBanshee& Obj) :
	CMonster(Obj)
{
	m_Banshee = (CSpriteComponent*)FindComponent("Banshee");

	m_DetectDistance = Obj.m_DetectDistance;
}

CBanshee::~CBanshee()
{
}

void CBanshee::Start()
{
	CMonster::Start();

	m_PlayerObject = m_Scene->GetSceneInfo()->GetPlayerObject();
}

bool CBanshee::Init()
{
	CMonster::Init();

	m_Banshee = CreateComponent<CSpriteComponent>("Banshee");
	m_Banshee->SetWorldScale(60.f, 80.f);
	m_Banshee->SetRenderLayerName("Monster");

	// Pivot 설정
	m_Banshee->SetPivot(0.5f, 0.f);

	m_Body->SetBoxSize(m_Banshee->GetWorldScale().x, m_Banshee->GetWorldScale().y);
	m_Body->SetWorldPosition(150.f, 300.f);

	m_Banshee->SetAnimation<CBansheeAnimation>("BansheeAnimation");

	m_Body->AddChild(m_Banshee);

	m_Gravity->SetPhysicsSimulate(false);

	m_HP = 60;

	m_DetectDistance = 1000.f;

	return true;
}

void CBanshee::Update(float DeltaTime)
{
	CMonster::Update(DeltaTime);

	if (m_Attacked)
		m_Banshee->GetMaterial(0)->SetBaseColor(1.f, 0.f, 0.f, 1.f);

	else
		m_Banshee->GetMaterial(0)->SetBaseColor(1.f, 1.f, 1.f, 1.f);

	// Scene에 Player가 있으면 Player 방향을 바라본다.
	if (m_PlayerObject)
	{
		// 감지거리 안에 있는 경우
		if (m_DetectDistance >= Vector2(m_PlayerObject->GetWorldPos().x, m_PlayerObject->GetWorldPos().y).Distance(GetWorldPos()))
		{
			// Player를 바라본다.
			if (m_PlayerObject->GetWorldPos().x - GetWorldPos().x > 0.f)
			{
				if (m_Banshee->GetDir() == EDirection::Left)
					m_Banshee->SetDir(EDirection::Right);
			}

			else
			{
				if (m_Banshee->GetDir() == EDirection::Right)
					m_Banshee->SetDir(EDirection::Left);
			}

			m_AttackTime += DeltaTime;

			if (m_AttackTime >= 6.f)
			{
				m_ActionType = EMonsterActionType::Attack;
				m_AttackTime = 0.f;
			}
		}

		else
			m_ActionType = EMonsterActionType::Idle;
	}

	if (m_HP <= 0)
		m_ActionType = EMonsterActionType::Die;
}

void CBanshee::PostUpdate(float DeltaTime)
{
	CMonster::PostUpdate(DeltaTime);

	switch (m_ActionType)
	{
	case EMonsterActionType::Idle:
		m_Banshee->GetAnimation()->ChangeAnimation("Idle");
		break;
	case EMonsterActionType::Move:
		break;
	case EMonsterActionType::Attack:
		m_Banshee->GetAnimation()->ChangeAnimation("Attack");
		break;
	case EMonsterActionType::Die:
		m_Scene->CreateObject<CMonsterDestroyEffect>("MonsterDestroyEffect")->SetEffectInfo(Vector2(m_Body->GetWorldPos().x, m_Body->GetWorldPos().y + m_Banshee->GetWorldScale().y / 2.f));
		m_Scene->GetResource()->FindSound("MonsterDie")->Play();
		m_Scene->CreateObject<CGold>("Gold")->SetGoldInfo(m_Body->GetWorldPos());
		Destroy();
		break;
	}
}

CBanshee* CBanshee::Clone() const
{
	return new CBanshee(*this);
}