#pragma once

#include "Animation\Animation2D.h"

class CBelialBackAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CBelialBackAnimation();
	CBelialBackAnimation(const CBelialBackAnimation& Anim);
	virtual ~CBelialBackAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CBelialBackAnimation* Clone();
};

