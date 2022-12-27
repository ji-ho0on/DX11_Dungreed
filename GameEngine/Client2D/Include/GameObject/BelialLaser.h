#pragma once

#include "GameObject\GameObject.h"

class CBelialLaser :
    public CGameObject
{
	friend class CScene;

protected:
	CBelialLaser();
	CBelialLaser(const CBelialLaser& Obj);
	virtual ~CBelialLaser();

protected:
	CSharedPtr<class CColliderBox2D>	m_Body;
	CSharedPtr<class CSpriteComponent>	m_BelialLaserHead;
	CSharedPtr<class CSpriteComponent>	m_BelialLaserBody1;
	CSharedPtr<class CSpriteComponent>	m_BelialLaserBody2;
	CSharedPtr<class CSpriteComponent>	m_BelialLaserBody3;

public:
	void SetLaserInfo(const Vector2& Position, bool IsRightHand);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBelialLaser* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

private:
	void AttackCollision(const CollisionResult& Result);
};

