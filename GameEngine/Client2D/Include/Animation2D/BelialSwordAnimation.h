#pragma once

#include "Animation\Animation2D.h"

class CBelialSwordAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CBelialSwordAnimation();
	CBelialSwordAnimation(const CBelialSwordAnimation& Anim);
	virtual ~CBelialSwordAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CBelialSwordAnimation* Clone();

private:
	void HitEnd();
};

