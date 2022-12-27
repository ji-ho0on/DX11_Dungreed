#pragma once

#include "GameObject\GameObject.h"

class CNormalMap1 :
    public CGameObject
{
	friend class CScene;

protected:
	CNormalMap1();
	CNormalMap1(const CNormalMap1& Obj);
	virtual ~CNormalMap1();

private:
	CSharedPtr<class CTileMapComponent>	m_NormalMapTile;

private:
	CSharedPtr<class CColliderBox2D>	m_NextSceneTrigger;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CNormalMap1* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

public:
	void DoorClose();

private:
	void TriggerCollision(const CollisionResult& Result);
};

