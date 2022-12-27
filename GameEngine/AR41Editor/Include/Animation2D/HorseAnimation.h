#pragma once

#include "Animation\Animation2D.h"

class CHorseAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CHorseAnimation();
	CHorseAnimation(const CHorseAnimation& Anim);
	virtual ~CHorseAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CHorseAnimation* Clone();
};

