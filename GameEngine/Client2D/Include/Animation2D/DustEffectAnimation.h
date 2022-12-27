#pragma once

#include "Animation\Animation2D.h"

class CDustEffectAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CDustEffectAnimation();
	CDustEffectAnimation(const CDustEffectAnimation& Anim);
	virtual ~CDustEffectAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CDustEffectAnimation* Clone();

private:
	void EffectEnd();
};

