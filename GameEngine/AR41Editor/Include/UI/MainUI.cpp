#include "MainUI.h"
#include "UI/UIImage.h"
#include "UI/UIButton.h"
#include "Engine.h"
#include "Scene/SceneViewport.h"
#include "PlaySlotUI.h"
#include "SettingUI.h"

CMainUI::CMainUI()
{
    m_WindowTypeName = "MainUI";
}

CMainUI::CMainUI(const CMainUI& Window) :
    CUIWindow(Window)
{
    m_MainLogoImage = FindWidget<CUIImage>("MainLogo");
    m_PlayButton = FindWidget<CUIButton>("PlayButton");
    m_OptionButton = FindWidget<CUIButton>("OptionButton");
    m_ExitButton = FindWidget<CUIButton>("ExitButton");
    m_CopyrightImage = FindWidget<CUIImage>("Copyright");
}

CMainUI::~CMainUI()
{
}

void CMainUI::Start()
{
    CUIWindow::Start();

    m_PlayButton->SetCallback<CMainUI>(EButtonEventState::Click, this, &CMainUI::PlayButtonClick);
    m_OptionButton->SetCallback<CMainUI>(EButtonEventState::Click, this, &CMainUI::OptionButtonClick);
    m_ExitButton->SetCallback<CMainUI>(EButtonEventState::Click, this, &CMainUI::ExitButtonClick);
}

bool CMainUI::Init()
{
    m_MainLogoImage = CreateWidget<CUIImage>("MainLogo");
    m_MainLogoImage->SetTexture("MainLogoImage", TEXT("MainScene/MainLogo.png"));

    m_MainLogoImage->SetSize(620.f, 300.f);
    m_MainLogoImage->SetPos(330.f, 300.f);

    m_PlayButton = CreateWidget<CUIButton>("PlayButton");
    m_PlayButton->SetTexture(EButtonState::Normal, "PlayOff_Kor", TEXT("MainScene/PlayOff_Kor.png"));
    m_PlayButton->SetTexture(EButtonState::Hovered, "PlayOn_Kor", TEXT("MainScene/PlayOn_Kor.png"));
    m_PlayButton->SetTexture(EButtonState::Click, "PlayOn_Kor", TEXT("MainScene/PlayOn_Kor.png"));
    m_PlayButton->SetSize(140.f, 50.f);
    m_PlayButton->SetPos(m_Size.x / 2.f - 70.f, 200.f);
    //m_PlayButton->SetCallback<CMainUI>(EButtonEventState::Click, this, &CMainUI::PlayButtonClick);


    m_OptionButton = CreateWidget<CUIButton>("OptionButton");
    m_OptionButton->SetTexture(EButtonState::Normal, "OptionOff_Kor", TEXT("MainScene/OptionOff_Kor.png"));
    m_OptionButton->SetTexture(EButtonState::Hovered, "OptionOn_Kor", TEXT("MainScene/OptionOn_Kor.png"));
    m_OptionButton->SetTexture(EButtonState::Click, "OptionOn_Kor", TEXT("MainScene/OptionOn_Kor.png"));
    m_OptionButton->SetSize(60.f, 50.f);
    m_OptionButton->SetPos(m_Size.x / 2.f - 30.f, 150.f);
    //m_OptionButton->SetCallback<CMainUI>(EButtonEventState::Click, this, &CMainUI::OptionButtonClick);


    m_ExitButton = CreateWidget<CUIButton>("ExitButton");
    m_ExitButton->SetTexture(EButtonState::Normal, "ExitOff_Kor", TEXT("MainScene/ExitOff_Kor.png"));
    m_ExitButton->SetTexture(EButtonState::Hovered, "ExitOn_Kor", TEXT("MainScene/ExitOn_Kor.png"));
    m_ExitButton->SetTexture(EButtonState::Click, "ExitOn_Kor", TEXT("MainScene/ExitOn_Kor.png"));
    m_ExitButton->SetSize(66.f, 50.f);
    m_ExitButton->SetPos(m_Size.x / 2.f - 33.f, 100.f);
    //m_ExitButton->SetCallback<CMainUI>(EButtonEventState::Click, this, &CMainUI::ExitButtonClick);

    m_CopyrightImage = CreateWidget<CUIImage>("Copyright");
    m_CopyrightImage->SetTexture("CopyrightImage", TEXT("MainScene/Copyright.png"));

    m_CopyrightImage->SetSize(680.f, 40.f);
    m_CopyrightImage->SetPos(300.f, 10.f);

    return true;
}

void CMainUI::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);
}

void CMainUI::PostUpdate(float DeltaTime)
{
    CUIWindow::PostUpdate(DeltaTime);
}

void CMainUI::Render()
{
    CUIWindow::Render();
}

CMainUI* CMainUI::Clone()
{
    return new CMainUI(*this);
}

void CMainUI::Save(FILE* File)
{
    CUIWindow::Save(File);
}

void CMainUI::Load(FILE* File)
{
    CUIWindow::Load(File);

    m_MainLogoImage = FindWidget<CUIImage>("MainLogo");
    m_PlayButton = FindWidget<CUIButton>("PlayButton");
    m_OptionButton = FindWidget<CUIButton>("OptionButton");
    m_ExitButton = FindWidget<CUIButton>("ExitButton");
    m_CopyrightImage = FindWidget<CUIImage>("Copyright");
}

void CMainUI::PlayButtonClick()
{
    CPlaySlotUI* PlaySlotUI = m_Owner->FindUIWindow<CPlaySlotUI>("PlaySlotUI");
    
    if(PlaySlotUI)
        PlaySlotUI->SetEnable(true);
}

void CMainUI::OptionButtonClick()
{
    CSettingUI* SettingUI = m_Owner->FindUIWindow<CSettingUI>("SettingUI");

    if (SettingUI)
        SettingUI->SetEnable(true);
}

void CMainUI::ExitButtonClick()
{
    CEngine::GetInst()->Exit();
}
