#pragma once

#include "Animation\Animation2D.h"

class CPortalAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CPortalAnimation();
	CPortalAnimation(const CPortalAnimation& Anim);
	virtual ~CPortalAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CPortalAnimation* Clone();

private:
	void PortalCreateEnd();
};

