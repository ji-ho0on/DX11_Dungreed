#include "BelialSword.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderOBB2D.h"
#include "../Animation2D/BelialSwordAnimation.h"
#include "Scene/Scene.h"
#include "Character.h"

CBelialSword::CBelialSword()	:
	m_ChargeTime(0.f),
	m_Shoot(false),
	m_Hit(false),
	m_HitTime(0.f)
{
	SetTypeID<CBelialSword>();

	m_ObjectTypeName = "BelialSword";
}

CBelialSword::CBelialSword(const CBelialSword& Obj) :
	CGameObject(Obj)
{
	m_Body = (CColliderOBB2D*)FindComponent("Body");
	m_Sword = (CSpriteComponent*)FindComponent("Sword");
	m_SwordEffect = (CSpriteComponent*)FindComponent("SwordEffect");

	m_ChargeTime = Obj.m_ChargeTime;
	m_Shoot = Obj.m_Shoot;
	m_Hit = Obj.m_Hit;
	m_HitTime = Obj.m_HitTime;
}

CBelialSword::~CBelialSword()
{
}

void CBelialSword::SetSwordInfo(const Vector2& Position)
{
	m_Body->SetWorldPosition(Position);
}

void CBelialSword::Start()
{
	CGameObject::Start();

	m_PlayerObject = m_Scene->GetSceneInfo()->GetPlayerObject();

	m_Body->SetCollisionCallback<CBelialSword>(ECollision_Result::Collision, this, &CBelialSword::AttackCollision);
}

bool CBelialSword::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderOBB2D>("Body");
	m_Body->SetCollisionProfile("MonsterAttack");
	m_Body->SetInheritScale(true);
	m_Body->SetPivot(0.f, 0.5f);

	m_Sword = CreateComponent<CSpriteComponent>("Sword");
	m_Sword->SetTexture("BelialSword_Default", TEXT("boss/Belial/Sword/BelialSword_default.png"));
	m_Sword->SetWorldScale(270.f, 90.f);
	m_Sword->SetRenderLayerName("Effect");
	m_Sword->SetPivot(0.f, 0.5f);
	m_Sword->SetInheritRotZ(true);

	m_SwordEffect = CreateComponent<CSpriteComponent>("SwordEffect");
	m_SwordEffect->SetAnimation<CBelialSwordAnimation>("BelialSwordAnimation");
	m_SwordEffect->SetWorldScale(300.f, 100.f);
	m_SwordEffect->SetRenderLayerName("Effect");
	m_SwordEffect->SetPivot(0.f, 0.5f);
	m_SwordEffect->SetInheritRotZ(true);

	m_Body->SetBoxHalfSize(m_Sword->GetWorldScale().x / 2.f, m_Sword->GetWorldScale().y / 4.f);

	m_Body->AddChild(m_Sword);
	m_Sword->AddChild(m_SwordEffect);

	m_Body->SetEnable(false);

	// 임시 위치 지정
	//m_Body->SetWorldPosition(300.f, 600.f);
	//m_Body->SetWorldRotationZ(-90.f);

	return true;
}

void CBelialSword::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (!m_Shoot)
	{
		m_ChargeTime += DeltaTime;

		// Charge시간 동안 2초동안 플레이어 방향으로 회전한다.
		//m_Body->SetWorldRotationZ(Vector2(m_PlayerObject->GetWorldPos().x, m_PlayerObject->GetWorldPos().y).Angle(GetWorldPos()));
		m_Body->SetWorldRotationZ(Vector2(GetWorldPos().x, GetWorldPos().y).Angle(m_PlayerObject->GetWorldPos()));

		if (m_ChargeTime >= 2.f)
		{
			m_Shoot = true;
			// 발사되면 ChargeEffect를 없애고 Sword의 이미지를 바꾼다.
			m_SwordEffect->SetEnable(false);
			m_Sword->SetTexture("BelialSword_Shoot", TEXT("boss/Belial/Sword/BelialSword_shoot.png"));
			m_Body->SetEnable(true);
		}
	}

	else if(!m_Hit)
	{
		// Shoot이 되면 마지막으로 찾은 Player 방향으로 발사된다.
		m_Body->AddWorldPosition(GetWorldAxis(AXIS_X) * 1600.f * DeltaTime);

		// 땅에 꽂히면 이동을 멈추고 Sword의 이미지가 다시 돌아온다.
		// HitEffect가 생성된다.
		if (GetWorldPos().y <= 300.f)
		{
			m_Hit = true;
			m_Sword->SetTexture("BelialSword_Default", TEXT("boss/Belial/Sword/BelialSword_default.png"));
			m_SwordEffect->SetEnable(true);
			m_SwordEffect->GetAnimation()->ChangeAnimation("Hit");
			m_SwordEffect->SetRelativeScale(81.f, 220.f);
			m_SwordEffect->SetRelativePositionX(189.f);
			m_Body->SetEnable(false);
		}
	}

	else
	{
		// 땅에 꽂히고 3초 후에 사라진다.
		m_HitTime += DeltaTime;

		if (m_HitTime >= 3.f)
			Destroy();
	}

}

void CBelialSword::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBelialSword* CBelialSword::Clone() const
{
	return new CBelialSword(*this);
}

void CBelialSword::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CBelialSword::Load(FILE* File)
{
	CGameObject::Load(File);
}

void CBelialSword::AttackCollision(const CollisionResult& Result)
{
	// 캐릭터에게 데미지를 준다.
	((CCharacter*)Result.Dest->GetOwner())->InflictDamage(10);
	m_Body->SetEnable(false);
}