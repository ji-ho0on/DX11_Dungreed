#pragma once

#include "Animation\Animation2D.h"

class CCharacterAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CCharacterAnimation();
	CCharacterAnimation(const CCharacterAnimation& Anim);
	virtual ~CCharacterAnimation();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CCharacterAnimation* Clone();
};

