#pragma once

#include "Animation\Animation2D.h"

class CTestAnimation2D :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CTestAnimation2D();
	CTestAnimation2D(const CTestAnimation2D& Anim);
	virtual ~CTestAnimation2D();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CTestAnimation2D* Clone();
};

