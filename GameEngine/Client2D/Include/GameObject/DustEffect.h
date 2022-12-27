#pragma once

#include "GameObject\GameObject.h"

class CDustEffect :
    public CGameObject
{
	friend class CScene;

protected:
	CDustEffect();
	CDustEffect(const CDustEffect& Obj);
	virtual ~CDustEffect();

protected:
	CSharedPtr<class CSpriteComponent>	m_Effect;

public:
	void SetEffectInfo(const Vector2& Position);
	void SetEffectDir(EDirection Dir);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CDustEffect* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

