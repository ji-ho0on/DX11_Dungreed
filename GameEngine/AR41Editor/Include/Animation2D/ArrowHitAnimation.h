#pragma once

#include "Animation\Animation2D.h"

class CArrowHitAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CArrowHitAnimation();
	CArrowHitAnimation(const CArrowHitAnimation& Anim);
	virtual ~CArrowHitAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CArrowHitAnimation* Clone();

private:
	void ArrowHitEnd();
};

