#pragma once

#include "Animation\Animation2D.h"

class CBirdAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CBirdAnimation();
	CBirdAnimation(const CBirdAnimation& Anim);
	virtual ~CBirdAnimation();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CBirdAnimation* Clone();
};

