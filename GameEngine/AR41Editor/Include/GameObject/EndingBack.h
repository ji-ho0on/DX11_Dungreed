#pragma once

#include "GameObject\GameObject.h"

class CEndingBack :
    public CGameObject
{
	friend class CScene;

protected:
	CEndingBack();
	CEndingBack(const CEndingBack& Obj);
	virtual ~CEndingBack();

private:
	CSharedPtr<class CSpriteComponent>	m_Back;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CEndingBack* Clone()    const;
};

