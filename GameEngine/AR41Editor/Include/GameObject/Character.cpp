#include "Character.h"
#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/TargetArm.h"
#include "Component/ColliderBox2D.h"
#include "Component/GravityAgent.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Scene/CameraManager.h"
#include "Device.h"
#include "../Animation2D/CharacterAnimation.h"
#include "../UI/CharacterLTUI.h"
#include "../UI/CharacterLBUI.h"
#include "../UI/CharacterHitUI.h"
#include "ShortSwordEffect.h"
#include "JumpEffect.h"
#include "DustEffect.h"

CCharacter::CCharacter() :
	m_ShortSwordState(EShortSwordState::Up),
	m_Direction(EDirection::Right)
{
	SetTypeID<CCharacter>();

	m_ObjectTypeName = "Character";
}

CCharacter::CCharacter(const CCharacter& Obj) :
	CCreature(Obj)
{
	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_Character = (CSpriteComponent*)FindComponent("Character");
	m_Camera = (CCameraComponent*)FindComponent("Camera");
	m_Arm = (CTargetArm*)FindComponent("Arm");
	m_Gravity = (CGravityAgent*)FindComponent("Gravity");
	m_Weapon = (CSpriteComponent*)FindComponent("Weapon");

	m_Direction = Obj.m_Direction;
	m_CurrentWeapon = Obj.m_CurrentWeapon;
	m_EquippedWeapon1 = Obj.m_EquippedWeapon1;
	m_EquippedWeapon2 = Obj.m_EquippedWeapon2;

	m_ShortSwordAngle[(int)EShortSwordState::Up] = Obj.m_ShortSwordAngle[(int)EShortSwordState::Up];
	m_ShortSwordAngle[(int)EShortSwordState::Down] = Obj.m_ShortSwordAngle[(int)EShortSwordState::Down];
	m_ShortSwordState = Obj.m_ShortSwordState;

	m_Level = Obj.m_Level;
	m_HPMax = Obj.m_HPMax;
	m_Power = Obj.m_Power;
	m_Armor = Obj.m_Armor;
	m_DashCount = Obj.m_DashCount;
	m_Gold = Obj.m_Gold;
	m_Satiety = Obj.m_Satiety;
	m_SatietyMax = Obj.m_SatietyMax;

	m_IsDash = Obj.m_IsDash;
	m_DashTime = Obj.m_DashTime;
	m_DashCountCooldown = Obj.m_DashCountCooldown;
}

CCharacter::~CCharacter()
{
	CInput::GetInst()->DeleteBindFunction<CCharacter>("A", Input_Type::Push, this);
	CInput::GetInst()->DeleteBindFunction<CCharacter>("D", Input_Type::Push, this);

	CInput::GetInst()->DeleteBindFunction<CCharacter>("W", Input_Type::Push, this);
	CInput::GetInst()->DeleteBindFunction<CCharacter>("S", Input_Type::Push, this);
	CInput::GetInst()->DeleteBindFunction<CCharacter>("S", Input_Type::Up, this);

	CInput::GetInst()->DeleteBindFunction<CCharacter>("Space", Input_Type::Down, this);

	CInput::GetInst()->DeleteBindFunction<CCharacter>("LClick", Input_Type::Down, this);
	CInput::GetInst()->DeleteBindFunction<CCharacter>("RClick", Input_Type::Down, this);
}

void CCharacter::SetCharacterPosition(const Vector2& Position)
{
	m_Body->SetWorldPosition(Position);
	m_Gravity->SetFallStartY(Position.y);
}

int CCharacter::InflictDamage(int Damage)
{
	int _Damage = CCreature::InflictDamage(Damage);

	m_LTUI->SetHP(m_HP);

	m_Scene->GetResource()->FindSound("PlayerHit")->Play();

	return _Damage;
}

void CCharacter::AddGold(int Gold)
{
	m_Gold += Gold;

	m_LBUI->SetGold(m_Gold);

	m_Scene->GetResource()->FindSound("gold_collect")->Play();
}

void CCharacter::AddSatiety(int Satiety)
{
	m_Satiety += Satiety;

	m_LBUI->SetSatiety(m_Satiety);
}

