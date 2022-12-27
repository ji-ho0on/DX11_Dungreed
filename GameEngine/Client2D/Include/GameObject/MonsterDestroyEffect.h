#pragma once

#include "GameObject\GameObject.h"

class CMonsterDestroyEffect :
    public CGameObject
{
	friend class CScene;

protected:
	CMonsterDestroyEffect();
	CMonsterDestroyEffect(const CMonsterDestroyEffect& Obj);
	virtual ~CMonsterDestroyEffect();

protected:
	CSharedPtr<class CSpriteComponent>	m_Effect;

public:
	void SetEffectInfo(const Vector2& Position);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CMonsterDestroyEffect* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

