#include "Belial.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../Animation2D/BelialHeadAnimation.h"
#include "../Animation2D/BelialHandAnimation.h"
#include "../Animation2D/BelialBackAnimation.h"
#include "Scene/Scene.h"
#include "BelialBullet.h"
#include "BelialSword.h"
#include "../UI/BossUI.h"
#include "Component/TargetArm.h"
#include "Component/CameraComponent.h"
#include "Device.h"
#include "Character.h"
#include "MonsterDestroyEffect.h"
#include "EndingPortal.h"

CBelial::CBelial() :
	m_Attack(false),
	m_AttackDelay(0.f),
	m_ActionType(EBelialActionType::Idle),
	m_SelectLaserAttackCount(false),
	m_LaserAttackCount(0),
	m_LaserAttackDelay(0.f),
	m_BulletAttackTime(0.f),
	m_BulletAttackCount(30),
	m_BulletAngle(0.f),
	m_BulletClockwise(true),
	m_SwordAttackTime(0.f),
	m_SwordAttackCount(6),
	m_BossStart(false),
	m_CameraStart(false),
	m_CameraTime(0.f),
	m_DieMotion(true),
	m_DieMotionTime(0.f),
	m_DestroyEffectTime(0.f),
	m_DestroyEffectCount(0),
	m_DestroyEffectDistance(0.f),
	m_DieEnd(false)

{
	SetTypeID<CBelial>();

	m_ObjectTypeName = "Belial";
}

CBelial::CBelial(const CBelial& Obj) :
	CCreature(Obj)
{
	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_BelialHead = (CSpriteComponent*)FindComponent("BelialHead");
	m_BelialBack = (CSpriteComponent*)FindComponent("BelialBack");
	m_BelialLeftHand = (CSpriteComponent*)FindComponent("BelialLeftHand");
	m_BelialRightHand = (CSpriteComponent*)FindComponent("BelialRightHand");
	m_BelialDeadHead = (CSpriteComponent*)FindComponent("BelialDeadHead");
	m_BelialDeadMouth = (CSpriteComponent*)FindComponent("BelialDeadMouth");

	m_Attack = Obj.m_Attack;
	m_AttackDelay = Obj.m_AttackDelay;
	m_ActionType = Obj.m_ActionType;

	m_SelectLaserAttackCount = Obj.m_SelectLaserAttackCount;
	m_LaserAttackCount = Obj.m_LaserAttackCount;
	m_LaserAttackDelay = Obj.m_LaserAttackDelay;

	m_BulletAttackTime = Obj.m_BulletAttackTime;
	m_BulletAttackCount = Obj.m_BulletAttackCount;
	m_BulletSummonPosition = Obj.m_BulletSummonPosition;
	m_BulletAngle = Obj.m_BulletAngle;
	m_BulletClockwise = Obj.m_BulletClockwise;

	m_SwordAttackTime = Obj.m_SwordAttackTime;
	m_SwordAttackCount = Obj.m_SwordAttackCount;
	m_SwordSummonPosition = Obj.m_SwordSummonPosition;
}

CBelial::~CBelial()
{
}

void CBelial::SetBossStart()
{
	m_BossStart = true;

	m_CameraStart = true;

	m_BellialHPUI->SetEnable(true);

	m_Scene->GetResource()->FindSound("ambience_prison")->Stop();

	m_Scene->GetResource()->FindSound("BelialLaugh")->Play();

	m_Scene->GetResource()->FindSound("JailBoss")->Play();

	m_Scene->GetCameraManager()->SetCurrentCamera(m_BelialCamera);

	((CCharacter*)m_PlayerObject.Get())->DeleteBindFunction();
}

int CBelial::InflictDamage(int Damage)
{
	int _Damage = CCreature::InflictDamage(Damage);

	m_Scene->GetResource()->FindSound("MonsterHit")->Play();

	m_BellialHPUI->SetHP(m_HP);

	if (m_HP <= 0)
	{
		m_Body->SetEnable(false);

		m_Scene->GetResource()->FindSound("JailBoss")->Stop();

		m_BellialHPUI->SetEnable(false);

		m_Scene->GetCameraManager()->SetCurrentCamera(m_BelialCamera);

		((CCharacter*)m_PlayerObject.Get())->DeleteBindFunction();
	}

	return _Damage;
}

