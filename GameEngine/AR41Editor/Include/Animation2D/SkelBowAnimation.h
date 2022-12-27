#pragma once

#include "Animation\Animation2D.h"

class CSkelBowAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CSkelBowAnimation();
	CSkelBowAnimation(const CSkelBowAnimation& Anim);
	virtual ~CSkelBowAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CSkelBowAnimation* Clone();

private:
	void AttackStart();
	void AttackEnd();
};

