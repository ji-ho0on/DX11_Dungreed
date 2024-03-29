#pragma once

#include "Animation\Animation2D.h"

class CMetalPlateAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CMetalPlateAnimation();
	CMetalPlateAnimation(const CMetalPlateAnimation& Anim);
	virtual ~CMetalPlateAnimation();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CMetalPlateAnimation* Clone();
};

