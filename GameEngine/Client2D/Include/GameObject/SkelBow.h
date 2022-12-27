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

	bool	m_Detect;			// ���� Player�� �����ߴ���
	float	m_DetectDistance;	// Player�� �����ϴ� ����, �ش� �����ȿ� ������ �÷��̾ �i�ư�

	float	m_AttackAngle;		// Ȱ�� ����
	Vector3	m_AttackDir;		// Ȱ�� �� ����

	bool	m_AttackRange;		// ���� �������� 2.5�ʰ� ��������
	float	m_AttackWaitTime;	// ���� ������ ���� �ð�
	float	m_AttackTime;		// �����ϴ� �ð�, �����ϴ� ������ �ٸ� �ൿ�� ���� ����

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

