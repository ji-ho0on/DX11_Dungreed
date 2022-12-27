#pragma once
#include "UI\UIWindow.h"
class CSettingUI :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CSettingUI();
	CSettingUI(const CSettingUI& Window);
	virtual ~CSettingUI();

private:
	CSharedPtr<class CUIImage>	m_ScrollRect;
	CSharedPtr<class CUIImage>	m_OptionBase;
	CSharedPtr<class CUIButton>	m_SettingExitButton;

	CSharedPtr<class CUIText>	m_SoundText;

	CSharedPtr<class CUIText>	m_BGMText;
	CSharedPtr<class CUIImage>	m_BGMSoundBar;
	CSharedPtr<class CUIImage>	m_BGMSoundHandle;

	CSharedPtr<class CUIText>	m_EffectSoundText;
	CSharedPtr<class CUIImage>	m_EffectSoundBar;
	CSharedPtr<class CUIImage>	m_EffectSoundHandle;

	CSharedPtr<class CUIText>	m_ScreenText;

	CSharedPtr<class CUIText>	m_ScreenModeText;

	std::string					m_CurrentSceenMode;
	CSharedPtr<class CUIButton>	m_OptionArrowLeftButton;
	CSharedPtr<class CUIText>	m_SelectScreenText;
	CSharedPtr<class CUIButton>	m_OptionArrowRightButton;

	CSharedPtr<class CUIButton>	m_ApplyButton;
	CSharedPtr<class CUIText>	m_ApplyText;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CSettingUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

private:
	void SettingExitButtonClick();
	void OptionArrowButtonClick();
	void ApplyButtonClick();
};

