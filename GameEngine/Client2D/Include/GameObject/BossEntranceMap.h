#pragma once

#include "GameObject\GameObject.h"

class CBossEntranceMap :
    public CGameObject
{
	friend class CScene;

protected:
	CBossEntranceMap();
	CBossEntranceMap(const CBossEntranceMap& Obj);
	virtual ~CBossEntranceMap();

private:
	CSharedPtr<class CTileMapComponent>	m_BossEntranceMapTile;
	CSharedPtr<class CSpriteComponent>	m_Door;

private:
	CSharedPtr<class CColliderBox2D>	m_NextSceneTrigger;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBossEntranceMap* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

public:
	void DoorClose();

private:
	void TriggerCollision(const CollisionResult& Result);
};

