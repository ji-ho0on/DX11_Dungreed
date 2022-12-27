#include "Gold.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderSphere2D.h"
#include "Component/GravityAgent.h"
#include "../Animation2D/GoldAnimation.h"
#include "Character.h"
#include "Scene/Scene.h"

CGold::CGold()	:
	m_GoldAmount(10)
{
	SetTypeID<CGold>();

	m_ObjectTypeName = "Gold";
}

CGold::CGold(const CGold& Obj) :
	CGameObject(Obj)
{
	m_Body = (CColliderSphere2D*)FindComponent("Body");
	m_Gold = (CSpriteComponent*)FindComponent("Gold");
	m_Gravity = (CGravityAgent*)FindComponent("Gravity");

	m_GoldAmount = Obj.m_GoldAmount;
}

CGold::~CGold()
{
}

void CGold::SetGoldInfo(const Vector2& Position)
{
	m_Body->SetWorldPosition(Position);
	m_Gravity->SetFallStartY(Position.y);
	m_Gravity->Jump();
}

void CGold::Start()
{
	CGameObject::Start();

	m_Body->SetCollisionCallback<CGold>(ECollision_Result::Collision, this, &CGold::GoldCollision);

	m_GoldAmount = rand() % 100 + 1;
}

bool CGold::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderSphere2D>("Body");
	m_Body->SetCollisionProfile("MonsterAttack");
	m_Body->SetInheritScale(true);
	m_Body->SetPivot(0.f, 1.f);

	m_Gold = CreateComponent<CSpriteComponent>("Gold");
	m_Gold->SetAnimation<CGoldAnimation>("GoldAnimation");
	m_Gold->SetWorldScale(30.f, 30.f);
	m_Gold->SetRenderLayerName("Effect");
	m_Gold->SetPivot(0.5f, 1.f);

	m_Gravity = CreateComponent<CGravityAgent>("Gravity");
	m_Gravity->SetGravityAccel(10.f);
	m_Gravity->SetJumpVelocity(50.f);
	m_Gravity->SetPhysicsSimulate(true);

	m_Body->SetRadius(m_Gold->GetWorldScale().x / 2.f);

	m_Body->AddChild(m_Gold);

	m_Body->SetWorldPosition(300.f, 300.f);
	m_Gravity->SetFallStartY(300.f);


	//////////////////////////////////////////////////////////////////////////////////////////
	// Gold Sound Load
	//////////////////////////////////////////////////////////////////////////////////////////
	if (m_Scene)
	{
		m_Scene->GetResource()->LoadSound("Effect", "gold_collect", false, "player/gold_collect.wav");
	}

	else
	{
		CResourceManager::GetInst()->LoadSound("Effect", "gold_collect", false, "player/gold_collect.wav");
	}

	return true;
}

void CGold::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CGold::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CGold* CGold::Clone() const
{
	return new CGold(*this);
}

void CGold::GoldCollision(const CollisionResult& result)
{
	((CCharacter*)result.Dest->GetOwner())->AddGold(m_GoldAmount);

	Destroy();
}
