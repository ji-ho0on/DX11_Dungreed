#pragma once

#include "Animation\Animation2D.h"

class CShortSwordSwing :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CShortSwordSwing();
	CShortSwordSwing(const CShortSwordSwing& Anim);
	virtual ~CShortSwordSwing();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CShortSwordSwing* Clone();

private:
	void ShortSwordSwingEnd();
};

