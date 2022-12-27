#pragma once

#include "Monster.h"

class CBanshee :
    public CMonster
{
	friend class CScene;

protected:
	CBanshee();
	CBanshee(const CBanshee& Obj);
	virtual ~CBanshee();

private:
	CSharedPtr<class CSpriteComponent>	m_Banshee;

private:
	CSharedPtr<CGameObject>	m_PlayerObject;

	float	m_DetectDistance;	// Player를 감지하는 범위
	float	m_AttackTime;		// 공격 시간

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBanshee* Clone()    const;
};

