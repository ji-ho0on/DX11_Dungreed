#include "CharacterLBUI.h"
#include "UI/UIProgressBar.h"
#include "UI/UIImage.h"
#include "UI/UIText.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Device.h"

CCharacterLBUI::CCharacterLBUI()
{
    m_WindowTypeName = "CharacterLBUI";
}

CCharacterLBUI::CCharacterLBUI(const CCharacterLBUI& Window) :
    CUIWindow(Window)
{
    m_GoldImage = FindWidget<CUIImage>("GoldImage");
    m_Gold = FindWidget<CUIText>("Gold");

    m_FoodImage = FindWidget<CUIImage>("FoodImage");
    m_Satiety = FindWidget<CUIText>("Satiety");
    m_SatietySlash = FindWidget<CUIText>("SatietySlash");
    m_SatietyMax = FindWidget<CUIText>("SatietyMax");
}

CCharacterLBUI::~CCharacterLBUI()
{
}

void CCharacterLBUI::SetGold(int Gold)
{
    int _Gold = Gold;

    if (Gold < 0)
        _Gold = 0;

    char GoldName[128] = {};

    _itoa_s(_Gold, GoldName, 10);

    TCHAR ConvertGoldName[128] = {};

    int	ConvertLength = MultiByteToWideChar(CP_ACP, 0, GoldName, -1, nullptr, 0);
    MultiByteToWideChar(CP_ACP, 0, GoldName, -1, ConvertGoldName, ConvertLength);

    m_Gold->SetText(ConvertGoldName);
}

void CCharacterLBUI::SetSatiety(int Satiety)
{
    int _Satiety = Satiety;

    if (Satiety < 0)
        _Satiety = 0;

    char SatietyName[4] = {};

    _itoa_s(_Satiety, SatietyName, 10);

    TCHAR ConvertSatietyName[4] = {};

    int	ConvertLength = MultiByteToWideChar(CP_ACP, 0, SatietyName, -1, nullptr, 0);
    MultiByteToWideChar(CP_ACP, 0, SatietyName, -1, ConvertSatietyName, ConvertLength);

    m_Satiety->SetText(ConvertSatietyName);
}

void CCharacterLBUI::SetSatietyMax(int SatietyMax)
{
    int _SatietyMax = SatietyMax;

    if (SatietyMax < 0)
        _SatietyMax = 0;

    char SatietyMaxName[4] = {};

    _itoa_s(_SatietyMax, SatietyMaxName, 10);

    TCHAR ConvertSatietyMaxName[4] = {};

    int	ConvertLength = MultiByteToWideChar(CP_ACP, 0, SatietyMaxName, -1, nullptr, 0);
    MultiByteToWideChar(CP_ACP, 0, SatietyMaxName, -1, ConvertSatietyMaxName, ConvertLength);

    m_SatietyMax->SetText(ConvertSatietyMaxName);
}

void CCharacterLBUI::Start()
{
    CUIWindow::Start();
}

bool CCharacterLBUI::Init()
{
    CUIWindow::Init();

    Resolution Resolution = CDevice::GetInst()->GetResolution();

    SetSize((float)Resolution.Width / 8.f, (float)Resolution.Height / 8.f);
    SetPos(0.f, 0.f);

    m_GoldImage = CreateWidget<CUIImage>("GoldImage");
    m_GoldImage->SetTexture("GoldCoin0", TEXT("gameScene/ui/GoldCoin0.png"));
    m_GoldImage->SetSize(25.f, 25.f);
    m_GoldImage->SetPos(22.f, m_Size.y * 3.f / 5.f);
    m_GoldImage->SetZOrder(1);

    m_Gold = CreateWidget<CUIText>("Gold");
    m_Gold->SetFont("NumberFont");
    m_Gold->SetFontSize(29.f);
    m_Gold->SetAlignH(EText_Align_H::Left);
    m_Gold->SetAlignV(EText_Align_V::Middle);
    m_Gold->SetSize(140.f, m_Size.y / 2.f);
    m_Gold->SetPos(m_Size.x * 0.4f, m_Size.y / 2.f);
    m_Gold->SetText(TEXT("0"));
    m_Gold->SetZOrder(1);

    m_FoodImage = CreateWidget<CUIImage>("Food");
    m_FoodImage->SetTexture("Food", TEXT("gameScene/ui/Food.png"));
    m_FoodImage->SetSize(30.f, 30.f);
    m_FoodImage->SetPos(20.f, m_Size.y * 1.f / 10.f);
    m_FoodImage->SetZOrder(1);

    m_Satiety = CreateWidget<CUIText>("Satiety");
    m_Satiety->SetFont("NumberFont");
    m_Satiety->SetFontSize(30.f);
    m_Satiety->SetAlignH(EText_Align_H::Left);
    m_Satiety->SetAlignV(EText_Align_V::Middle);
    m_Satiety->SetSize(50.f, m_Size.y / 2.f);
    m_Satiety->SetPos(m_Size.x * 0.4f, 0.f);
    m_Satiety->SetText(TEXT("0"));
    m_Satiety->SetZOrder(1);

    m_SatietySlash = CreateWidget<CUIText>("SatietySlash");
    m_SatietySlash->SetFont("NumberFont");
    m_SatietySlash->SetFontSize(30.f);
    m_SatietySlash->SetAlignH(EText_Align_H::Center);
    m_SatietySlash->SetAlignV(EText_Align_V::Middle);
    m_SatietySlash->SetSize(20.f, m_Size.y / 2.f);
    m_SatietySlash->SetPos(m_Satiety->GetPos().x + m_Satiety->GetSize().x, 0.f);
    m_SatietySlash->SetText(TEXT("/"));
    m_SatietySlash->SetZOrder(1);

    m_SatietyMax = CreateWidget<CUIText>("SatietyMax");
    m_SatietyMax->SetFont("NumberFont");
    m_SatietyMax->SetFontSize(30.f);
    m_SatietyMax->SetAlignH(EText_Align_H::Right);
    m_SatietyMax->SetAlignV(EText_Align_V::Middle);
    m_SatietyMax->SetSize(50.f, m_Size.y / 2.f);
    m_SatietyMax->SetPos(m_SatietySlash->GetPos().x + m_SatietySlash->GetSize().x, 0.f);
    m_SatietyMax->SetText(TEXT("100"));
    m_SatietyMax->SetZOrder(1);

    return true;
}

void CCharacterLBUI::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);
}

void CCharacterLBUI::PostUpdate(float DeltaTime)
{
    CUIWindow::PostUpdate(DeltaTime);
}

void CCharacterLBUI::Render()
{
    CUIWindow::Render();
}

CCharacterLBUI* CCharacterLBUI::Clone()
{
    return new CCharacterLBUI(*this);
}

void CCharacterLBUI::Save(FILE* File)
{
    CUIWindow::Save(File);
}

void CCharacterLBUI::Load(FILE* File)
{
    CUIWindow::Load(File);
}