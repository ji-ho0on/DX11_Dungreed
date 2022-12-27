#pragma once

#include "Animation\Animation2D.h"

class CPickaxAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CPickaxAnimation();
	CPickaxAnimation(const CPickaxAnimation& Anim);
	virtual ~CPickaxAnimation();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CPickaxAnimation* Clone();
};

