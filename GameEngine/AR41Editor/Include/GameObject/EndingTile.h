#pragma once

#include "GameObject\GameObject.h"

class CEndingTile :
    public CGameObject
{
	friend class CScene;

protected:
	CEndingTile();
	CEndingTile(const CEndingTile& Obj);
	virtual ~CEndingTile();

private:
	CSharedPtr<class CSpriteComponent>	m_EndingTile;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CEndingTile* Clone()    const;
};

