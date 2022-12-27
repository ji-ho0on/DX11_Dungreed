#pragma once

#include "GameObject\GameObject.h"

class CEndingTree :
    public CGameObject
{
	friend class CScene;

protected:
	CEndingTree();
	CEndingTree(const CEndingTree& Obj);
	virtual ~CEndingTree();

private:
	CSharedPtr<class CSpriteComponent>	m_Tree;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CEndingTree* Clone()    const;
};

