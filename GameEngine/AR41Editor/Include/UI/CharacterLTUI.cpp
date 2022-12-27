#include "CharacterLTUI.h"
#include "UI/UIProgressBar.h"
#include "UI/UIImage.h"
#include "UI/UIText.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Device.h"

CCharacterLTUI::CCharacterLTUI()
{
    m_WindowTypeName = "CharacterLTUI";
}

CCharacterLTUI::CCharacterLTUI(const CCharacterLTUI& Window) :
    CUIWindow(Window)
{
    m_HPBack = FindWidget<CUIImage>("HPBack");
    m_HPBar = FindWidget<CUIProgressBar>("HPBar");
    m_HPFront = FindWidget<CUIImage>("HPFront");
    m_Level = FindWidget<CUIText>("Level");
    m_HP = FindWidget<CUIText>("HP");
    m_HPSlash = FindWidget<CUIText>("HPSlash");
    m_HPMax = FindWidget<CUIText>("HPMax");
    m_DashBack1 = FindWidget<CUIImage>("DashBack1");
    m_DashBack2 = FindWidget<CUIImage>("DashBack2");
    m_DashBack3 = FindWidget<CUIImage>("DashBack3");
    m_DashBack4 = FindWidget<CUIImage>("DashBack4");
    m_DashBack5 = FindWidget<CUIImage>("DashBack5");

    m_DashCount = Window.m_DashCount;

    m_DashCount1 = FindWidget<CUIImage>("DashCount1");
    m_DashCount2 = FindWidget<CUIImage>("DashCount2");
    m_DashCount3 = FindWidget<CUIImage>("DashCount3");
    m_DashCount4 = FindWidget<CUIImage>("DashCount4");
}

CCharacterLTUI::~CCharacterLTUI()
{
}

void CCharacterLTUI::SetLevel(int Level)
{
    int _Level = Level;

    if (Level < 0)
        _Level = 0;

    char LevelName[4] = {};

    _itoa_s(_Level, LevelName, 10);

    TCHAR ConvertLevelName[4] = {};

    int	ConvertLength = MultiByteToWideChar(CP_ACP, 0, LevelName, -1, nullptr, 0);
    MultiByteToWideChar(CP_ACP, 0, LevelName, -1, ConvertLevelName, ConvertLength);

    m_Level->SetText(ConvertLevelName);
}

void CCharacterLTUI::SetHP(int HP)
{
    int _HP = HP;

    if (HP < 0)
        _HP = 0;

    char HPName[4] = {};

    _itoa_s(_HP, HPName, 10);

    TCHAR ConvertHPName[4] = {};

    int	ConvertLength = MultiByteToWideChar(CP_ACP, 0, HPName, -1, nullptr, 0);
    MultiByteToWideChar(CP_ACP, 0, HPName, -1, ConvertHPName, ConvertLength);

    m_HP->SetText(ConvertHPName);
    m_HPBar->SetValue((float)_HP);
}

void CCharacterLTUI::SetHPMax(int HPMax)
{
    int _HPMax = HPMax;

    if (HPMax < 0)
        _HPMax = 0;

    char HPMaxName[4] = {};

    _itoa_s(_HPMax, HPMaxName, 10);

    TCHAR ConvertHPMaxName[4] = {};

    int	ConvertLength = MultiByteToWideChar(CP_ACP, 0, HPMaxName, -1, nullptr, 0);
    MultiByteToWideChar(CP_ACP, 0, HPMaxName, -1, ConvertHPMaxName, ConvertLength);

    m_HPMax->SetText(ConvertHPMaxName);
    m_HPBar->SetProgressBarMax(float(_HPMax));
}

void CCharacterLTUI::SetDashCount(int DashCount)
{
    int Count = DashCount;

    if (DashCount < 0)
        Count = 0;

    else if (DashCount > 4)
        Count = 4;

    m_DashCount = Count;

    if (m_DashCount == 0)
    {
        m_DashCount1->SetEnable(false);
        m_DashCount2->SetEnable(false);
        m_DashCount3->SetEnable(false);
        m_DashCount4->SetEnable(false);
    }

    else if (m_DashCount == 1)
    {
        m_DashCount1->SetEnable(true);
        m_DashCount2->SetEnable(false);
        m_DashCount3->SetEnable(false);
        m_DashCount4->SetEnable(false);
    }

    else if (m_DashCount == 2)
    {
        m_DashCount1->SetEnable(true);
        m_DashCount2->SetEnable(true);
        m_DashCount3->SetEnable(false);
        m_DashCount4->SetEnable(false);
    }

    else if (m_DashCount == 3)
    {
        m_DashCount1->SetEnable(true);
        m_DashCount2->SetEnable(true);
        m_DashCount3->SetEnable(true);
        m_DashCount4->SetEnable(false);
    }

    else if (m_DashCount == 4)
    {
        m_DashCount1->SetEnable(true);
        m_DashCount2->SetEnable(true);
        m_DashCount3->SetEnable(true);
        m_DashCount4->SetEnable(true);
    }
}