void CBelial::Start()
{
	CCreature::Start();

	m_PlayerObject = m_Scene->GetSceneInfo()->GetPlayerObject();

	m_BellialHPUI = m_Scene->GetViewport()->CreateUIWindow<CBossUI>("BelialHPUI");
	m_BellialHPUI->SetHPMax(m_HP);
	m_BellialHPUI->SetEnable(false);
}

bool CBelial::Init()
{
	CCreature::Init();

	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Body->SetCollisionProfile("Monster");
	m_Body->SetInheritScale(true);
	m_Body->SetPivot(0.5f, 0.f);


	m_BelialHead = CreateComponent<CSpriteComponent>("BelialHead");
	m_BelialHead->SetAnimation<CBelialHeadAnimation>("BelialHeadAnimation");
	m_BelialHead->SetRenderLayerName("Monster");
	m_BelialHead->Set2DZOffset(400.f);
	m_BelialHead->SetInheritScale(true);
	m_BelialHead->SetWorldScale(280.f, 384.f);
	m_BelialHead->SetPivot(0.5f, 0.f);

	m_Body->SetBoxSize(m_BelialHead->GetWorldScale().x, m_BelialHead->GetWorldScale().y);

	m_BelialBack = CreateComponent<CSpriteComponent>("BelialBack");
	m_BelialBack->SetAnimation<CBelialBackAnimation>("BelialBackAnimation");
	m_BelialBack->SetWorldScale(200.f, 200.f);
	m_BelialBack->SetRelativePosition(25.f, 10.f);
	m_BelialBack->SetPivot(0.5f, 0.f);
	m_BelialBack->SetRenderLayerName("Monster");
	m_BelialBack->Set2DZOffset(400.f);

	m_BelialLeftHand = CreateComponent<CSpriteComponent>("BelialLeftHand");
	m_BelialLeftHand->SetAnimation<CBelialHandAnimation>("BelialHandAnimation");
	m_BelialLeftHand->SetWorldScale(228.f, 268.f);
	m_BelialLeftHand->SetRelativePosition(-400.f, -85.f);
	m_BelialLeftHand->SetPivot(0.5f, 0.f);
	m_BelialLeftHand->SetRenderLayerName("Monster");
	m_BelialLeftHand->Set2DZOffset(200.f);

	m_BelialRightHand = CreateComponent<CSpriteComponent>("BelialRightHand");
	m_BelialRightHand->SetAnimation<CBelialHandAnimation>("BelialHandAnimation");
	m_BelialRightHand->SetWorldScale(228.f, 268.f);
	m_BelialRightHand->SetRelativePosition(460.f, 140.f);
	m_BelialRightHand->SetPivot(0.5f, 0.f);
	m_BelialRightHand->SetRenderLayerName("Monster");
	m_BelialRightHand->SetDir(EDirection::Left);
	m_BelialRightHand->Set2DZOffset(200.f);

	m_BelialDeadHead = CreateComponent<CSpriteComponent>("BelialDeadHead");
	m_BelialDeadHead->SetTexture("BelialDead_head", TEXT("boss/Belial/Dead/BelialDead_head.png"));
	m_BelialDeadHead->SetWorldScale(280.f, 308.f);
	m_BelialDeadHead->SetRelativePositionY(76.f);
	m_BelialDeadHead->SetPivot(0.5f, 0.f);
	m_BelialDeadHead->SetRenderLayerName("Monster");
	m_BelialDeadHead->Set2DZOffset(400.f);
	m_BelialDeadHead->SetEnable(false);

	m_BelialDeadMouth = CreateComponent<CSpriteComponent>("BelialDeadMouth");
	m_BelialDeadMouth->SetTexture("BelialDead_mouth", TEXT("boss/Belial/Dead/BelialDead_mouth.png"));
	m_BelialDeadMouth->SetWorldScale(196.f, 124.f);
	m_BelialDeadMouth->SetRelativePositionX(30.f);
	m_BelialDeadMouth->SetPivot(0.5f, 0.f);
	m_BelialDeadMouth->SetRenderLayerName("Monster");
	m_BelialDeadMouth->Set2DZOffset(400.f);
	m_BelialDeadMouth->SetEnable(false);


	m_BelialCamera = CreateComponent<CCameraComponent>("BelialCamera");
	m_BelialTargetArm = CreateComponent<CTargetArm>("BelialTargetArm");

	Resolution RS = CDevice::GetInst()->GetResolution();

	float Width = (float)RS.Width / 2.f;
	float Height = (float)RS.Height / 2.f;

	m_BelialTargetArm->SetTargetOffset(Vector3(-Width, -Height + 150.f, 0.f));





	m_Body->AddChild(m_BelialHead);
	m_Body->AddChild(m_BelialBack);
	m_Body->AddChild(m_BelialLeftHand);
	m_Body->AddChild(m_BelialRightHand);
	m_Body->AddChild(m_BelialDeadHead);
	m_Body->AddChild(m_BelialDeadMouth);
	m_Body->AddChild(m_BelialTargetArm);
	m_BelialTargetArm->AddChild(m_BelialCamera);

	m_Body->SetWorldPosition(673.f, 420.f);

	srand((unsigned int)time(0));

	int Random = rand();

	m_BulletSummonPosition = m_BelialBack->GetWorldPos();
	m_BulletSummonPosition.y += m_BelialBack->GetWorldScale().y / 2.f;

	m_BulletClockwise = rand() % 2;

	m_SwordSummonPosition = Vector2(m_BelialBack->GetWorldPos().x - 360.f, m_BelialBack->GetWorldPos().y + 500.f);

	m_HP = 600;


	//////////////////////////////////////////////////////////////////////////////////////////
	// Belial 사용하는 Sound Load
	//////////////////////////////////////////////////////////////////////////////////////////
	if (m_Scene)
	{
		// 피격 소리
		m_Scene->GetResource()->LoadSound("Effect", "MonsterHit", false, "enemy/public/Hit_Monster.wav");

		// Bullet 소환 소리
		m_Scene->GetResource()->LoadSound("Effect", "SummonBullet", false, "enemy/belial/random5.wav");

		// Sword 소환 소리
		m_Scene->GetResource()->LoadSound("Effect", "SummonSword", false, "enemy/belial/slimeball.wav");

		// 웃음 소리
		m_Scene->GetResource()->LoadSound("Effect", "BelialLaugh", false, "enemy/belial/beliallaugh_rev.wav");

		// 죽을때 터지는 소리
		m_Scene->GetResource()->LoadSound("Effect", "Explosion", false, "enemy/public/Explosion.wav");

		// 보스 시작 BGM
		m_Scene->GetResource()->LoadSound("BGM", "JailBoss", false, "stage/bgm/1.JailBoss.wav");
	}

	else
	{
		// 피격 소리
		CResourceManager::GetInst()->LoadSound("Effect", "MonsterHit", false, "enemy/public/Hit_Monster.wav");

		// Bullet 소환 소리
		CResourceManager::GetInst()->LoadSound("Effect", "SummonBullet", false, "enemy/belial/random5.wav");

		// Sword 소환 소리
		CResourceManager::GetInst()->LoadSound("Effect", "SummonSword", false, "enemy/belial/slimeball.wav");

		// 웃음 소리
		CResourceManager::GetInst()->LoadSound("Effect", "BelialLaugh", false, "enemy/belial/beliallaugh_rev.wav");

		// 죽을때 터지는 소리
		CResourceManager::GetInst()->LoadSound("Effect", "Explosion", false, "enemy/public/Explosion.wav");

		// 보스 시작 BGM
		CResourceManager::GetInst()->LoadSound("BGM", "JailBoss", false, "stage/bgm/1.JailBoss.wav");
	}

	return true;
}

