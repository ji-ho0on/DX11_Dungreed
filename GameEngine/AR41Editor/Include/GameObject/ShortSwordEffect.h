#pragma once

#include "GameObject\GameObject.h"

class CShortSwordEffect :
    public CGameObject
{
	friend class CScene;

protected:
	CShortSwordEffect();
	CShortSwordEffect(const CShortSwordEffect& Obj);
	virtual ~CShortSwordEffect();

private:
	CSharedPtr<class CColliderOBB2D>	m_EffectBody;
	CSharedPtr<class CSpriteComponent>	m_Effect;

public:
	void SetEffectInfo(const Vector2& Position, float RotationZ);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CShortSwordEffect* Clone()    const;

private:
	void EffectCollision(const CollisionResult& Result);
};

