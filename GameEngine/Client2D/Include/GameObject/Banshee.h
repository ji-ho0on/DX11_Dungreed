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

	float	m_DetectDistance;	// Player�� �����ϴ� ����
	float	m_AttackTime;		// ���� �ð�

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBanshee* Clone()    const;
};