void CCharacterLTUI::Start()
{
    CUIWindow::Start();
}

bool CCharacterLTUI::Init()
{
    CUIWindow::Init();

    Resolution Resolution = CDevice::GetInst()->GetResolution();

    SetSize((float)Resolution.Width / 4.f, (float)Resolution.Height / 6.f);
    SetPos(10.f, (float)Resolution.Height - m_Size.y - 10.f);

    m_HPBack = CreateWidget<CUIImage>("HPBack");
    m_HPBack->SetTexture("PlayerLifeBack", TEXT("gameScene/ui/PlayerLifeBack.png"));
    m_HPBack->SetSize(m_Size.x, m_Size.y / 3.f * 2.f);
    m_HPBack->SetPos(0.f, m_Size.y - m_HPBack->GetSize().y);
    m_HPBack->SetZOrder(3);

    m_HPBar = CreateWidget<CUIProgressBar>("HPBar");
    m_HPBar->SetTexture(EProgressBarTextureType::Bar, "LifeBar", TEXT("gameScene/ui/LifeBar.png"));
    m_HPBar->SetOpacity(0.f);
    m_HPBar->SetSize(m_Size.x * 0.66f, m_Size.y / 3.f * 2.f);
    m_HPBar->SetPos(m_Size.x * 0.3f, m_Size.y - m_HPBar->GetSize().y);
    m_HPBar->SetProgressBarMin(0.f);
    m_HPBar->SetProgressBarMax(100.f);
    m_HPBar->SetValue(100.f);
    m_HPBar->SetZOrder(2);

    m_HPFront = CreateWidget<CUIImage>("HPFront");
    m_HPFront->SetTexture("PlayerLifeBase1", TEXT("gameScene/ui/PlayerLifeBase1.png"));
    m_HPFront->SetSize(m_Size.x, m_Size.y / 3.f * 2.f);
    m_HPFront->SetPos(0.f, m_Size.y - m_HPFront->GetSize().y);
    m_HPFront->SetZOrder(1);

    m_Level = CreateWidget<CUIText>("Level");
    m_Level->SetFont("NumberFont");
    m_Level->SetFontSize(45.f);
    m_Level->SetAlignH(EText_Align_H::Center);
    m_Level->SetAlignV(EText_Align_V::Middle);
    m_Level->SetSize(m_HPBack->GetSize().x * 0.3f, m_HPBack->GetSize().y);
    m_Level->SetPos(m_HPBack->GetPos());
    m_Level->SetText(TEXT("1"));
    m_Level->SetZOrder(1);

    m_HPSlash = CreateWidget<CUIText>("HPSlash");
    m_HPSlash->SetFont("NumberFont");
    m_HPSlash->SetFontSize(45.f);
    m_HPSlash->SetAlignH(EText_Align_H::Center);
    m_HPSlash->SetAlignV(EText_Align_V::Middle);
    m_HPSlash->SetSize(m_HPBar->GetSize());
    m_HPSlash->SetPos(m_HPBar->GetPos());
    m_HPSlash->SetText(TEXT("/"));
    m_HPSlash->SetZOrder(1);

    m_HP = CreateWidget<CUIText>("HP");
    m_HP->SetFont("NumberFont");
    m_HP->SetFontSize(45.f);
    m_HP->SetAlignH(EText_Align_H::Right);
    m_HP->SetAlignV(EText_Align_V::Middle);
    m_HP->SetSize(m_HPBar->GetSize().x / 3.f, m_HPBar->GetSize().y);
    m_HP->SetPos(m_HPBar->GetPos());
    m_HP->SetText(TEXT("100"));
    m_HP->SetZOrder(1);

    m_HPMax = CreateWidget<CUIText>("HPMax");
    m_HPMax->SetFont("NumberFont");
    m_HPMax->SetFontSize(45.f);
    m_HPMax->SetAlignH(EText_Align_H::Left);
    m_HPMax->SetAlignV(EText_Align_V::Middle);
    m_HPMax->SetSize(m_HPBar->GetSize().x / 3.f, m_HPBar->GetSize().y);
    m_HPMax->SetPos(m_HPBar->GetPos().x + (m_HPMax->GetSize().x * 2.f), m_HPBar->GetPos().y);
    m_HPMax->SetText(TEXT("100"));
    m_HPMax->SetZOrder(1);

    m_DashBack1 = CreateWidget<CUIImage>("DashBack1");
    m_DashBack1->SetTexture("DashCountBase_0", TEXT("gameScene/ui/DashCountBase_0.png"));
    m_DashBack1->SetSize(m_Size.x / 2.f * 11.f / 40.f, m_Size.y / 3.f);
    m_DashBack1->SetPos(0.f, 0.f);
    m_DashBack1->SetZOrder(3);

    m_DashBack2 = CreateWidget<CUIImage>("DashBack2");
    m_DashBack2->SetTexture("DashBase", TEXT("gameScene/ui/DashBase.png"));
    m_DashBack2->SetSize(m_Size.x / 2.f * 9.f / 40.f, m_Size.y / 3.f);
    m_DashBack2->SetPos(m_DashBack1->GetSize().x, 0.f);
    m_DashBack2->SetZOrder(3);

    m_DashBack3 = CreateWidget<CUIImage>("DashBack3");
    m_DashBack3->SetTexture("DashBase", TEXT("gameScene/ui/DashBase.png"));
    m_DashBack3->SetSize(m_Size.x / 2.f * 9.f / 40.f, m_Size.y / 3.f);
    m_DashBack3->SetPos(m_DashBack2->GetPos().x + m_DashBack2->GetSize().x, 0.f);
    m_DashBack3->SetZOrder(3);

    m_DashBack4 = CreateWidget<CUIImage>("DashBack4");
    m_DashBack4->SetTexture("DashBase", TEXT("gameScene/ui/DashBase.png"));
    m_DashBack4->SetSize(m_Size.x / 2.f * 9.f / 40.f, m_Size.y / 3.f);
    m_DashBack4->SetPos(m_DashBack3->GetPos().x + m_DashBack3->GetSize().x, 0.f);
    m_DashBack4->SetZOrder(3);

    m_DashBack5 = CreateWidget<CUIImage>("DashBack5");
    m_DashBack5->SetTexture("DashBaseRightEnd", TEXT("gameScene/ui/DashBaseRightEnd.png"));
    m_DashBack5->SetSize(m_Size.x / 2.f * 2.f / 40.f, m_Size.y / 3.f);
    m_DashBack5->SetPos(m_DashBack4->GetPos().x + m_DashBack4->GetSize().x, 0.f);
    m_DashBack5->SetZOrder(3);

    m_DashCount1 = CreateWidget<CUIImage>("DashCount1");
    m_DashCount1->SetTexture("DashCount", TEXT("gameScene/ui/DashCount.png"));
    m_DashCount1->SetSize(m_DashBack1->GetSize().x * 9.f / 11.f, m_DashBack1->GetSize().y / 2.f);
    m_DashCount1->SetPos(m_DashBack1->GetPos().x + (m_DashBack1->GetSize().x * 2.f / 11.f), m_DashBack1->GetPos().y + (m_DashBack1->GetSize().y / 4.f));
    m_DashCount1->SetZOrder(2);

    m_DashCount2 = CreateWidget<CUIImage>("DashCount2");
    m_DashCount2->SetTexture("DashCount", TEXT("gameScene/ui/DashCount.png"));
    m_DashCount2->SetSize(m_DashBack2->GetSize().x, m_DashBack2->GetSize().y / 2.f);
    m_DashCount2->SetPos(m_DashBack2->GetPos().x, m_DashBack2->GetPos().y + (m_DashBack2->GetSize().y / 4.f));
    m_DashCount2->SetZOrder(2);

    m_DashCount3 = CreateWidget<CUIImage>("DashCount3");
    m_DashCount3->SetTexture("DashCount", TEXT("gameScene/ui/DashCount.png"));
    m_DashCount3->SetSize(m_DashBack3->GetSize().x, m_DashBack3->GetSize().y / 2.f);
    m_DashCount3->SetPos(m_DashBack3->GetPos().x, m_DashBack3->GetPos().y + (m_DashBack3->GetSize().y / 4.f));
    m_DashCount3->SetZOrder(2);

    m_DashCount4 = CreateWidget<CUIImage>("DashCount4");
    m_DashCount4->SetTexture("DashCount", TEXT("gameScene/ui/DashCount.png"));
    m_DashCount4->SetSize(m_DashBack4->GetSize().x, m_DashBack4->GetSize().y / 2.f);
    m_DashCount4->SetPos(m_DashBack4->GetPos().x, m_DashBack4->GetPos().y + (m_DashBack4->GetSize().y / 4.f));
    m_DashCount4->SetZOrder(2);

    m_DashCount = 4;

    return true;
}

void CCharacterLTUI::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);
}

void CCharacterLTUI::PostUpdate(float DeltaTime)
{
    CUIWindow::PostUpdate(DeltaTime);
}

void CCharacterLTUI::Render()
{
    CUIWindow::Render();
}

CCharacterLTUI* CCharacterLTUI::Clone()
{
    return new CCharacterLTUI(*this);
}

void CCharacterLTUI::Save(FILE* File)
{
    CUIWindow::Save(File);
}

void CCharacterLTUI::Load(FILE* File)
{
    CUIWindow::Load(File);
}