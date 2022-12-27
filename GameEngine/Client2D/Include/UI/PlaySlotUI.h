#pragma once

#include "UI\UIWindow.h"

class CPlaySlotUI :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CPlaySlotUI();
	CPlaySlotUI(const CPlaySlotUI& Window);
	virtual ~CPlaySlotUI();

protected:
	CSharedPtr<class CUIImage>	m_SlotBackImage;

	CSharedPtr<class CUIButton>	m_SlotButton1;
	CSharedPtr<class CUIButton>	m_SlotButton2;
	CSharedPtr<class CUIButton>	m_SlotButton3;

	CSharedPtr<class CUIImage>	m_SlotImage1;
	CSharedPtr<class CUIImage>	m_SlotImage2;
	CSharedPtr<class CUIImage>	m_SlotImage3;

	CSharedPtr<class CUIButton> m_SlotDeleteButton1;
	CSharedPtr<class CUIButton> m_SlotDeleteButton2;
	CSharedPtr<class CUIButton> m_SlotDeleteButton3;

	CSharedPtr<class CUIText>	m_SlotDeleteText1;
	CSharedPtr<class CUIText>	m_SlotDeleteText2;
	CSharedPtr<class CUIText>	m_SlotDeleteText3;

	CSharedPtr<class CUIButton>	m_SlotExitButton;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CPlaySlotUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

private:
	void SlotButton1Click();
	void SlotButton2Click();
	void SlotButton3Click();
	void SlotExitButtonClick();
};

