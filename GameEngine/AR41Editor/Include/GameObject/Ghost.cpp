#include "Ghost.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../Animation2D/GhostAnimation.h"
#include "Scene/Scene.h"
#include "MonsterDestroyEffect.h"
#include "Component/GravityAgent.h"
#include "Character.h"
#include "Gold.h"

CGhost::CGhost()
{
	SetTypeID<CGhost>();

	m_ObjectTypeName = "Ghost";
}

CGhost::CGhost(const CGhost& Obj) :
	CMonster(Obj)
{
	m_Ghost = (CSpriteComponent*)FindComponent("Ghost");

	m_DetectDistance = Obj.m_DetectDistance;
	m_AttackWaitTime = Obj.m_AttackWaitTime;
	m_Attack = Obj.m_Attack;
	m_AttackTime = Obj.m_AttackTime;
	m_MoveSpeed = Obj.m_MoveSpeed;
}

CGhost::~CGhost()
{
}

void CGhost::Start()
{
	CMonster::Start();

	m_PlayerObject = m_Scene->GetSceneInfo()->GetPlayerObject();

	m_Body->SetCollisionCallback<CGhost>(ECollision_Result::Collision, this, &CGhost::AttackCollision);
}

bool CGhost::Init()
{
	CMonster::Init();

	m_Ghost = CreateComponent<CSpriteComponent>("Ghost");
	m_Ghost->SetWorldScale(60.f, 60.f);
	m_Ghost->SetRenderLayerName("Monster");

	// Pivot 설정
	m_Ghost->SetPivot(0.5f, 0.f);

	m_Body->SetBoxSize(m_Ghost->GetWorldScale().x, m_Ghost->GetWorldScale().y);
	m_Body->SetWorldPosition(150.f, 300.f);

	m_Ghost->SetAnimation<CGhostAnimation>("GhostAnimation");

	m_Body->AddChild(m_Ghost);

	// GravityAgnet가 없어야함.
	DeleteObjectComponent(m_Gravity);

	m_HP = 20;

	m_DetectDistance = 1000.f;

	m_ActionType = EMonsterActionType::Move;

	m_MoveSpeed = 80.f;

	return true;
}

void CGhost::Update(float DeltaTime)
{
	CMonster::Update(DeltaTime);

	if (m_Attacked)
		m_Ghost->GetMaterial(0)->SetBaseColor(1.f, 0.f, 0.f, 1.f);

	else
		m_Ghost->GetMaterial(0)->SetBaseColor(1.f, 1.f, 1.f, 1.f);

	// Scene에 Player가 있으면 Player 방향을 바라본다.
	if (m_PlayerObject)
	{
		// 감지거리 안에 있는 경우
		if (m_DetectDistance >= Vector2(m_PlayerObject->GetWorldPos().x, m_PlayerObject->GetWorldPos().y).Distance(GetWorldPos()))
		{
			// Player를 바라본다.
			if (m_PlayerObject->GetWorldPos().x - GetWorldPos().x > 0.f)
			{
				if (m_Ghost->GetDir() == EDirection::Left)
					m_Ghost->SetDir(EDirection::Right);
			}

			else
			{
				if (m_Ghost->GetDir() == EDirection::Right)
					m_Ghost->SetDir(EDirection::Left);
			}

			m_AttackDir = m_PlayerObject->GetWorldPos() - GetWorldPos();
			m_AttackDir.Normalize();

			m_AttackWaitTime += DeltaTime;

			if (m_AttackWaitTime >= 4.f)
			{
				m_ActionType = EMonsterActionType::Attack;
				m_AttackWaitTime = 0.f;
				m_Attack = true;
				m_MoveSpeed = 200.f;
			}
		}

		else
			m_ActionType = EMonsterActionType::Idle;
	}

	if (m_HP <= 0)
		m_ActionType = EMonsterActionType::Die;

	else if (m_Attack)
	{
		m_AttackTime += DeltaTime;

		if (m_AttackTime >= 1.f)
		{
			m_AttackTime = 0.f;
			m_Attack = false;
			m_MoveSpeed = 80.f;
			m_ActionType = EMonsterActionType::Move;
		}
	}
}

void CGhost::PostUpdate(float DeltaTime)
{
	CMonster::PostUpdate(DeltaTime);

	switch (m_ActionType)
	{
	case EMonsterActionType::Idle:
		m_Ghost->GetAnimation()->ChangeAnimation("Idle");
		break;
	case EMonsterActionType::Move:
		m_Ghost->GetAnimation()->ChangeAnimation("Idle");
		m_Body->AddWorldPosition(m_AttackDir * m_MoveSpeed * DeltaTime);
		break;
	case EMonsterActionType::Attack:
		m_Ghost->GetAnimation()->ChangeAnimation("Attack");
		m_Body->AddWorldPosition(m_AttackDir * m_MoveSpeed * DeltaTime);
		break;
	case EMonsterActionType::Die:
		m_Scene->CreateObject<CMonsterDestroyEffect>("MonsterDestroyEffect")->SetEffectInfo(Vector2(m_Body->GetWorldPos().x, m_Body->GetWorldPos().y + m_Ghost->GetWorldScale().y / 2.f));
		m_Scene->GetResource()->FindSound("MonsterDie")->Play();
		m_Scene->CreateObject<CGold>("Gold")->SetGoldInfo(m_Body->GetWorldPos());
		Destroy();
		break;
	}
}

CGhost* CGhost::Clone() const
{
	return new CGhost(*this);
}

void CGhost::AttackCollision(const CollisionResult& Result)
{
	if (m_Attack)
	{
		// 캐릭터에게 데미지를 준다.
		if (Result.Dest->GetOwner()->CheckTypeID<CCharacter>())
			((CCharacter*)Result.Dest->GetOwner())->InflictDamage(5);
	}
}
