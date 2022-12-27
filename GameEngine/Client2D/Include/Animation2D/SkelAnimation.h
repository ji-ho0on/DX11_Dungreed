#pragma once

#include "Animation\Animation2D.h"

class CSkelAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CSkelAnimation();
	CSkelAnimation(const CSkelAnimation& Anim);
	virtual ~CSkelAnimation();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CSkelAnimation* Clone();
};

