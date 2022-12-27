#include "EndingUI.h"
#include "UI/UIImage.h"
#include "UI/UIButton.h"
#include "UI/UIText.h"
#include "Device.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Sound/Sound.h"
#include "Scene/SceneManager.h"
#include "PathManager.h"

CEndingUI::CEndingUI()
{
    m_WindowTypeName = "EndingUI";
}

CEndingUI::CEndingUI(const CEndingUI& Window) :
    CUIWindow(Window)
{
    m_EndingBackImage = FindWidget<CUIImage>("EndingBack");
    m_MainLogoImage = FindWidget<CUIImage>("MainLogo");
    m_EndingText = FindWidget<CUIText>("EndingText");
}

CEndingUI::~CEndingUI()
{
}

void CEndingUI::Start()
{
    CUIWindow::Start();
}

bool CEndingUI::Init()
{
    Resolution Resolution = CDevice::GetInst()->GetResolution();

    SetSize(700.f, (float)Resolution.Height);
    SetPos(580.f, 0.f);

    m_EndingBackImage = CreateWidget<CUIImage>("EndingBack");
    m_EndingBackImage->SetSize(700.f, (float)Resolution.Height);
    m_EndingBackImage->SetTint(Vector4::Black);
    m_EndingBackImage->SetOpacity(0.7f);
    m_EndingBackImage->SetZOrder(2);

    m_MainLogoImage = CreateWidget<CUIImage>("MainLogo");
    m_MainLogoImage->SetTexture("MainLogoImage", TEXT("MainScene/MainLogo.png"));
    m_MainLogoImage->SetSize(580.f, 300.f);
    m_MainLogoImage->SetPos(60.f, 380.f);
    m_MainLogoImage->SetZOrder(1);

    m_EndingText = CreateWidget<CUIText>("EndingText");
    m_EndingText->SetText(TEXT("By  CJH"));
    m_EndingText->SetSize(200.f, 50.f);
    m_EndingText->SetFontSize(50.f);
    m_EndingText->SetAlignH(EText_Align_H::Center);
    m_EndingText->SetAlignV(EText_Align_V::Middle);
    m_EndingText->SetPos(250.f, 250.f);
    m_EndingText->SetZOrder(1);

    return true;
}

void CEndingUI::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);
}

void CEndingUI::PostUpdate(float DeltaTime)
{
    CUIWindow::PostUpdate(DeltaTime);
}

void CEndingUI::Render()
{
    CUIWindow::Render();
}

CEndingUI* CEndingUI::Clone()
{
    return new CEndingUI(*this);
}

void CEndingUI::Save(FILE* File)
{
    CUIWindow::Save(File);
}

void CEndingUI::Load(FILE* File)
{
    CUIWindow::Load(File);
}