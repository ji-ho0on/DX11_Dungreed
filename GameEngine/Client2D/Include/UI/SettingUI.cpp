#include "SettingUI.h"
#include "UI/UIImage.h"
#include "UI/UIButton.h"
#include "UI/UIText.h"
#include "Engine.h"
#include "Scene/SceneViewport.h"
#include "Device.h"
#include "Input.h"
#include "Resource/ResourceManager.h"
#include "Resource/Sound/Sound.h"

CSettingUI::CSettingUI()
{
    m_WindowTypeName = "SettingUI";
}

CSettingUI::CSettingUI(const CSettingUI& Window) :
    CUIWindow(Window)
{
}

CSettingUI::~CSettingUI()
{
}

void CSettingUI::Start()
{
    CUIWindow::Start();

    m_SettingExitButton->SetCallback<CSettingUI>(EButtonEventState::Click, this, &CSettingUI::SettingExitButtonClick);
    m_OptionArrowLeftButton->SetCallback<CSettingUI>(EButtonEventState::Click, this, &CSettingUI::OptionArrowButtonClick);
    m_OptionArrowRightButton->SetCallback<CSettingUI>(EButtonEventState::Click, this, &CSettingUI::OptionArrowButtonClick);
    m_ApplyButton->SetCallback<CSettingUI>(EButtonEventState::Click, this, &CSettingUI::ApplyButtonClick);
}