void CBelial::Update(float DeltaTime)
{
	CCreature::Update(DeltaTime);


	if (m_Attacked)
		m_BelialHead->GetMaterial(0)->SetBaseColor(1.f, 0.f, 0.f, 1.f);

	else
		m_BelialHead->GetMaterial(0)->SetBaseColor(1.f, 1.f, 1.f, 1.f);


	if (m_BossStart)
	{
		if (m_CameraStart)
		{
			m_CameraTime += DeltaTime;

			if (m_CameraTime >= 3.f)
			{
				m_CameraStart = false;
				m_CameraTime = 0.f;

				m_Scene->GetCameraManager()->SetCurrentCamera((CCameraComponent*)m_PlayerObject->FindComponent("Camera"));

				((CCharacter*)m_PlayerObject.Get())->AddBindFunction();
			}
		}

		if (m_HP <= 0)
			m_ActionType = EBelialActionType::Die;

		// 공격중이 아닐 때, 랜덤으로 패턴 선택
		else if (!m_Attack)
		{
			m_AttackDelay += DeltaTime;

			// 공격중이 아니라면 기본 Idle
			m_ActionType = EBelialActionType::Idle;

			// 다음 공격까지 3초의 대기시간을 가지고 다음 공격 선택
			if (m_AttackDelay >= 3.f)
			{
				m_Attack = true;
				m_ActionType = (EBelialActionType)(rand() % (int)EBelialActionType::Sword + 1);
				m_AttackDelay = 0.f;
			}
		}
	}

	// 아직 보스 패턴 시작을 안했다면 기본 Idle
	else
	{
		m_ActionType = EBelialActionType::Idle;
	}
}

