#pragma once

#include "Monster.h"

class CSkelSword :
    public CMonster
{
	friend class CScene;

protected:
	CSkelSword();
	CSkelSword(const CSkelSword& Obj);
	virtual ~CSkelSword();

private:
	CSharedPtr<class CSpriteComponent>	m_Skel;
	CSharedPtr<class CSpriteComponent>	m_Sword;

private:
	CSharedPtr<CGameObject>	m_PlayerObject;

	bool	m_Detect;			// 현재 Player를 감지했는지
	float	m_DetectDistance;	// Player를 감지하는 범위, 해당 범위안에 들어오면 플레이어를 쫒아감

	bool	m_AttackRange;		// 현재 공격범위에 들어왔는지
	float	m_AttackDistance;	// 공격범위, 해당 범위안에 들어오면 공격함.
	float	m_AttackTime;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CSkelSword* Clone()    const;
};

