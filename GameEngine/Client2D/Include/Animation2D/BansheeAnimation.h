#pragma once

#include "Animation\Animation2D.h"

class CBansheeAnimation :
    public CAnimation2D
{
	friend class CSpriteComponent;
	friend class CSceneManager;
	friend class CScene;

protected:
	CBansheeAnimation();
	CBansheeAnimation(const CBansheeAnimation& Anim);
	virtual ~CBansheeAnimation();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual CBansheeAnimation* Clone();

private:
	void SummonBullet();
	void AttackEnd();
};

