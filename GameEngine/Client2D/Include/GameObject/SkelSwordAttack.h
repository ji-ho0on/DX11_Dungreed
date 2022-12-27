#pragma once

#include "GameObject\GameObject.h"

class CSkelSwordAttack :
    public CGameObject
{
	friend class CScene;

protected:
	CSkelSwordAttack();
	CSkelSwordAttack(const CSkelSwordAttack& Obj);
	virtual ~CSkelSwordAttack();

private:
	CSharedPtr<class CColliderBox2D>	m_Body;

private:
	float	m_AttackTime;

public:
	void SetAttackInfo(const Vector2& Position);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CSkelSwordAttack* Clone()    const;

private:
	void AttackCollision(const CollisionResult& Result);
};

