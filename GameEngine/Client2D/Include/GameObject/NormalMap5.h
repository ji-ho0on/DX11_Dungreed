#pragma once

#include "GameObject\GameObject.h"

class CNormalMap5 :
    public CGameObject
{
	friend class CScene;

protected:
	CNormalMap5();
	CNormalMap5(const CNormalMap5& Obj);
	virtual ~CNormalMap5();

private:
	CSharedPtr<class CTileMapComponent>	m_NormalMapTile;

private:
	CSharedPtr<class CColliderBox2D>	m_SceneTrigger1;
	CSharedPtr<class CColliderBox2D>	m_SceneTrigger2;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CNormalMap5* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

public:
	void DoorClose();

private:
	void TriggerCollision1(const CollisionResult& Result);
	void TriggerCollision2(const CollisionResult& Result);
};