bool CSettingUI::Init()
{
    Resolution Resolution = CDevice::GetInst()->GetResolution();

    m_ScrollRect = CreateWidget<CUIImage>("ScrollRect");
    m_ScrollRect->SetTexture("ScrollRect", TEXT("MainScene/ScrollRect.png"));
    m_ScrollRect->SetSize((float)Resolution.Width + 40.f, (float)Resolution.Height + 40.f);
    m_ScrollRect->SetPos(-20.f, -20.f);
    m_ScrollRect->SetZOrder(3);

    m_OptionBase = CreateWidget<CUIImage>("OptionBase");
    m_OptionBase->SetTexture("OptionBase", TEXT("MainScene/OptionBase2.png"));
    m_OptionBase->SetSize((float)Resolution.Width, 100.f);
    m_OptionBase->SetPos(0.f, (float)Resolution.Height - 110.f);
    m_OptionBase->SetZOrder(2);

    m_SettingExitButton = CreateWidget<CUIButton>("SettingExitButton");
    m_SettingExitButton->SetTexture(EButtonState::Normal, "FullWindowExitButton", TEXT("MainScene/FullWindowExitButton.png"));
    m_SettingExitButton->SetTexture(EButtonState::Hovered, "FullWindowExitButton_Selected", TEXT("MainScene/FullWindowExitButton_Selected.png"));
    m_SettingExitButton->SetTexture(EButtonState::Click, "FullWindowExitButton_Selected", TEXT("MainScene/FullWindowExitButton_Selected.png"));
    m_SettingExitButton->SetSize(80.f, 70.f);
    m_SettingExitButton->SetPos(1190.f, 625);
    m_SettingExitButton->SetZOrder(0);

    m_SoundText = CreateWidget<CUIText>("SoundText");
    m_SoundText->SetText(TEXT("사운드"));
    m_SoundText->SetSize(150.f, 100.f);
    m_SoundText->SetFontSize(45.f);
    m_SoundText->SetColor(189, 189, 189);
    m_SoundText->SetAlignH(EText_Align_H::Center);
    m_SoundText->SetAlignV(EText_Align_V::Middle);
    m_SoundText->SetPos(((float)Resolution.Width - m_SoundText->GetSize().x) / 2.f, m_OptionBase->GetPos().y - 100.f);

    m_BGMText = CreateWidget<CUIText>("BGMText");
    m_BGMText->SetText(TEXT("음악 볼륨"));
    m_BGMText->SetSize(300.f, 100.f);
    m_BGMText->SetFontSize(45.f);
    m_BGMText->SetAlignH(EText_Align_H::Left);
    m_BGMText->SetAlignV(EText_Align_V::Middle);
    m_BGMText->SetPos(180.f, m_SoundText->GetPos().y - 100.f);

    m_BGMSoundBar = CreateWidget<CUIImage>("BGMSoundBar");
    m_BGMSoundBar->SetTexture("OptionSoundBar", TEXT("MainScene/OptionSoundBar.png"));
    m_BGMSoundBar->SetSize(400.f, 20.f);
    m_BGMSoundBar->SetPos(m_BGMText->GetPos() + Vector2(500.f, 40.f));

    m_BGMSoundHandle = CreateWidget<CUIImage>("BGMSoundHandle");
    m_BGMSoundHandle->SetTexture("OptionSoundHandle", TEXT("MainScene/OptionSoundHandle.png"));
    m_BGMSoundHandle->SetSize(30.f, 50.f);
    m_BGMSoundHandle->SetPos(m_BGMText->GetPos() + Vector2(700.f, 25.f));
    m_BGMSoundHandle->SetPivot(0.5f, 0.f);

    m_EffectSoundText = CreateWidget<CUIText>("EffectSoundText");
    m_EffectSoundText->SetText(TEXT("효과음 볼륨"));
    m_EffectSoundText->SetSize(300.f, 100.f);
    m_EffectSoundText->SetFontSize(45.f);
    m_EffectSoundText->SetAlignH(EText_Align_H::Left);
    m_EffectSoundText->SetAlignV(EText_Align_V::Middle);
    m_EffectSoundText->SetPos(180.f, m_BGMText->GetPos().y - 80.f);

    m_EffectSoundBar = CreateWidget<CUIImage>("EffectSoundBar");
    m_EffectSoundBar->SetTexture("OptionSoundBar", TEXT("MainScene/OptionSoundBar.png"));
    m_EffectSoundBar->SetSize(400.f, 20.f);
    m_EffectSoundBar->SetPos(m_EffectSoundText->GetPos() + Vector2(500.f, 40.f));

    m_EffectSoundHandle = CreateWidget<CUIImage>("EffectSoundHandle");
    m_EffectSoundHandle->SetTexture("OptionSoundHandle", TEXT("MainScene/OptionSoundHandle.png"));
    m_EffectSoundHandle->SetSize(30.f, 50.f);
    m_EffectSoundHandle->SetPos(m_EffectSoundText->GetPos() + Vector2(700.f, 25.f));
    m_EffectSoundHandle->SetPivot(0.5f, 0.f);



    m_ScreenText = CreateWidget<CUIText>("ScreenText");
    m_ScreenText->SetText(TEXT("화면"));
    m_ScreenText->SetSize(150.f, 100.f);
    m_ScreenText->SetFontSize(45.f);
    m_ScreenText->SetColor(189, 189, 189);
    m_ScreenText->SetAlignH(EText_Align_H::Center);
    m_ScreenText->SetAlignV(EText_Align_V::Middle);
    m_ScreenText->SetPos(((float)Resolution.Width - m_SoundText->GetSize().x) / 2.f, m_EffectSoundHandle->GetPos().y - 150.f);

    m_ScreenModeText = CreateWidget<CUIText>("ScreenModeText");
    m_ScreenModeText->SetText(TEXT("창모드"));
    m_ScreenModeText->SetSize(300.f, 100.f);
    m_ScreenModeText->SetFontSize(45.f);
    m_ScreenModeText->SetAlignH(EText_Align_H::Left);
    m_ScreenModeText->SetAlignV(EText_Align_V::Middle);
    m_ScreenModeText->SetPos(180.f, m_ScreenText->GetPos().y - 100.f);

    m_OptionArrowLeftButton = CreateWidget<CUIButton>("OptionArrowLeftButton");
    m_OptionArrowLeftButton->SetTexture(EButtonState::Normal, "OptionArrow0_LEft", TEXT("MainScene/OptionArrow0_LEft.png"));
    m_OptionArrowLeftButton->SetTexture(EButtonState::Hovered, "OptionArrow1_Left", TEXT("MainScene/OptionArrow1_Left.png"));
    m_OptionArrowLeftButton->SetTexture(EButtonState::Click, "OptionArrow1_Left", TEXT("MainScene/OptionArrow1_Left.png"));
    m_OptionArrowLeftButton->SetSize(65.f, 45.f);
    m_OptionArrowLeftButton->SetPos(m_ScreenModeText->GetPos() + Vector2(300.f, 27.5f));

    m_SelectScreenText = CreateWidget<CUIText>("SelectScreenText");
    m_SelectScreenText->SetText(TEXT("창화면"));
    m_SelectScreenText->SetSize(300.f, 100.f);
    m_SelectScreenText->SetFontSize(45.f);
    m_SelectScreenText->SetAlignH(EText_Align_H::Center);
    m_SelectScreenText->SetAlignV(EText_Align_V::Middle);
    m_SelectScreenText->SetPos(m_ScreenModeText->GetPos() + Vector2(450.f, 0.f));
    m_SelectScreenText->SetPivot(0.5f, 0.f);

    m_CurrentSceenMode = "창화면";

    m_OptionArrowRightButton = CreateWidget<CUIButton>("OptionArrowRightButton");
    m_OptionArrowRightButton->SetTexture(EButtonState::Normal, "OptionArrow0", TEXT("MainScene/OptionArrow0.png"));
    m_OptionArrowRightButton->SetTexture(EButtonState::Hovered, "OptionArrow1", TEXT("MainScene/OptionArrow1.png"));
    m_OptionArrowRightButton->SetTexture(EButtonState::Click, "OptionArrow1", TEXT("MainScene/OptionArrow1.png"));
    m_OptionArrowRightButton->SetSize(65.f, 45.f);
    m_OptionArrowRightButton->SetPos(m_ScreenModeText->GetPos() + Vector2(800.f, 27.5f));


    m_ApplyButton = CreateWidget<CUIButton>("ApplyButton");
    m_ApplyButton->SetTexture(EButtonState::Normal, "ApplyButton", TEXT("MainScene/ApplyButton.png"));
    m_ApplyButton->SetTexture(EButtonState::Hovered, "ApplyButton_Selected", TEXT("MainScene/ApplyButton_Selected.png"));
    m_ApplyButton->SetTexture(EButtonState::Click, "ApplyButton_Selected", TEXT("MainScene/ApplyButton_Selected.png"));
    m_ApplyButton->SetSize(460.f, 95.f);
    m_ApplyButton->SetPos(((float)Resolution.Width - m_ApplyButton->GetSize().x) / 2.f, m_ScreenModeText->GetPos().y -100.f);

    m_ApplyText = CreateWidget<CUIText>("ApplyText");
    m_ApplyText->SetText(TEXT("적용"));
    m_ApplyText->SetSize(150.f, 100.f);
    m_ApplyText->SetFontSize(45.f);
    m_ApplyText->SetAlignH(EText_Align_H::Center);
    m_ApplyText->SetAlignV(EText_Align_V::Middle);
    m_ApplyText->SetPos(((float)Resolution.Width - m_ApplyText->GetSize().x) / 2.f, m_ApplyButton->GetPos().y);

    return true;
}