void CCharacter::AddBindFunction()
{
	CInput::GetInst()->AddBindFunction<CCharacter>("A", Input_Type::Push, this, &CCharacter::LeftKey, m_Scene);
	CInput::GetInst()->AddBindFunction<CCharacter>("D", Input_Type::Push, this, &CCharacter::RightKey, m_Scene);

	CInput::GetInst()->AddBindFunction<CCharacter>("W", Input_Type::Push, this, &CCharacter::UpKey, m_Scene);
	CInput::GetInst()->AddBindFunction<CCharacter>("S", Input_Type::Push, this, &CCharacter::DownKey, m_Scene);
	CInput::GetInst()->AddBindFunction<CCharacter>("S", Input_Type::Up, this, &CCharacter::DownKeyCancel, m_Scene);

	CInput::GetInst()->AddBindFunction<CCharacter>("Space", Input_Type::Down, this, &CCharacter::Jump, m_Scene);

	CInput::GetInst()->AddBindFunction<CCharacter>("LClick", Input_Type::Down, this, &CCharacter::Attack, m_Scene);
	CInput::GetInst()->AddBindFunction<CCharacter>("RClick", Input_Type::Down, this, &CCharacter::Dash, m_Scene);
}

void CCharacter::DeleteBindFunction()
{
	CInput::GetInst()->DeleteBindFunction<CCharacter>("A", Input_Type::Push, this);
	CInput::GetInst()->DeleteBindFunction<CCharacter>("D", Input_Type::Push, this);

	CInput::GetInst()->DeleteBindFunction<CCharacter>("W", Input_Type::Push, this);
	CInput::GetInst()->DeleteBindFunction<CCharacter>("S", Input_Type::Push, this);
	CInput::GetInst()->DeleteBindFunction<CCharacter>("S", Input_Type::Up, this);

	CInput::GetInst()->DeleteBindFunction<CCharacter>("Space", Input_Type::Down, this);

	CInput::GetInst()->DeleteBindFunction<CCharacter>("LClick", Input_Type::Down, this);
	CInput::GetInst()->DeleteBindFunction<CCharacter>("RClick", Input_Type::Down, this);
}

void CCharacter::Start()
{
	CCreature::Start();

	if (m_Scene)
		m_Scene->GetCameraManager()->SetCurrentCamera(m_Camera);

	CInput::GetInst()->AddBindFunction<CCharacter>("A", Input_Type::Push, this, &CCharacter::LeftKey, m_Scene);
	CInput::GetInst()->AddBindFunction<CCharacter>("D", Input_Type::Push, this, &CCharacter::RightKey, m_Scene);

	CInput::GetInst()->AddBindFunction<CCharacter>("W", Input_Type::Push, this, &CCharacter::UpKey, m_Scene);
	CInput::GetInst()->AddBindFunction<CCharacter>("S", Input_Type::Push, this, &CCharacter::DownKey, m_Scene);
	CInput::GetInst()->AddBindFunction<CCharacter>("S", Input_Type::Up, this, &CCharacter::DownKeyCancel, m_Scene);

	CInput::GetInst()->AddBindFunction<CCharacter>("Space", Input_Type::Down, this, &CCharacter::Jump, m_Scene);

	CInput::GetInst()->AddBindFunction<CCharacter>("LClick", Input_Type::Down, this, &CCharacter::Attack, m_Scene);
	CInput::GetInst()->AddBindFunction<CCharacter>("RClick", Input_Type::Down, this, &CCharacter::Dash, m_Scene);

	m_LBUI = m_Scene->GetViewport()->CreateUIWindow<CCharacterLBUI>("CharacterLBUI");

	m_LBUI->SetGold(m_Gold);
	m_LBUI->SetSatiety(m_SatietyMax);
	m_LBUI->SetSatiety(m_Satiety);

	m_LTUI = m_Scene->GetViewport()->CreateUIWindow<CCharacterLTUI>("CharacterLTUI");

	m_LTUI->SetLevel(m_Level);
	m_LTUI->SetHPMax(m_HPMax);
	m_LTUI->SetHP(m_HP);
	m_LTUI->SetDashCount(m_DashCount);

	m_HitUI = m_Scene->GetViewport()->CreateUIWindow<CCharacterHitUI>("CharacterHitUI");
	m_HitUI->SetEnable(false);

	m_Scene->GetSceneInfo()->SetPlayerObject(this);
}