void CBelial::PostUpdate(float DeltaTime)
{
	CCreature::PostUpdate(DeltaTime);

	switch (m_ActionType)
	{
	case EBelialActionType::Idle:
	{
		m_BelialHead->GetAnimation()->ChangeAnimation("Idle");
		m_BelialHead->SetWorldScaleY(384.f);
	}
		break;
	case EBelialActionType::Laser:
	{
		if (!m_SelectLaserAttackCount)
		{
			// Laser 공격 횟수는 1 ~ 3번 중 랜덤으로 선택
			m_LaserAttackCount = rand() % 3 + 1;
			m_SelectLaserAttackCount = true;
		}

		if (m_LaserAttackCount == 0)
		{
			m_Attack = false;
			m_SelectLaserAttackCount = false;
			break;
		}

		// 홀수번째 공격에는 오른손이 움직임
		if (m_LaserAttackCount % 2 == 1)
			m_BelialRightHand->SetWorldPositionY(m_PlayerObject->GetWorldPos().y);

		// 짝수번째 공격에는 왼손이 움직임
		else
			m_BelialLeftHand->SetWorldPositionY(m_PlayerObject->GetWorldPos().y);

		m_LaserAttackDelay += DeltaTime;

		if (m_LaserAttackDelay >= 1.5f)
		{
			m_LaserAttackDelay -= 1.5f;

			if (m_LaserAttackCount % 2 == 1)
			{
				m_BelialRightHand->GetAnimation()->ChangeAnimation("Attack");
				--m_LaserAttackCount;
			}

			else
			{
				m_BelialLeftHand->GetAnimation()->ChangeAnimation("Attack");
				--m_LaserAttackCount;
			}
		}
	}
		break;
	case EBelialActionType::Bullet:
	{
		m_BelialHead->GetAnimation()->ChangeAnimation("Attack");
		m_BelialHead->SetWorldScaleY(480.f);


		// 3초 동안 4방향으로 Bullet을 총 30번 발사 -> 0.1초에 1
		m_BulletAttackTime += DeltaTime;

		if (m_BulletAttackTime >= 0.1f)
		{
			m_BulletAttackTime -= 0.1f;

			--m_BulletAttackCount;

			if (m_BulletClockwise)
				SummonBulletClockwise();

			else
				SummonBulletCounterClockwise();
		}

		if (m_BulletAttackCount == 0)
		{
			m_Attack = false;
			m_BulletAttackCount = 30;
			m_BulletClockwise = rand() % 2;
		}

	}
		break;
	case EBelialActionType::Sword:
	{
		m_BelialHead->GetAnimation()->ChangeAnimation("Idle");

		m_SwordAttackTime += DeltaTime;

		// 검 6개 생성
		if (m_SwordAttackTime >= 0.2f)
		{
			m_SwordAttackTime -= 0.2f;

			--m_SwordAttackCount;

			SummonSword();
		}

		if (m_SwordAttackCount == 0)
		{
			m_Attack = false;
			m_SwordAttackCount = 6;
			// 다 쏘고나면 SummonPosition 초기화
			m_SwordSummonPosition = Vector2(m_BelialBack->GetWorldPos().x - 360.f, m_BelialBack->GetWorldPos().y + 500.f);
		}
	}
		break;
	case EBelialActionType::Die:
		// 죽으면 9초 동안 DestroyEffect가 5개씩 39번 나오고, 40번째에 10방향으로 7번 나옴
		// 9초후에 다 Enable(false)하고 DeadHead랑 DeadMouth만 Enable(true)하고 아래로 떨어지다가 Y 320 위치에서 멈춘다.
		if (m_DieMotion)
		{
			m_DieMotionTime += DeltaTime;

			m_BelialHead->GetAnimation()->ChangeAnimation("Idle");
			m_BelialHead->SetWorldScaleY(384.f);
			m_BelialLeftHand->GetAnimation()->ChangeAnimation("Idle");
			m_BelialRightHand->GetAnimation()->ChangeAnimation("Idle");


			m_DestroyEffectTime += DeltaTime;

			if (m_DestroyEffectCount < 39)
			{
				if (m_DestroyEffectTime >= 0.2f)
				{
					m_DestroyEffectTime -= 0.2f;

					RandomDestroyEffect();

					m_Scene->GetResource()->FindSound("Explosion")->Play();

					++m_DestroyEffectCount;
				}
			}

			else
			{
				if (m_DestroyEffectTime >= 0.1f)
				{
					m_DestroyEffectTime -= 0.1f;

					LastDestroyEffect();

					m_Scene->GetResource()->FindSound("Explosion")->Play();

					++m_DestroyEffectCount;
				}
			}

			if (m_DieMotionTime >= 8.3f)
			{
				m_DieMotion = false;
				m_DieMotionTime = 0.f;

				m_BelialBack->SetEnable(false);
				m_BelialHead->SetEnable(false);
				m_BelialLeftHand->SetEnable(false);
				m_BelialRightHand->SetEnable(false);

				m_BelialDeadHead->SetEnable(true);
				m_BelialDeadMouth->SetEnable(true);

				m_Scene->GetCameraManager()->SetCurrentCamera((CCameraComponent*)m_PlayerObject->FindComponent("Camera"));

				((CCharacter*)m_PlayerObject.Get())->AddBindFunction();
			}
		}

		else if(!m_DieEnd)
		{
			if (m_BelialDeadHead->GetWorldPos().y > 320.f)
			{
				m_Body->AddWorldPosition(GetWorldAxis(AXIS_Y) * -300.f * DeltaTime);
			}

			else
			{
				m_BelialDeadHead->SetRelativeRotationZ(-10.f);
				m_BelialDeadMouth->SetEnable(false);
				
				m_Scene->CreateObject<CEndingPortal>("EndingPortal")->SetWorldPosition(1180.f, 192.f);

				m_DieEnd = true;
			}

		}
		break;
	}
}

