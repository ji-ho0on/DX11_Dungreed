#include "BelialLaser.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../Animation2D/BelialLaserAnimation.h"
#include "Scene/Scene.h"
#include "Character.h"

CBelialLaser::CBelialLaser()
{
	SetTypeID<CBelialLaser>();

	m_ObjectTypeName = "BelialLaser";
}

CBelialLaser::CBelialLaser(const CBelialLaser& Obj) :
	CGameObject(Obj)
{
	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_BelialLaserHead = (CSpriteComponent*)FindComponent("BelialLaserHead");
	m_BelialLaserBody1 = (CSpriteComponent*)FindComponent("BelialLaserBody1");
	m_BelialLaserBody2 = (CSpriteComponent*)FindComponent("BelialLaserBody2");
	m_BelialLaserBody3 = (CSpriteComponent*)FindComponent("BelialLaserBody3");
}

CBelialLaser::~CBelialLaser()
{
}

void CBelialLaser::SetLaserInfo(const Vector2& Position, bool IsRightHand)
{
	m_Body->SetWorldPosition(Position);
	m_Body->AddWorldPositionY(10.f);
	//m_Body->AddWorldPositionY(m_Body->GetBoxSize().y / 2.f);

	if (IsRightHand)
	{
		m_Body->AddWorldPositionX(-m_Body->GetBoxSize().x);

		m_BelialLaserHead->SetDir(EDirection::Left);
		m_BelialLaserBody1->SetDir(EDirection::Left);
		m_BelialLaserBody2->SetDir(EDirection::Left);
		m_BelialLaserBody3->SetDir(EDirection::Left);

		m_BelialLaserHead->SetRelativePositionX(900.f);
		m_BelialLaserBody1->SetRelativePositionX(600.f);
		m_BelialLaserBody2->SetRelativePositionX(300.f);
		m_BelialLaserBody3->SetRelativePositionX(0.f);

		//m_BelialLaserBody3->SetRelativePositionX(0.f);
		//m_BelialLaserBody2->SetRelativePositionX(m_BelialLaserBody3->GetWorldPos().x + m_BelialLaserBody3->GetWorldScale().x);
		//m_BelialLaserBody1->SetRelativePositionX(m_BelialLaserBody2->GetWorldPos().x + m_BelialLaserBody2->GetWorldScale().x);
		//m_BelialLaserHead->SetRelativePositionX(m_BelialLaserBody1->GetWorldPos().x + m_BelialLaserBody1->GetWorldScale().x);
	}
}

void CBelialLaser::Start()
{
	CGameObject::Start();

	m_Body->SetCollisionCallback<CBelialLaser>(ECollision_Result::Collision, this, &CBelialLaser::AttackCollision);
}

bool CBelialLaser::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Body->SetCollisionProfile("MonsterAttack");
	m_Body->SetInheritScale(true);
	//m_Body->SetPivot(0.f, 0.5f);

	m_BelialLaserHead = CreateComponent<CSpriteComponent>("BelialLaserHead");
	m_BelialLaserHead->SetAnimation<CBelialLaserAnimation>("BelialLaserAnimation");
	m_BelialLaserHead->SetWorldScale(300.f, 176.f);
	m_BelialLaserHead->SetRenderLayerName("Effect");
	//m_BelialLaserHead->SetPivot(0.f, 0.5f);

	m_BelialLaserBody1 = CreateComponent<CSpriteComponent>("BelialLaserBody1");
	m_BelialLaserBody1->SetAnimation<CBelialLaserAnimation>("BelialLaserAnimation")->ChangeAnimation("Body");
	m_BelialLaserBody1->SetWorldScale(300.f, 204.f);
	m_BelialLaserBody1->SetRelativePositionY(-12.f);
	m_BelialLaserBody1->SetRelativePositionX(m_BelialLaserHead->GetWorldPos().x + m_BelialLaserHead->GetWorldScale().x);
	m_BelialLaserBody1->SetRenderLayerName("Effect");
	//m_BelialLaserBody1->SetPivot(0.f, 0.5f);

	m_BelialLaserBody2 = CreateComponent<CSpriteComponent>("BelialLaserBody2");
	m_BelialLaserBody2->SetAnimation<CBelialLaserAnimation>("BelialLaserAnimation")->ChangeAnimation("Body");
	m_BelialLaserBody2->SetWorldScale(300.f, 204.f);
	m_BelialLaserBody2->SetRelativePositionY(-12.f);
	m_BelialLaserBody2->SetRelativePositionX(m_BelialLaserBody1->GetWorldPos().x + m_BelialLaserBody1->GetWorldScale().x);
	m_BelialLaserBody2->SetRenderLayerName("Effect");
	//m_BelialLaserBody2->SetPivot(0.f, 0.5f);

	m_BelialLaserBody3 = CreateComponent<CSpriteComponent>("BelialLaserBody3");
	m_BelialLaserBody3->SetAnimation<CBelialLaserAnimation>("BelialLaserAnimation")->ChangeAnimation("Body");
	m_BelialLaserBody3->SetWorldScale(300.f, 204.f);
	m_BelialLaserBody3->SetRelativePositionY(-12.f);
	m_BelialLaserBody3->SetRelativePositionX(m_BelialLaserBody2->GetWorldPos().x + m_BelialLaserBody2->GetWorldScale().x);
	m_BelialLaserBody3->SetRenderLayerName("Effect");
	//m_BelialLaserBody3->SetPivot(0.f, 0.5f);

	m_Body->SetBoxSize(m_BelialLaserHead->GetWorldScale().x + m_BelialLaserBody1->GetWorldScale().x * 3.f, m_BelialLaserHead->GetWorldScale().y);

	m_Body->AddChild(m_BelialLaserHead);
	m_Body->AddChild(m_BelialLaserBody1);
	m_Body->AddChild(m_BelialLaserBody2);
	m_Body->AddChild(m_BelialLaserBody3);

	// 임시
	m_Body->SetWorldPosition(200.f, 300.f);


	return true;
}

void CBelialLaser::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBelialLaser::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBelialLaser* CBelialLaser::Clone() const
{
	return new CBelialLaser(*this);
}

void CBelialLaser::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CBelialLaser::Load(FILE* File)
{
	CGameObject::Load(File);
}

void CBelialLaser::AttackCollision(const CollisionResult& Result)
{
	// 캐릭터에게 데미지를 준다.
	((CCharacter*)Result.Dest->GetOwner())->InflictDamage(9);
}
