#include "Monster.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Component/GravityAgent.h"
#include "Scene/Scene.h"

CMonster::CMonster() :
	m_ActionType(EMonsterActionType::Idle),
	m_Power(10),
	m_Speed(200.f)
{
	SetTypeID<CMonster>();

	m_ObjectTypeName = "Monster";
}

CMonster::CMonster(const CMonster& Obj) :
	CCreature(Obj)
{
	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_Gravity = (CGravityAgent*)FindComponent("Gravity");
	m_ActionType = Obj.m_ActionType;
	m_Power = Obj.m_Power;
	m_Speed = Obj.m_Speed;
}

CMonster::~CMonster()
{
}

int CMonster::InflictDamage(int Damage)
{
	int _Damage = CCreature::InflictDamage(Damage);

	m_Scene->GetResource()->FindSound("MonsterHit")->Play();

	if (m_HP <= 0)
		m_Scene->GetSceneInfo()->DeleteMonsterList(this);

	return _Damage;
}

void CMonster::Destroy()
{
	//m_Scene->GetSceneInfo()->DeleteMonsterList(this);

	CCreature::Destroy();
}

void CMonster::Start()
{
	CCreature::Start();

	m_Scene->GetSceneInfo()->PushMonsterList(this);
}

bool CMonster::Init()
{
	CCreature::Init();

	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Body->SetCollisionProfile("Monster");
	m_Body->SetInheritScale(true);
	m_Body->SetPivot(0.5f, 0.f);

	m_Gravity = CreateComponent<CGravityAgent>("Gravity");
	m_Gravity->SetGravityAccel(10.f);
	m_Gravity->SetJumpVelocity(50.f);
	m_Gravity->SetPhysicsSimulate(true);
	m_Gravity->SetFallStartY(300.f);


	//////////////////////////////////////////////////////////////////////////////////////////
	// 몬스터 사용하는 Sound Load
	//////////////////////////////////////////////////////////////////////////////////////////
	if (m_Scene)
	{
		// 피격 소리
		m_Scene->GetResource()->LoadSound("Effect", "MonsterHit", false, "enemy/public/Hit_Monster.wav");

		// 죽는 소리
		m_Scene->GetResource()->LoadSound("Effect", "MonsterDie", false, "enemy/public/MonsterDie.wav");
	}

	else
	{
		// 피격 소리
		CResourceManager::GetInst()->LoadSound("Effect", "MonsterHit", false, "enemy/public/Hit_Monster.wav");

		// 죽는 소리
		CResourceManager::GetInst()->LoadSound("Effect", "MonsterDie", false, "enemy/public/MonsterDie.wav");
	}

	return true;
}

void CMonster::Update(float DeltaTime)
{
	CCreature::Update(DeltaTime);

	if (m_Attacked)
	{
		m_AttackedTime += DeltaTime;

		if (m_AttackedTime >= 0.2f)
		{
			m_AttackedTime = 0.f;
			m_Attacked = false;
		}
	}
}

void CMonster::PostUpdate(float DeltaTime)
{
	CCreature::PostUpdate(DeltaTime);
}

CMonster* CMonster::Clone() const
{
	return new CMonster(*this);
}

void CMonster::Save(FILE* File)
{
	CCreature::Save(File);

	fwrite(&m_ActionType, sizeof(EMonsterActionType), 1, File);
	fwrite(&m_Power, sizeof(int), 1, File);
	fwrite(&m_Speed, sizeof(float), 1, File);
}

void CMonster::Load(FILE* File)
{
	CCreature::Load(File);

	fread(&m_ActionType, sizeof(EMonsterActionType), 1, File);
	fread(&m_Power, sizeof(int), 1, File);
	fread(&m_Speed, sizeof(float), 1, File);
}
