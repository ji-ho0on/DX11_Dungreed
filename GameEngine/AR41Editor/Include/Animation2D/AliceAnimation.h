#pragma once

#include "Animation\Animation2D.h"

class CAliceAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CAliceAnimation();
	CAliceAnimation(const CAliceAnimation& Anim);
	virtual ~CAliceAnimation();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CAliceAnimation* Clone();
};

