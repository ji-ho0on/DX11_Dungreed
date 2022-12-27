#pragma once

#include "Animation\Animation2D.h"

class CBansheeBulletAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CBansheeBulletAnimation();
	CBansheeBulletAnimation(const CBansheeBulletAnimation& Anim);
	virtual ~CBansheeBulletAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CBansheeBulletAnimation* Clone();

private:
	void DestroyEnd();
};

