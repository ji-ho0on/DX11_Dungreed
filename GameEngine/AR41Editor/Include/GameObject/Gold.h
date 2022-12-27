#pragma once

#include "GameObject\GameObject.h"

class CGold :
    public CGameObject
{
	friend class CScene;

protected:
	CGold();
	CGold(const CGold& Obj);
	virtual ~CGold();

private:
	CSharedPtr<class CColliderSphere2D>	m_Body;
	CSharedPtr<class CSpriteComponent>	m_Gold;
	CSharedPtr<class CGravityAgent>		m_Gravity;

private:
	int		m_GoldAmount;

public:
	void SetGoldInfo(const Vector2& Position);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CGold* Clone()    const;

private:
	void GoldCollision(const CollisionResult& result);
};