bool CCharacter::Init()
{
	CCreature::Init();

	// 충돌용 Box Collider 생성
	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Body->SetCollisionProfile("Player");


	m_Character = CreateComponent<CSpriteComponent>("Character");
	m_Character->SetAnimation<CCharacterAnimation>("CharacterAnimation");


	// 캐릭터 시점으로 잡아줄 Camera와 TargetArm 생성
	m_Camera = CreateComponent<CCameraComponent>("Camera");
	m_Arm = CreateComponent<CTargetArm>("Arm");

	// 중력을 적용시켜줄 GravityAgent 생성
	m_Gravity = CreateComponent<CGravityAgent>("Gravity");
	m_Gravity->SetGravityAccel(10.f);
	m_Gravity->SetJumpVelocity(50.f);
	m_Gravity->SetPhysicsSimulate(true);

	// 캐릭터가 사용할 무기 생성
	m_Weapon = CreateComponent<CSpriteComponent>("Weapon");
	m_Weapon->SetRenderLayerName("Weapon");
	m_Weapon->SetTexture("ShortSword", TEXT("MeleeWeapon/ShortSword.png"));
	m_Weapon->Set2DZOffset(-20.f);


	m_Body->AddChild(m_Character);

	m_Character->AddChild(m_Arm);
	m_Arm->AddChild(m_Camera);

	m_Character->AddChild(m_Weapon);



	Resolution RS = CDevice::GetInst()->GetResolution();

	float Width = (float)RS.Width / 2.f;
	float Height = (float)RS.Height / 2.f;

	// Camera의 Offset으로 화면의 절반을 주기위해 Device의 해상도를 받아와 절반을 Offset으로 설정
	m_Arm->SetTargetOffset(Vector3(-Width, -Height, 0.f));

	// RootComponent는 Relative로 하거나 World로 하거나 상관 없음
	// 화면에서의 위치와 크기를 조정
	m_Body->SetInheritScale(true);
	m_Body->SetWorldPosition(660.f, 128.f);
	m_Gravity->SetFallStartY(128.f);

	m_Weapon->SetInheritScale(false);
	m_Weapon->SetInheritRotZ(true);


	m_Character->SetInheritScale(true);
	m_Character->SetWorldScale(60.f, 80.f);
	m_Character->SetPivot(0.5f, 0.f);

	m_Body->SetBoxSize(m_Character->GetWorldScale().x / 2.f, m_Character->GetWorldScale().y);
	m_Body->SetPivot(0.5f, 0.f);

	m_Weapon->SetRelativePosition(m_Character->GetWorldScale().x / 4.f, m_Character->GetWorldScale().y / 2.f);
	m_Weapon->SetWorldScale(80.f, 25.f);
	m_Weapon->SetRelativeRotationZ(m_ShortSwordAngle[(int)m_ShortSwordState]);
	m_Weapon->SetPivot(0.f, 0.5f);


	m_EquippedWeapon1 = EWeaponType::ShortSword;
	m_EquippedWeapon2 = EWeaponType::CrossBow;

	m_ShortSwordAngle[(int)EShortSwordState::Up] = 100.f;
	m_ShortSwordAngle[(int)EShortSwordState::Down] = -100.f;

	m_Level = 1;
	m_HP = 100;
	m_HPMax = 100;
	m_Power = 30;
	m_Armor = 10;
	m_DashCount = 4;
	m_Gold = 0;
	m_Satiety = 0;
	m_SatietyMax = 100;
	
	m_IsDash = false;
	m_DashTime = 0.f;
	m_DashCountCooldown = 0.f;

	//m_Gravity->SetPhysicsSimulate(false);



	//////////////////////////////////////////////////////////////////////////////////////////
	// 캐릭터가 사용하는 Sound Load
	//////////////////////////////////////////////////////////////////////////////////////////
	if (m_Scene)
	{
		// ShortSword 휘두르는 소리
		m_Scene->GetResource()->LoadSound("Effect", "Swing1", false, "MeleeWeapon/Swing1.wav");

		// Dash 소리
		m_Scene->GetResource()->LoadSound("Effect", "Dash", false, "player/dash.wav");

		// Jump 소리
		m_Scene->GetResource()->LoadSound("Effect", "Jump", false, "player/Jumping.wav");

		// Step1 소리
		m_Scene->GetResource()->LoadSound("Effect", "step_lth1", false, "player/step_lth1.wav");

		// Step2 소리
		m_Scene->GetResource()->LoadSound("Effect", "step_lth2", false, "player/step_lth2.wav");

		// Step3 소리
		m_Scene->GetResource()->LoadSound("Effect", "step_lth3", false, "player/step_lth3.wav");

		// Step4 소리
		m_Scene->GetResource()->LoadSound("Effect", "step_lth4", false, "player/step_lth4.wav");

		// 피격 소리
		m_Scene->GetResource()->LoadSound("Effect", "PlayerHit", false, "player/Hit_Player.wav");

		// Gold 획득 소리
		m_Scene->GetResource()->LoadSound("Effect", "gold_collect", false, "player/gold_collect.wav");
	}

	else
	{
		// ShortSword 휘두르는 소리
		CResourceManager::GetInst()->LoadSound("Effect", "Swing1", false, "MeleeWeapon/Swing1.wav");

		// Dash 소리
		CResourceManager::GetInst()->LoadSound("Effect", "Dash", false, "player/dash.wav");

		// Jump 소리
		CResourceManager::GetInst()->LoadSound("Effect", "Jump", false, "player/Jumping.wav");

		// Step1 소리
		CResourceManager::GetInst()->LoadSound("Effect", "step_lth1", false, "player/step_lth1.wav");

		// Step2 소리
		CResourceManager::GetInst()->LoadSound("Effect", "step_lth2", false, "player/step_lth2.wav");

		// Step3 소리
		CResourceManager::GetInst()->LoadSound("Effect", "step_lth3", false, "player/step_lth3.wav");

		// Step4 소리
		CResourceManager::GetInst()->LoadSound("Effect", "step_lth4", false, "player/step_lth4.wav");

		// 피격 소리
		CResourceManager::GetInst()->LoadSound("Effect", "PlayerHit", false, "player/Hit_Player.wav");

		// Gold 획득 소리
		CResourceManager::GetInst()->LoadSound("Effect", "gold_collect", false, "player/gold_collect.wav");
	}



	return true;
}

