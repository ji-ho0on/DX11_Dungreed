#pragma once

#include "GameObject\GameObject.h"

class CCreature :
    public CGameObject
{
	friend class CScene;

protected:
	CCreature();
	CCreature(const CCreature& Obj);
	virtual ~CCreature();

protected:
	int					m_HP;
	bool				m_Attacked;		// 피격당했는지
	float				m_AttackedTime;	// 피격당한 시간

public:
	virtual int InflictDamage(int Damage);
	virtual void Destroy();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CCreature* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

