#pragma once

#include "UI\UIWindow.h"

class CCharacterHitUI :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CCharacterHitUI();
	CCharacterHitUI(const CCharacterHitUI& Window);
	virtual ~CCharacterHitUI();

private:
	class CUIImage* m_RedWarningLeft;
	class CUIImage* m_RedWarningRight;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CCharacterHitUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

