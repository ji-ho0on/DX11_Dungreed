#pragma once

#include "Animation\Animation2D.h"

class CGhostAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CGhostAnimation();
	CGhostAnimation(const CGhostAnimation& Anim);
	virtual ~CGhostAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CGhostAnimation* Clone();

private:
	void AttackEnd();
};

