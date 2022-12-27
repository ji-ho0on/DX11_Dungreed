#pragma once

#include "Monster.h"

enum class ERedBatMoveDir
{
	LT,
	RT,
	LB,
	RB,
	End
};

class CRedBat :
    public CMonster
{
	friend class CScene;

protected:
	CRedBat();
	CRedBat(const CRedBat& Obj);
	virtual ~CRedBat();

private:
	CSharedPtr<class CSpriteComponent>	m_RedBat;

private:
	CSharedPtr<CGameObject>	m_PlayerObject;

	Vector3	m_MoveDir;
	float	m_MoveDirChangeTime;

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
	virtual CRedBat* Clone()    const;
};

