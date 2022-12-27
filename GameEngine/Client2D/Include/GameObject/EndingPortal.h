#pragma once

#include "GameObject\GameObject.h"

class CEndingPortal :
    public CGameObject
{
	friend class CScene;

protected:
	CEndingPortal();
	CEndingPortal(const CEndingPortal& Obj);
	virtual ~CEndingPortal();

protected:
	CSharedPtr<class CColliderBox2D>	m_Body;
	CSharedPtr<class CSpriteComponent>	m_Portal;
	CSharedPtr<class CSpriteComponent>	m_PortalInteraction;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CEndingPortal* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

private:
	void PortalCollision(const CollisionResult& Result);
	void PortalRelease(const CollisionResult& Result);
	void PortalEntrance();
};

