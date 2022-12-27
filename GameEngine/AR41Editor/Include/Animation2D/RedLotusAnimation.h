#pragma once

#include "Animation\Animation2D.h"

class CRedLotusAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CRedLotusAnimation();
	CRedLotusAnimation(const CRedLotusAnimation& Anim);
	virtual ~CRedLotusAnimation();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CRedLotusAnimation* Clone();
};