void CCharacter::Update(float DeltaTime)
{
	CCreature::Update(DeltaTime);

	if (m_Attacked)
		m_HitUI->SetEnable(true);

	else
		m_HitUI->SetEnable(false);

	//////////////////////////////////////////////////////////////////////////////////////////
	// 캐릭터 위치를 기준으로 마우스가 있는 방향을 바라본다.
	//////////////////////////////////////////////////////////////////////////////////////////
	if (CInput::GetInst()->GetMouseWorldPos().x - GetWorldPos().x > 0.f)
	{
		// 현재 마우스가 오른쪽에 있는데 왼쪽을 바라보고 있었다면 방향 변경
		if (m_Direction == EDirection::Left)
		{
			m_Weapon->SetRelativePosition(m_Character->GetWorldScale().x / 4.f, m_Character->GetWorldScale().y / 2.f);
			m_Character->SetDir(EDirection::Right);
		}

		m_Direction = EDirection::Right;
	}

	else
	{
		// 현재 마우스가 왼쪽에 있는데 오른쪽을 바라보고 있었다면 방향 변경
		if (m_Direction == EDirection::Right)
		{
			m_Weapon->SetRelativePosition(-m_Character->GetWorldScale().x / 4.f, m_Character->GetWorldScale().y / 2.f);
			m_Character->SetDir(EDirection::Left);
		}

		m_Direction = EDirection::Left;
	}


	//////////////////////////////////////////////////////////////////////////////////////////
	// Character의 방향에 따라 MouseAngle 계산
	//////////////////////////////////////////////////////////////////////////////////////////
	if (m_Character->GetDir() == EDirection::Right)
		m_MouseAngleRight = Vector2(GetWorldPos().x, GetWorldPos().y + (GetWorldScale().y / 2.f)).Angle(CInput::GetInst()->GetMouseWorldPos());

	else
		m_MouseAngleLeft = Vector2(GetWorldPos().x, GetWorldPos().y + (GetWorldScale().y / 2.f)).Angle(CInput::GetInst()->GetMouseWorldPos());;

	//////////////////////////////////////////////////////////////////////////////////////////
	// DashCount가 충전을 위한 시간 증가
	//////////////////////////////////////////////////////////////////////////////////////////
	m_DashCountCooldown += DeltaTime;

	// DashCount 충전시간 2초
	if (m_DashCountCooldown >= 2.f)
	{
		m_DashCountCooldown -= 2.f;

		++m_DashCount;

		// 최대 DashCount = 4
		if (m_DashCount > 4)
			m_DashCount = 4;

		else
			m_LTUI->SetDashCount(m_DashCount);
	}

	//////////////////////////////////////////////////////////////////////////////////////////
	// Dash 상태라면 Dash 발동
	//////////////////////////////////////////////////////////////////////////////////////////
	if (m_IsDash)
	{
		m_DashTime += DeltaTime;
		
		m_Body->AddWorldPosition(m_DashDir * 2300.f * DeltaTime);

		if (m_DashTime > 0.1f)
		{
			m_Gravity->SetPhysicsSimulate(true);
			m_Gravity->SetGroundCheck(false);

			if (m_Gravity->IsJump())
			{
				m_Gravity->SetFallStartY(GetWorldPos().y);
				m_Gravity->SetJump(false);
				m_Gravity->SetFallTime(0.f);
			}

			else
			{
				m_Gravity->SetFallStartY(GetWorldPos().y);
				m_Gravity->SetFallTime(m_Gravity->GetFallTime() + m_DashTime);
			}

			m_DashTime = 0.f;
			m_IsDash = false;
		}
	}
}

