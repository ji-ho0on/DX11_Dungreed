#pragma once

#include "Animation\Animation2D.h"

class CBelialHeadAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CBelialHeadAnimation();
	CBelialHeadAnimation(const CBelialHeadAnimation& Anim);
	virtual ~CBelialHeadAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CBelialHeadAnimation* Clone();
};