CBelial* CBelial::Clone() const
{
	return new CBelial(*this);
}

void CBelial::Save(FILE* File)
{
	CCreature::Save(File);
}

void CBelial::Load(FILE* File)
{
	CCreature::Load(File);

	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_BelialHead = (CSpriteComponent*)FindComponent("BelialHead");
	m_BelialBack = (CSpriteComponent*)FindComponent("BelialBack");
	m_BelialLeftHand = (CSpriteComponent*)FindComponent("BelialLeftHand");
	m_BelialRightHand = (CSpriteComponent*)FindComponent("BelialRightHand");
	m_BelialDeadHead = (CSpriteComponent*)FindComponent("BelialDeadHead");
	m_BelialDeadMouth = (CSpriteComponent*)FindComponent("BelialDeadMouth");
}

void CBelial::SummonBulletClockwise()
{
	CBelialBullet* Bullet1 = m_Scene->CreateObject<CBelialBullet>("BelialBullet1");
	CBelialBullet* Bullet2 = m_Scene->CreateObject<CBelialBullet>("BelialBullet2");
	CBelialBullet* Bullet3 = m_Scene->CreateObject<CBelialBullet>("BelialBullet3");
	CBelialBullet* Bullet4 = m_Scene->CreateObject<CBelialBullet>("BelialBullet4");

	Bullet1->SetBulletInfo(m_BulletSummonPosition, m_BulletAngle);
	Bullet2->SetBulletInfo(m_BulletSummonPosition, m_BulletAngle + 90.f);
	Bullet3->SetBulletInfo(m_BulletSummonPosition, m_BulletAngle + 180.f);
	Bullet4->SetBulletInfo(m_BulletSummonPosition, m_BulletAngle + 270.f);

	m_Scene->GetResource()->FindSound("SummonBullet")->Play();

	// 한번 발사할 때 마다 6도씩 증가
	m_BulletAngle -= 6.f;
}

