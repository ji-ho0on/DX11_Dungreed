#pragma once

#include "GameObject\GameObject.h"

class CArrowHitEffect :
    public CGameObject
{
	friend class CScene;

protected:
	CArrowHitEffect();
	CArrowHitEffect(const CArrowHitEffect& Obj);
	virtual ~CArrowHitEffect();

private:
	CSharedPtr<class CSpriteComponent>	m_Effect;

public:
	void SetEffectInfo(const Vector2& Position, float RotationZ);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CArrowHitEffect* Clone()    const;
};

