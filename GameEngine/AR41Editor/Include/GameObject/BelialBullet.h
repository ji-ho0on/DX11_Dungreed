#pragma once

#include "GameObject/GameObject.h"

class CBelialBullet :
    public CGameObject
{
	friend class CScene;

protected:
	CBelialBullet();
	CBelialBullet(const CBelialBullet& Obj);
	virtual ~CBelialBullet();

protected:
	CSharedPtr<class CColliderSphere2D>	m_Body;
	CSharedPtr<class CSpriteComponent>	m_Bullet;

protected:
	bool		m_Move;
	Vector2		m_InitPosition;

public:
	void SetBulletInfo(const Vector2& Position, float Angle);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBelialBullet* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

private:
	void AttackCollision(const CollisionResult& Result);
};

