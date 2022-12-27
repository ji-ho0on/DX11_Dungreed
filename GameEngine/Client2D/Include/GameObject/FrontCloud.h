#pragma once

#include "GameObject\GameObject.h"

class CFrontCloud :
    public CGameObject
{
	friend class CScene;

protected:
	CFrontCloud();
	CFrontCloud(const CFrontCloud& Obj);
	virtual ~CFrontCloud();

private:
	CSharedPtr<class CSpriteComponent>	m_FrontCloud;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CFrontCloud* Clone()    const;
};

