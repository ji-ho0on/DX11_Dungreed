#include "Player2D.h"
#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/TargetArm.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderOBB2D.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderLine2D.h"
#include "Component/GravityAgent.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Scene/CameraManager.h"
#include "Device.h"
#include "Bullet.h"
#include "Resource/Material/Material.h"
#include "../Animation2D/CharacterAnimation.h"

CPlayer2D::CPlayer2D()
{
	SetTypeID<CPlayer2D>();

	m_ObjectTypeName = "Player2D";
}

CPlayer2D::CPlayer2D(const CPlayer2D& Obj) :
	CGameObject(Obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("Sprite");
	m_Body = (CColliderBox2D*)FindComponent("Body");
	//m_Body = (CColliderOBB2D*)FindComponent("Body");
	//m_Body = (CColliderSphere2D*)FindComponent("Body");
	//m_Line = (CColliderLine2D*)FindComponent("Line");
	//m_SpriteChild = (CSceneComponent*)FindComponent("SpriteChild");
	//m_SpriteChildChild = (CSpriteComponent*)FindComponent("SpriteChildChild");
	m_Camera = (CCameraComponent*)FindComponent("Camera");
	m_Arm = (CTargetArm*)FindComponent("Arm");
	m_Gravity = (CGravityAgent*)FindComponent("Gravity");
}

