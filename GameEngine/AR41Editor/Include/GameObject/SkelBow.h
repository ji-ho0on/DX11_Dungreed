#pragma once

#include "Monster.h"

class CSkelBow :
    public CMonster
{
	friend class CScene;

protected:
	CSkelBow();
	CSkelBow(const CSkelBow& Obj);
	virtual ~CSkelBow();

private:
	CSharedPtr<class CSpriteComponent>	m_Skel;
	CSharedPtr<class CSpriteComponent>	m_Bow;

private:
	CSharedPtr<CGameObject>	m_PlayerObject;

	bool	m_Detect;			// 현재 Player를 감지했는지
	float	m_DetectDistance;	// Player를 감지하는 범위, 해당 범위안에 들어오면 플레이어를 쫒아감

	float	m_AttackAngle;		// 활의 각도
	Vector3	m_AttackDir;		// 활을 쏠 방향

	bool	m_AttackRange;		// 감지 범위에서 2.5초가 지났는지
	float	m_AttackWaitTime;	// 감지 범위에 들어온 시간
	float	m_AttackTime;		// 공격하는 시간, 공격하는 동안은 다른 행동을 하지 않음

public:
	float GetAttackAngle()	const
	{
		return m_AttackAngle;
	}

	const Vector3& GetAttackDir()	const
	{
		return m_AttackDir;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CSkelBow* Clone()    const;
};

