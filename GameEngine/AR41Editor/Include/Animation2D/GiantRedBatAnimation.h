#pragma once

#include "Animation\Animation2D.h"

class CGiantRedBatAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CGiantRedBatAnimation();
	CGiantRedBatAnimation(const CGiantRedBatAnimation& Anim);
	virtual ~CGiantRedBatAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CGiantRedBatAnimation* Clone();
};

