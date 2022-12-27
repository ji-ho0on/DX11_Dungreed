#pragma once

#include "Monster.h"

class CGhost :
    public CMonster
{
	friend class CScene;

protected:
	CGhost();
	CGhost(const CGhost& Obj);
	virtual ~CGhost();

private:
	CSharedPtr<class CSpriteComponent>	m_Ghost;

private:
	CSharedPtr<CGameObject>	m_PlayerObject;

	Vector3 m_AttackDir;

	float	m_DetectDistance;	// Player�� �����ϴ� ����
	float	m_AttackWaitTime;	// ���� ��� �ð�
	bool	m_Attack;
	float	m_AttackTime;
	float	m_MoveSpeed;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CGhost* Clone()    const;

private:
	void AttackCollision(const CollisionResult& Result);
};

