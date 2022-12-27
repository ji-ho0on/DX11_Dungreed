#pragma once

#include "Animation\Animation2D.h"

class CMonsterDestroyAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CMonsterDestroyAnimation();
	CMonsterDestroyAnimation(const CMonsterDestroyAnimation& Anim);
	virtual ~CMonsterDestroyAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CMonsterDestroyAnimation* Clone();

private:
	void DestroyEnd();
};

