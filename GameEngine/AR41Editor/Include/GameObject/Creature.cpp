#include "Creature.h"

CCreature::CCreature() :
	m_HP(100),
	m_Attacked(false),
	m_AttackedTime(0.f)
{
	SetTypeID<CCreature>();

	m_ObjectTypeName = "Creature";
}

CCreature::CCreature(const CCreature& Obj) :
	CGameObject(Obj)
{
	m_HP = Obj.m_HP;
	m_Attacked = Obj.m_Attacked;
	m_AttackedTime = Obj.m_AttackedTime;
}

CCreature::~CCreature()
{
}

int CCreature::InflictDamage(int Damage)
{
	int _Damage = Damage;

	if (_Damage < 0)
		_Damage = 0;

	m_HP -= _Damage;

	m_Attacked = true;

	return _Damage;
}

void CCreature::Destroy()
{
	CGameObject::Destroy();
}

void CCreature::Start()
{
	CGameObject::Start();
}

bool CCreature::Init()
{
	CGameObject::Init();

	return true;
}

void CCreature::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

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

void CCreature::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CCreature* CCreature::Clone() const
{
	return new CCreature(*this);
}

void CCreature::Save(FILE* File)
{
	CGameObject::Save(File);

	fwrite(&m_HP, sizeof(int), 1, File);
}

void CCreature::Load(FILE* File)
{
	CGameObject::Load(File);

	fread(&m_HP, sizeof(int), 1, File);
}