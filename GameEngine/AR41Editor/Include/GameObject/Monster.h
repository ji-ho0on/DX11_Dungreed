#pragma once

#include "Creature.h"

class CMonster :
	public CCreature
{
	friend class CScene;

protected:
	CMonster();
	CMonster(const CMonster& Obj);
	virtual ~CMonster();

protected:
	CSharedPtr<class CColliderBox2D>	m_Body;
	CSharedPtr<class CGravityAgent>		m_Gravity;

protected:
	EMonsterActionType	m_ActionType;
	int					m_Power;
	float				m_Speed;

public:
	void SetMonsterActionType(EMonsterActionType Type)
	{
		m_ActionType = Type;
	}

public:
	virtual int InflictDamage(int Damage);
	virtual void Destroy();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CMonster* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