CPlayer2D::~CPlayer2D()
{
	CInput::GetInst()->DeleteBindFunction<CPlayer2D>("A", Input_Type::Push, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer2D>("D", Input_Type::Push, this);

	CInput::GetInst()->DeleteBindFunction<CPlayer2D>("W", Input_Type::Push, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer2D>("S", Input_Type::Push, this);

	CInput::GetInst()->DeleteBindFunction<CPlayer2D>("Space", Input_Type::Down, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer2D>("1", Input_Type::Down, this);
}

void CPlayer2D::Start()
{
	CGameObject::Start();

	if (m_Scene)
		m_Scene->GetCameraManager()->SetCurrentCamera(m_Camera);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("A", Input_Type::Push, this, &CPlayer2D::MoveLeft, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("D", Input_Type::Push, this, &CPlayer2D::MoveRight, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("W", Input_Type::Push, this, &CPlayer2D::MoveUp, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("S", Input_Type::Push, this, &CPlayer2D::MoveDown, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Space", Input_Type::Down, this, &CPlayer2D::Jump, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("1", Input_Type::Down, this, &CPlayer2D::Shotgun, m_Scene);
}

bool CPlayer2D::Init()
{
	CGameObject::Init();

	// GameObject���� ��¿� SpriteComponent�� ����
	// ó�� ������ Component�� RootComponent�� ������
	m_Sprite = CreateComponent<CSpriteComponent>("Sprite");

	// �浹�� Box Collider ����
	m_Body = CreateComponent<CColliderBox2D>("Body");
	//m_Body = CreateComponent<CColliderOBB2D>("Body");
	//m_Body = CreateComponent<CColliderSphere2D>("Body");
	m_Body->SetCollisionProfile("Player");

	//m_Line = CreateComponent<CColliderLine2D>("Line");
	//m_Line->SetCollisionProfile("Player");

	// SpriteChild�� SpriteComponent�� �ƴ϶� SceneComponent�� �����Ͽ� ȭ�鿡 ����� �ȵǰ� ���縸 �ϰԲ� ������
	//m_SpriteChild = CreateComponent<CSceneComponent>("SpriteChild");
	//m_SpriteChildChild = CreateComponent<CSpriteComponent>("SpriteChildChild");

	m_Camera = CreateComponent<CCameraComponent>("Camera");
	m_Arm = CreateComponent<CTargetArm>("Arm");

	// ChildComponent�� ����
	m_Sprite->AddChild(m_Body);
	//m_Sprite->AddChild(m_Line);
	//m_Sprite->AddChild(m_SpriteChild);
	//m_SpriteChild->AddChild(m_SpriteChildChild);

	// RootComponent�� Sprite�� Child�� Arm�� �����ϰ� �� Child�� Camera�� ����
	m_Sprite->AddChild(m_Arm);
	m_Arm->AddChild(m_Camera);

	Resolution RS = CDevice::GetInst()->GetResolution();

	float Width = (float)RS.Width / 2.f;
	float Height = (float)RS.Height / 2.f;

	// Camera�� Offset���� ȭ���� ������ �ֱ����� Device�� �ػ󵵸� �޾ƿ� ������ Offset���� ����
	m_Arm->SetTargetOffset(Vector3(-Width, -Height, 0.f));

	// RootComponent�� Relative�� �ϰų� World�� �ϰų� ��� ����
	// ȭ�鿡���� ��ġ�� ũ�⸦ ����
	m_Body->SetInheritScale(true);
	m_Body->SetInheritRotZ(true);

	//m_Line->SetInheritScale(true);
	//m_Line->SetInheritRotZ(true);
	//m_Line->SetRelativePosition(-50.f, 0.f);
	//m_Line->SetRelativeDestPoint(-50.f, 0.f);

	m_Sprite->SetWorldPosition(100.f, 300.f);
	m_Sprite->SetWorldScale(30.f, 40.f);


	// Pivot ����
	m_Sprite->SetPivot(0.5f, 0.f);

	// Sprite�� Child�� �����߱� ������ Sprite�� �������� ������� �Ÿ��� ������
	// Z�� ȸ���� ������ ������ ����
	//m_SpriteChild->SetRelativePosition(150.f, 0.f);
	//m_SpriteChild->SetInheritRotZ(true);
	//
	//m_SpriteChildChild->SetRelativeScale(50.f, 50.f);
	//m_SpriteChildChild->SetRelativePosition(100.f, 0.f);
	//m_SpriteChildChild->SetInheritRotZ(true);
	//m_SpriteChildChild->SetInheritScale(true);

	m_Body->SetBoxSize(30.f, 40.f);
	m_Body->SetPivot(0.5f, 0.f);
	//m_Body->SetRelativePositionY(m_Sprite->GetWorldScale().y / 2.f);
	//CMaterial* Material = m_Sprite->GetMaterial(0);

	// Material�� �̿��� BaseColor����
	//Material->SetBaseColorUnsignedChar(255, 0, 0, 255);
	//Material->SetOpacity(0.5f);
	//Material->SetRenderState("DepthDisable");

	m_Sprite->SetAnimation<CCharacterAnimation>("PlayerAnimation");

	m_Gravity = CreateComponent<CGravityAgent>("Gravity");
	m_Gravity->SetGravityAccel(10.f);
	m_Gravity->SetJumpVelocity(30.f);
	m_Gravity->SetFallStartY(m_Sprite->GetWorldPos().y);
	m_Gravity->SetPhysicsSimulate(true);
	
	return true;
}

void CPlayer2D::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CPlayer2D::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CPlayer2D* CPlayer2D::Clone() const
{
	return new CPlayer2D(*this);
}

void CPlayer2D::MoveUp()
{
	m_Sprite->AddWorldPosition(m_Sprite->GetWorldAxis(AXIS_Y) * 300.f * g_DeltaTime);
}

void CPlayer2D::MoveDown()
{
	m_Sprite->AddWorldPosition(m_Sprite->GetWorldAxis(AXIS_Y) * -300.f * g_DeltaTime);
}

void CPlayer2D::MoveLeft()
{
	m_Sprite->AddWorldPosition(m_Sprite->GetWorldAxis(AXIS_X) * -300.f * g_DeltaTime);
}

void CPlayer2D::MoveRight()
{
	m_Sprite->AddWorldPosition(m_Sprite->GetWorldAxis(AXIS_X) * 300.f * g_DeltaTime);
}

void CPlayer2D::Rotation()
{
	m_Sprite->AddWorldRotationZ(180.f * g_DeltaTime);
}

void CPlayer2D::RotationInv()
{
	m_Sprite->AddWorldRotationZ(-180.f * g_DeltaTime);
}

void CPlayer2D::Fire()
{
	CBullet* Bullet = m_Scene->CreateObject<CBullet>("Bullet");
	
	Bullet->SetWorldPosition(GetWorldPos());
	Bullet->SetWorldRotation(GetWorldRot());
	Bullet->SetCollisionProfileName("PlayerAttack");
}

void CPlayer2D::Shotgun()
{
	CBullet* Bullet1 = m_Scene->CreateObject<CBullet>("Bullet1");
	Bullet1->SetWorldPosition(GetWorldPos());
	Bullet1->SetWorldRotation(GetWorldRot());
	Bullet1->SetDistance(300.f);
	Bullet1->SetMoveSpeed(1000.f);
	Bullet1->SetCollisionProfileName("PlayerAttack");

	CBullet* Bullet2 = m_Scene->CreateObject<CBullet>("Bullet2");
	Bullet2->SetWorldPosition(GetWorldPos());
	Bullet2->SetWorldRotation(GetWorldRot());
	Bullet2->AddWorldRotationZ(30.f);
	Bullet2->SetDistance(300.f);
	Bullet2->SetMoveSpeed(1000.f);
	Bullet2->SetCollisionProfileName("PlayerAttack");

	CBullet* Bullet3 = m_Scene->CreateObject<CBullet>("Bullet3");
	Bullet3->SetWorldPosition(GetWorldPos());
	Bullet3->SetWorldRotation(GetWorldRot());
	Bullet3->AddWorldRotationZ(-30.f);
	Bullet3->SetDistance(300.f);
	Bullet3->SetMoveSpeed(1000.f);
	Bullet3->SetCollisionProfileName("PlayerAttack");
}

void CPlayer2D::Jump()
{
	m_Gravity->Jump();
}
