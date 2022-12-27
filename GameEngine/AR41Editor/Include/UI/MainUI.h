#pragma once

#include "UI\UIWindow.h"

class CMainUI :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CMainUI();
	CMainUI(const CMainUI& Window);
	virtual ~CMainUI();

protected:
	CSharedPtr<class CUIImage>	m_MainLogoImage;

	CSharedPtr<class CUIButton>	m_PlayButton;
	CSharedPtr<class CUIButton>	m_OptionButton;
	CSharedPtr<class CUIButton>	m_ExitButton;

	CSharedPtr<class CUIImage>	m_CopyrightImage;


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CMainUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

private:
	void PlayButtonClick();
	void OptionButtonClick();
	void ExitButtonClick();
};

