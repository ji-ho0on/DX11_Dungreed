#pragma once

#include "GameObject\GameObject.h"

class CHorse :
    public CGameObject
{
	friend class CScene;

protected:
	CHorse();
	CHorse(const CHorse& Obj);
	virtual ~CHorse();

private:
	CSharedPtr<class CSpriteComponent>	m_Horse;
	CSharedPtr<class CSpriteComponent>	m_Character;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CHorse* Clone()    const;
};

