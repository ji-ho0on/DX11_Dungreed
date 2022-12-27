#pragma once

#include "GameObject\GameObject.h"

class CBansheeBullet :
    public CGameObject
{
	friend class CScene;

protected:
	CBansheeBullet();
	CBansheeBullet(const CBansheeBullet& Obj);
	virtual ~CBansheeBullet();

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
	virtual CBansheeBullet* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

private:
	void AttackCollision(const CollisionResult& Result);
};

