#pragma once

#include "Animation\Animation2D.h"

class CJumpEffectAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CJumpEffectAnimation();
	CJumpEffectAnimation(const CJumpEffectAnimation& Anim);
	virtual ~CJumpEffectAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CJumpEffectAnimation* Clone();

private:
	void EffectEnd();
};