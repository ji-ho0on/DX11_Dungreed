#pragma once

#include "GameObject\GameObject.h"

class CBossMap :
    public CGameObject
{
	friend class CScene;

protected:
	CBossMap();
	CBossMap(const CBossMap& Obj);
	virtual ~CBossMap();

private:
	CSharedPtr<class CTileMapComponent>	m_BossMapTile;

private:
	CSharedPtr<class CColliderBox2D>	m_BossTrigger;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBossMap* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

private:
	void TriggerCollision(const CollisionResult& Result);
};

