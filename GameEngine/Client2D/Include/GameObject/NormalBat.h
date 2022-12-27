#pragma once

#include "Monster.h"

enum class ENormalBatMoveDir
{
	LT,
	RT,
	LB,
	RB,
	End
};

class CNormalBat :
    public CMonster
{
	friend class CScene;

protected:
	CNormalBat();
	CNormalBat(const CNormalBat& Obj);
	virtual ~CNormalBat();

private:
	CSharedPtr<class CSpriteComponent>	m_NormalBat;

private:
	CSharedPtr<CGameObject>	m_PlayerObject;

	Vector3	m_MoveDir;
	float	m_MoveDirChangeTime;

	float	m_DetectDistance;	// Player를 감지하는 범위

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CNormalBat* Clone()    const;
};

