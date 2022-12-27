#pragma once

#include "GameObject\GameObject.h"

class CJumpEffect :
    public CGameObject
{
	friend class CScene;

protected:
	CJumpEffect();
	CJumpEffect(const CJumpEffect& Obj);
	virtual ~CJumpEffect();

protected:
	CSharedPtr<class CSpriteComponent>	m_Effect;

public:
	void SetEffectInfo(const Vector2& Position);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CJumpEffect* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

