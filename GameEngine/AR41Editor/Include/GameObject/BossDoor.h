#pragma once

#include "GameObject\GameObject.h"

class CBossDoor :
    public CGameObject
{
	friend class CScene;

protected:
	CBossDoor();
	CBossDoor(const CBossDoor& Obj);
	virtual ~CBossDoor();

protected:
	CSharedPtr<class CSpriteComponent>	m_Door;
	CSharedPtr<class CColliderBox2D>	m_Body;

	CSharedPtr<class CSpriteComponent>	m_DoorInteraction;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBossDoor* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

private:
	void DoorCollision(const CollisionResult& Result);
	void DoorRelease(const CollisionResult& Result);
	void DoorEntrance();
};