void CSettingUI::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);

    // 마우스 클릭을 받아서 마우스 위치가 범위에 들어왔을 때 SoundHandle 위치를 이동 시키고 사운드도 조절한다.

    // BGM : Pos = 680,450 Size = 400,20
    // Effect : Pos = 680,370 Size = 400,20

    if (GetEnable() && CInput::GetInst()->GetMouseLDown())
    {
        Vector2 MousePos = CInput::GetInst()->GetMouseWorldPos();

        if (MousePos.x >= 680.f && MousePos.x <= 1080.f)
        {
            if (MousePos.y >= 450.f && MousePos.y <= 470.f)
            {
                // BGM Sound 조절
                m_BGMSoundHandle->SetPos(MousePos.x, 435.f);

                int Volume = (int)((MousePos.x - 680.f) / 4.f);

                CResourceManager::GetInst()->SetVolume("BGM", Volume);
            }

            else if (MousePos.y >= 370.f && MousePos.y <= 390.f)
            {
                // Effect Sound 조절
                m_EffectSoundHandle->SetPos(MousePos.x, 355.f);

                int Volume = (int)((MousePos.x - 680.f) / 4.f);

                CResourceManager::GetInst()->SetVolume("Effect", Volume);
                CSound* Sound = CResourceManager::GetInst()->FindSound("Swing1");

                if (Sound)
                    Sound->Play();
            }
        }
    }
}

void CSettingUI::PostUpdate(float DeltaTime)
{
    CUIWindow::PostUpdate(DeltaTime);
}

void CSettingUI::Render()
{
    CUIWindow::Render();
}

CSettingUI* CSettingUI::Clone()
{
    return new CSettingUI(*this);
}

void CSettingUI::Save(FILE* File)
{
    CUIWindow::Save(File);
}

void CSettingUI::Load(FILE* File)
{
    CUIWindow::Load(File);
}

void CSettingUI::SettingExitButtonClick()
{
    SetEnable(false);
}

void CSettingUI::OptionArrowButtonClick()
{
    if (m_CurrentSceenMode == "창화면")
    {
        m_SelectScreenText->SetText(TEXT("전체화면"));
        m_CurrentSceenMode = "전체화면";
    }
    
    else
    {
        m_SelectScreenText->SetText(TEXT("창화면"));
        m_CurrentSceenMode = "창화면";
    }
}

void CSettingUI::ApplyButtonClick()
{
}
