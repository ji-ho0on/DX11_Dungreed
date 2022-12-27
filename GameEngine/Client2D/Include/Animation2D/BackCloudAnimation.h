#pragma once

#include "Animation\Animation2D.h"

class CBackCloudAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CBackCloudAnimation();
	CBackCloudAnimation(const CBackCloudAnimation& Anim);
	virtual ~CBackCloudAnimation();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CBackCloudAnimation* Clone();
};

