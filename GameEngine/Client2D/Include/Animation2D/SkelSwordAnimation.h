#pragma once

#include "Animation\Animation2D.h"

class CSkelSwordAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CSkelSwordAnimation();
	CSkelSwordAnimation(const CSkelSwordAnimation& Anim);
	virtual ~CSkelSwordAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CSkelSwordAnimation* Clone();

	void AttackEnd();
};

