#pragma once

#include "Animation\Animation2D.h"

class CBelialHandAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CBelialHandAnimation();
	CBelialHandAnimation(const CBelialHandAnimation& Anim);
	virtual ~CBelialHandAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CBelialHandAnimation* Clone();

private:
	void Attack();
	void AttackEnd();
};

