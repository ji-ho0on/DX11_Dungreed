#pragma once

#include "Animation\Animation2D.h"

class CBelialLaserAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CBelialLaserAnimation();
	CBelialLaserAnimation(const CBelialLaserAnimation& Anim);
	virtual ~CBelialLaserAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CBelialLaserAnimation* Clone();

private:
	void ColliderDestroy();
	void LaserEnd();
};

