#pragma once

#include "GameObject/GameObject.h"

class CBullet :
    public CGameObject
{
	friend class CScene;

protected:
	CBullet();
	CBullet(const CBullet& Obj);
	virtual ~CBullet();

private:
	CSharedPtr<class CColliderSphere2D>	m_Body;
	CSharedPtr<class CSpriteComponent>	m_Bullet;
	float								m_MoveSpeed;
	float								m_Distance;

public:
	void SetDistance(float Distance)
	{
		m_Distance = Distance;
	}

	void SetMoveSpeed(float Speed)
	{
		m_MoveSpeed = Speed;
	}

public:
	void SetCollisionProfileName(const std::string& Name);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBullet* Clone()    const;

private:
	void CollisionBullet(const CollisionResult& result);
};

