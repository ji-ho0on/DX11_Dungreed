#pragma once

#include "Monster.h"

class CGiantRedBat :
    public CMonster
{
	friend class CScene;

protected:
	CGiantRedBat();
	CGiantRedBat(const CGiantRedBat& Obj);
	virtual ~CGiantRedBat();

private:
	CSharedPtr<class CSpriteComponent>	m_GiantRedBat;

private:
	CSharedPtr<CGameObject>	m_PlayerObject;

	float	m_DetectDistance;	// Player를 감지하는 범위

	float	m_AttackAngle;
	float	m_AttackTime;		// 공격 시간
	bool	m_Attack;

	float	m_BulletSummonTime;
	int		m_BulletCount;
	float	m_BulletAngle;
	float	m_BulletWaitTime;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CGiantRedBat* Clone()    const;

private:
	void SummonBullet();
};

