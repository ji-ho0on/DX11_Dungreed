#pragma once

#include "Animation\Animation2D.h"

class CDoorAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CDoorAnimation();
	CDoorAnimation(const CDoorAnimation& Anim);
	virtual ~CDoorAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CDoorAnimation* Clone();
};

