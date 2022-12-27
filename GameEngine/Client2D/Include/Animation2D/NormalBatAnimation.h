#pragma once

#include "Animation\Animation2D.h"

class CNormalBatAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CNormalBatAnimation();
	CNormalBatAnimation(const CNormalBatAnimation& Anim);
	virtual ~CNormalBatAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CNormalBatAnimation* Clone();
};

