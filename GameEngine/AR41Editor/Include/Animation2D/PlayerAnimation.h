#pragma once

#include "Animation\Animation2D.h"

class CPlayerAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CPlayerAnimation();
	CPlayerAnimation(const CPlayerAnimation& Anim);
	virtual ~CPlayerAnimation();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CPlayerAnimation* Clone();
};

