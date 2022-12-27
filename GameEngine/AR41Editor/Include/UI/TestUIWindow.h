#pragma once

#include "UI\UIWindow.h"

class CTestUIWindow :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CTestUIWindow();
	CTestUIWindow(const CTestUIWindow& Window);
	virtual ~CTestUIWindow();

protected:
	CSharedPtr<class CUIButton>			m_TestButton;
	CSharedPtr<class CUIText>			m_TestText;
	CSharedPtr<class CUIProgressBar>	m_TestProgressBar;
	CSharedPtr<class CUINumber>			m_TestNumber;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CTestUIWindow* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

