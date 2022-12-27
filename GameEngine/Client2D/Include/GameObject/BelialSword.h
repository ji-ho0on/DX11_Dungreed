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

	float	m_ChargeTime;	// 소환되고 Charge하는 시간
	bool	m_Shoot;		// Charge가 끝나고 발사가 되었는지
	bool	m_Hit;			// 발사가 되고 땅에 Hit 되었는지
	float	m_HitTime;		// 땅에 Hit된 후 시간


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

