#pragma once

#include "UI\UIWindow.h"

class CEndingUI :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CEndingUI();
	CEndingUI(const CEndingUI& Window);
	virtual ~CEndingUI();

protected:
	CSharedPtr<class CUIImage>	m_EndingBackImage;

	CSharedPtr<class CUIImage>	m_MainLogoImage;

	CSharedPtr<class CUIText>	m_EndingText;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CEndingUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

