#pragma once

#include "GameObject\GameObject.h"

class CSkelBowAttack :
    public CGameObject
{
	friend class CScene;

protected:
	CSkelBowAttack();
	CSkelBowAttack(const CSkelBowAttack& Obj);
	virtual ~CSkelBowAttack();

private:
	CSharedPtr<class CColliderOBB2D>	m_Body;
	CSharedPtr<class CSpriteComponent>	m_Arrow;

private:
	Vector3		m_Dir;
	Vector2		m_InitPosition;

public:
	void SetAttackInfo(const Vector2& Position, const Vector3& Dir, float Angle);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CSkelBowAttack* Clone()    const;

private:
	void EffectCollision(const CollisionResult& Result);
};

