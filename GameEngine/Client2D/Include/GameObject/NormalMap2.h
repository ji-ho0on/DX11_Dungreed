#pragma once

#include "GameObject\GameObject.h"

class CNormalMap2 :
    public CGameObject
{
	friend class CScene;

protected:
	CNormalMap2();
	CNormalMap2(const CNormalMap2& Obj);
	virtual ~CNormalMap2();

private:
	CSharedPtr<class CTileMapComponent>	m_NormalMapTile;

private:
	CSharedPtr<class CColliderBox2D>	m_PrevSceneTrigger;
	CSharedPtr<class CColliderBox2D>	m_NextSceneTrigger;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CNormalMap2* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

public:
	void DoorClose();

private:
	void TriggerCollision1(const CollisionResult& Result);
	void TriggerCollision2(const CollisionResult& Result);
};

