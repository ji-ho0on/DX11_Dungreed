#pragma once

#include "GameObject\GameObject.h"

class CNormalMap4 :
    public CGameObject
{
	friend class CScene;

protected:
	CNormalMap4();
	CNormalMap4(const CNormalMap4& Obj);
	virtual ~CNormalMap4();

private:
	CSharedPtr<class CTileMapComponent>	m_NormalMapTile;

private:
	CSharedPtr<class CColliderBox2D>	m_SceneTrigger;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CNormalMap4* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

public:
	void DoorClose();

private:
	void TriggerCollision(const CollisionResult& Result);
};

