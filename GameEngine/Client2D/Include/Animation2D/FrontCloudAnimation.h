#pragma once

#include "Animation\Animation2D.h"

class CFrontCloudAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CFrontCloudAnimation();
	CFrontCloudAnimation(const CFrontCloudAnimation& Anim);
	virtual ~CFrontCloudAnimation();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CFrontCloudAnimation* Clone();
};

