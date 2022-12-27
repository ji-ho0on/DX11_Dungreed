#pragma once

#include "GameObject\GameObject.h"

class CBackCloud :
    public CGameObject
{
	friend class CScene;

protected:
	CBackCloud();
	CBackCloud(const CBackCloud& Obj);
	virtual ~CBackCloud();

private:
	CSharedPtr<class CSpriteComponent>	m_BackCloud;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBackCloud* Clone()    const;
};

