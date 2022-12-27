#pragma once

#include "Animation\Animation2D.h"

class CRedBatAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CRedBatAnimation();
	CRedBatAnimation(const CRedBatAnimation& Anim);
	virtual ~CRedBatAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CRedBatAnimation* Clone();

private:
	void SummonBullet();
	void AttackEnd();
};

