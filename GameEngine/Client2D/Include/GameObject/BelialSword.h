#pragma once

#include "GameObject\GameObject.h"

class CBelialSword :
    public CGameObject
{
	friend class CScene;

protected:
	CBelialSword();
	CBelialSword(const CBelialSword& Obj);
	virtual ~CBelialSword();

protected:
	CSharedPtr<class CColliderOBB2D>	m_Body;
	CSharedPtr<class CSpriteComponent>	m_Sword;
	CSharedPtr<class CSpriteComponent>	m_SwordEffect;

protected:
	CSharedPtr<CGameObject>	m_PlayerObject;

	float	m_ChargeTime;	// ��ȯ�ǰ� Charge�ϴ� �ð�
	bool	m_Shoot;		// Charge�� ������ �߻簡 �Ǿ�����
	bool	m_Hit;			// �߻簡 �ǰ� ���� Hit �Ǿ�����
	float	m_HitTime;		// ���� Hit�� �� �ð�


public:
	void SetSwordInfo(const Vector2& Position);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBelialSword* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

private:
	void AttackCollision(const CollisionResult& Result);
};

