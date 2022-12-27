#pragma once

#include "GameObject\GameObject.h"

class CBird :
    public CGameObject
{
	friend class CScene;

protected:
	CBird();
	CBird(const CBird& Obj);
	virtual ~CBird();

private:
	CSharedPtr<class CSpriteComponent>	m_Bird;
	float								m_MapWidth;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBird* Clone()    const;
};

