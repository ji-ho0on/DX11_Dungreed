#pragma once

#include "GameObject\GameObject.h"

class CNormalMap3 :
    public CGameObject
{
	friend class CScene;

protected:
	CNormalMap3();
	CNormalMap3(const CNormalMap3& Obj);
	virtual ~CNormalMap3();

private:
	CSharedPtr<class CTileMapComponent>	m_NormalMapTile;

private:
	CSharedPtr<class CColliderBox2D>	m_SceneTrigger1;
	CSharedPtr<class CColliderBox2D>	m_SceneTrigger2;
	CSharedPtr<class CColliderBox2D>	m_SceneTrigger3;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CNormalMap3* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

public:
	void DoorClose();

private:
	void TriggerCollision1(const CollisionResult& Result);
	void TriggerCollision2(const CollisionResult& Result);
	void TriggerCollision3(const CollisionResult& Result);
};

