#pragma once

#include "Monster.h"

class CGiantNormalBat :
    public CMonster
{
	friend class CScene;

protected:
	CGiantNormalBat();
	CGiantNormalBat(const CGiantNormalBat& Obj);
	virtual ~CGiantNormalBat();

private:
	CSharedPtr<class CSpriteComponent>	m_GiantNormalBat;

private:
	CSharedPtr<CGameObject>	m_PlayerObject;

	float	m_AttackAngle;

	float	m_DetectDistance;	// Player�� �����ϴ� ����
	float	m_AttackTime;		// ���� �ð�

public:
	float GetAttackAngle()	const
	{
		return m_AttackAngle;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CGiantNormalBat* Clone()    const;
};

