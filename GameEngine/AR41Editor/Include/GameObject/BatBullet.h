#pragma once

#include "GameObject\GameObject.h"

class CBatBullet :
    public CGameObject
{
	friend class CScene;

protected:
	CBatBullet();
	CBatBullet(const CBatBullet& Obj);
	virtual ~CBatBullet();

protected:
	CSharedPtr<class CColliderSphere2D>	m_Body;
	CSharedPtr<class CSpriteComponent>	m_Bullet;

protected:
	Vector2		m_InitPosition;
	bool		m_Move;
	float		m_MoveWaitTime;

public:
	void SetBulletInfo(const Vector2& Position, float Angle);
	void SetBulletScale(const Vector2& Scale);

public:
	void SetMove(bool Move)
	{
		m_Move = Move;
	}

	void SetMoveWaitTime(float Time)
	{
		m_MoveWaitTime = Time;
		m_Move = false;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBatBullet* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

private:
	void AttackCollision(const CollisionResult& Result);
};

