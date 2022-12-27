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

	bool	m_Detect;			// ���� Player�� �����ߴ���
	float	m_DetectDistance;	// Player�� �����ϴ� ����, �ش� �����ȿ� ������ �÷��̾ �i�ư�

	bool	m_AttackRange;		// ���� ���ݹ����� ���Դ���
	float	m_AttackDistance;	// ���ݹ���, �ش� �����ȿ� ������ ������.
	float	m_AttackTime;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CSkelSword* Clone()    const;
};

