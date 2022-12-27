#pragma once

#include "Animation\Animation2D.h"

class CGiantNormalBatAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CGiantNormalBatAnimation();
	CGiantNormalBatAnimation(const CGiantNormalBatAnimation& Anim);
	virtual ~CGiantNormalBatAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CGiantNormalBatAnimation* Clone();

private:
	void SummonBullet();
	void AttackEnd();
};