void CCharacter::PostUpdate(float DeltaTime)
{
	CCreature::PostUpdate(DeltaTime);

	//////////////////////////////////////////////////////////////////////////////////////////
	// 무기의 각도를 바꿔준다. 방향에 따라도 달라짐
	//////////////////////////////////////////////////////////////////////////////////////////
	if (m_Character->GetDir() == EDirection::Right)
	{
		m_Weapon->SetRelativeRotationZ(m_MouseAngleRight);

		if (m_CurrentWeapon == EWeaponType::ShortSword)
		{
			m_Weapon->AddRelativeRotationZ(m_ShortSwordAngle[(int)m_ShortSwordState]);
		}
	}

	else
	{
		m_Weapon->SetRelativeRotationZ(m_MouseAngleLeft);

		if (m_CurrentWeapon == EWeaponType::ShortSword)
		{
			m_Weapon->AddRelativeRotationZ(-m_ShortSwordAngle[(int)m_ShortSwordState]);
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////
	// 캐릭터의 조건들에 따라 ActionType 변경
	//////////////////////////////////////////////////////////////////////////////////////////
	if(m_HP <= 0)
		m_ActionType = ECharacterActionType::Die;

	else if (!m_Gravity->IsGround() || m_IsDash)
	{
		m_ActionType = ECharacterActionType::Jump;
		m_StepTime = 0.f;
		m_StepCount = 0;
	}

	else if (m_Gravity->GetMove().x != 0.f && m_Gravity->IsGround())
		m_ActionType = ECharacterActionType::Run;

	else
	{
		m_ActionType = ECharacterActionType::Idle;
		m_StepTime = 0.f;
		m_StepCount = 0;
	}

	//////////////////////////////////////////////////////////////////////////////////////////
	// 캐릭터 Action에 따라 ActionType별로 ChangeAnimation
	//////////////////////////////////////////////////////////////////////////////////////////
	switch (m_ActionType)
	{
	case ECharacterActionType::Idle:
		m_Character->GetAnimation()->ChangeAnimation("CharacterIdle");
		break;
	case ECharacterActionType::Run:
	{
		m_Character->GetAnimation()->ChangeAnimation("CharacterRun");


		m_StepTime += DeltaTime;

 		if (m_StepTime >= 0.3f)
		{
			m_StepTime -= 0.3f;

			if (m_StepCount % 4 == 0)
			{
				m_Scene->GetResource()->FindSound("step_lth1")->Play();
			}

			else if (m_StepCount % 4 == 1)
			{
				m_Scene->GetResource()->FindSound("step_lth2")->Play();
			}

			else if (m_StepCount % 4 == 2)
			{
				m_Scene->GetResource()->FindSound("step_lth3")->Play();
			}

			else if (m_StepCount % 4 == 3)
			{
				m_Scene->GetResource()->FindSound("step_lth4")->Play();
			}

			++m_StepCount;

			CDustEffect* DustEffect = m_Scene->CreateObject<CDustEffect>("DustEffect");
			DustEffect->SetEffectInfo(GetWorldPos());
			DustEffect->SetEffectDir(m_Character->GetDir());
		}
	}
		break;
	case ECharacterActionType::Jump:
		m_Character->GetAnimation()->ChangeAnimation("CharacterJump");
		break;
	case ECharacterActionType::Die:
		m_Character->GetAnimation()->ChangeAnimation("CharacterDie");
		break;
	}
}

CCharacter* CCharacter::Clone() const
{
	return new CCharacter(*this);
}

void CCharacter::Save(FILE* File)
{
	CCreature::Save(File);
}

void CCharacter::Load(FILE* File)
{
	CCreature::Load(File);
}

void CCharacter::UpKey()
{
	if (!m_Gravity->IsJump())
	{
		m_Gravity->Jump();

		m_Scene->CreateObject<CJumpEffect>("JumpEffect")->SetEffectInfo(GetWorldPos());

		m_Scene->GetResource()->FindSound("Jump")->Play();
	}
}

void CCharacter::DownKey()
{
	m_DownKey = true;
}

void CCharacter::DownKeyCancel()
{
	m_DownKey = false;
}

void CCharacter::LeftKey()
{
	m_Body->AddWorldPosition(m_Character->GetWorldAxis(AXIS_X) * -300.f * g_DeltaTime);
}

void CCharacter::RightKey()
{
	m_Body->AddWorldPosition(m_Character->GetWorldAxis(AXIS_X) * 300.f * g_DeltaTime);
}

void CCharacter::Jump()
{
	if (!m_Gravity->IsJump())
	{
		if (m_DownKey)
		{
			m_Gravity->SetGroundCheck(true);
			m_Gravity->SetOneWayThrough(true);
		}

		else
		{
			m_Gravity->Jump();

			m_Scene->CreateObject<CJumpEffect>("JumpEffect")->SetEffectInfo(GetWorldPos());

			m_Scene->GetResource()->FindSound("Jump")->Play();
		}
	}
}

void CCharacter::Dash()
{
	if (m_IsDash || m_DashCount <= 0)
		return;

	m_Gravity->SetPhysicsSimulate(false);
	m_IsDash = true;
	--m_DashCount;
	m_LTUI->SetDashCount(m_DashCount);

	// Dash 방향 계산
	// 방향 = 마우스위치 - m_Character의 Position
	m_DashDir = Vector3(CInput::GetInst()->GetMouseWorldPos().x, CInput::GetInst()->GetMouseWorldPos().y, 0.f) - GetWorldPos();
	m_DashDir.Normalize();

	m_Gravity->SetOneWayThrough(true);

	m_Scene->GetResource()->FindSound("Dash")->Play();
 }

void CCharacter::Attack()
{
	// ShortSword일 때는 공격마다 m_ShortSwordAngle이 변해야함.
	if (m_ShortSwordState == EShortSwordState::Up)
		m_ShortSwordState = EShortSwordState::Down;

	else
		m_ShortSwordState = EShortSwordState::Up;

	// 공격시 검기 Effect 생성
	CShortSwordEffect* Effect = m_Scene->CreateObject<CShortSwordEffect>("ShortSwordEffect");

	if (m_Direction == EDirection::Right)
		Effect->SetEffectInfo(Vector2(m_Body->GetWorldPos().x + m_Character->GetWorldScale().x / 4.f, m_Body->GetWorldPos().y + m_Character->GetWorldScale().y / 2.f), m_MouseAngleRight);

	else
		Effect->SetEffectInfo(Vector2(m_Body->GetWorldPos().x - m_Character->GetWorldScale().x / 4.f, m_Body->GetWorldPos().y + m_Character->GetWorldScale().y / 2.f), m_MouseAngleLeft);

	// Sound 재생 추가 해야함
	m_Scene->GetResource()->FindSound("Swing1")->Play();
}
