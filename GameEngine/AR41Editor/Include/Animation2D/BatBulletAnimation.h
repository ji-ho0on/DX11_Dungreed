#pragma once

#include "Animation\Animation2D.h"

class CBatBulletAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CBatBulletAnimation();
	CBatBulletAnimation(const CBatBulletAnimation& Anim);
	virtual ~CBatBulletAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CBatBulletAnimation* Clone();

private:
	void DestroyEnd();
};

