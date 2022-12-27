#pragma once

#include "Animation\Animation2D.h"

class CGoldAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CGoldAnimation();
	CGoldAnimation(const CGoldAnimation& Anim);
	virtual ~CGoldAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CGoldAnimation* Clone();
};