void CBelial::SummonBulletCounterClockwise()
{
	CBelialBullet* Bullet1 = m_Scene->CreateObject<CBelialBullet>("BelialBullet1");
	CBelialBullet* Bullet2 = m_Scene->CreateObject<CBelialBullet>("BelialBullet2");
	CBelialBullet* Bullet3 = m_Scene->CreateObject<CBelialBullet>("BelialBullet3");
	CBelialBullet* Bullet4 = m_Scene->CreateObject<CBelialBullet>("BelialBullet4");

	Bullet1->SetBulletInfo(m_BulletSummonPosition, m_BulletAngle);
	Bullet2->SetBulletInfo(m_BulletSummonPosition, m_BulletAngle + 90.f);
	Bullet3->SetBulletInfo(m_BulletSummonPosition, m_BulletAngle + 180.f);
	Bullet4->SetBulletInfo(m_BulletSummonPosition, m_BulletAngle + 270.f);

	m_Scene->GetResource()->FindSound("SummonBullet")->Play();

	// 한번 발사할 때 마다 6도씩 증가
	m_BulletAngle += 6.f;
}

void CBelial::SummonSword()
{
	CBelialSword* Sword = m_Scene->CreateObject<CBelialSword>("CBelialSword");

	Sword->SetSwordInfo(m_SwordSummonPosition);

	m_Scene->GetResource()->FindSound("SummonSword")->Play();

	// 한번 소환할 때 마다 x위치 50씩 증가
	m_SwordSummonPosition.x += 120.f;
}

void CBelial::RandomDestroyEffect()
{
	CMonsterDestroyEffect* Effect1 = m_Scene->CreateObject<CMonsterDestroyEffect>("CMonsterDestroyEffect1");
	CMonsterDestroyEffect* Effect2 = m_Scene->CreateObject<CMonsterDestroyEffect>("CMonsterDestroyEffect2");
	CMonsterDestroyEffect* Effect3 = m_Scene->CreateObject<CMonsterDestroyEffect>("CMonsterDestroyEffect3");
	CMonsterDestroyEffect* Effect4 = m_Scene->CreateObject<CMonsterDestroyEffect>("CMonsterDestroyEffect4");
	CMonsterDestroyEffect* Effect5 = m_Scene->CreateObject<CMonsterDestroyEffect>("CMonsterDestroyEffect5");

	int RandomX = (rand() % 601) - 300;
	int RandomY = (rand() % 601) - 300;

	Vector2 Pos1 = m_BulletSummonPosition + Vector2((float)RandomX, (float)RandomY);

	RandomX = (rand() % 601) - 300;
	RandomY = (rand() % 601) - 300;

	Vector2 Pos2 = m_BulletSummonPosition + Vector2((float)RandomX, (float)RandomY);

	RandomX = (rand() % 601) - 300;
	RandomY = (rand() % 601) - 300;

	Vector2 Pos3 = m_BulletSummonPosition + Vector2((float)RandomX, (float)RandomY);

	RandomX = (rand() % 601) - 300;
	RandomY = (rand() % 601) - 300;

	Vector2 Pos4 = m_BulletSummonPosition + Vector2((float)RandomX, (float)RandomY);

	RandomX = (rand() % 601) - 300;
	RandomY = (rand() % 601) - 300;

	Vector2 Pos5 = m_BulletSummonPosition + Vector2((float)RandomX, (float)RandomY);

	Effect1->SetEffectInfo(Pos1);
	Effect2->SetEffectInfo(Pos2);
	Effect3->SetEffectInfo(Pos3);
	Effect4->SetEffectInfo(Pos4);
	Effect5->SetEffectInfo(Pos5);
}

