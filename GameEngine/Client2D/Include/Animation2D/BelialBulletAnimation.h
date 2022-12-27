#pragma once

#include "Animation\Animation2D.h"

class CBelialBulletAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CBelialBulletAnimation();
	CBelialBulletAnimation(const CBelialBulletAnimation& Anim);
	virtual ~CBelialBulletAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CBelialBulletAnimation* Clone();

private:
	void DestroyEnd();
};