void CBelial::LastDestroyEffect()
{
	CMonsterDestroyEffect* Effect1 = m_Scene->CreateObject<CMonsterDestroyEffect>("CMonsterDestroyEffect1");
	CMonsterDestroyEffect* Effect2 = m_Scene->CreateObject<CMonsterDestroyEffect>("CMonsterDestroyEffect2");
	CMonsterDestroyEffect* Effect3 = m_Scene->CreateObject<CMonsterDestroyEffect>("CMonsterDestroyEffect3");
	CMonsterDestroyEffect* Effect4 = m_Scene->CreateObject<CMonsterDestroyEffect>("CMonsterDestroyEffect4");
	CMonsterDestroyEffect* Effect5 = m_Scene->CreateObject<CMonsterDestroyEffect>("CMonsterDestroyEffect5");
	CMonsterDestroyEffect* Effect6 = m_Scene->CreateObject<CMonsterDestroyEffect>("CMonsterDestroyEffect6");
	CMonsterDestroyEffect* Effect7 = m_Scene->CreateObject<CMonsterDestroyEffect>("CMonsterDestroyEffect7");
	CMonsterDestroyEffect* Effect8 = m_Scene->CreateObject<CMonsterDestroyEffect>("CMonsterDestroyEffect8");
	CMonsterDestroyEffect* Effect9 = m_Scene->CreateObject<CMonsterDestroyEffect>("CMonsterDestroyEffect9");
	CMonsterDestroyEffect* Effect10 = m_Scene->CreateObject<CMonsterDestroyEffect>("CMonsterDestroyEffect10");

	Effect1->SetEffectInfo(m_BulletSummonPosition + Vector2(m_DestroyEffectDistance * cosf(0.f), m_DestroyEffectDistance * sinf(0.f)));
	Effect2->SetEffectInfo(m_BulletSummonPosition + Vector2(m_DestroyEffectDistance * cosf(36.f), m_DestroyEffectDistance * sinf(36.f)));
	Effect3->SetEffectInfo(m_BulletSummonPosition + Vector2(m_DestroyEffectDistance * cosf(72.f), m_DestroyEffectDistance * sinf(72.f)));
	Effect4->SetEffectInfo(m_BulletSummonPosition + Vector2(m_DestroyEffectDistance * cosf(108.f), m_DestroyEffectDistance * sinf(108.f)));
	Effect5->SetEffectInfo(m_BulletSummonPosition + Vector2(m_DestroyEffectDistance * cosf(144.f), m_DestroyEffectDistance * sinf(144.f)));
	Effect6->SetEffectInfo(m_BulletSummonPosition + Vector2(m_DestroyEffectDistance * cosf(180.f), m_DestroyEffectDistance * sinf(180.f)));
	Effect7->SetEffectInfo(m_BulletSummonPosition + Vector2(m_DestroyEffectDistance * cosf(216.f), m_DestroyEffectDistance * sinf(216.f)));
	Effect8->SetEffectInfo(m_BulletSummonPosition + Vector2(m_DestroyEffectDistance * cosf(252.f), m_DestroyEffectDistance * sinf(252.f)));
	Effect9->SetEffectInfo(m_BulletSummonPosition + Vector2(m_DestroyEffectDistance * cosf(288.f), m_DestroyEffectDistance * sinf(288.f)));
	Effect10->SetEffectInfo(m_BulletSummonPosition + Vector2(m_DestroyEffectDistance * cosf(324.f), m_DestroyEffectDistance * sinf(324.f)));

	m_DestroyEffectDistance += 50.f;
}
