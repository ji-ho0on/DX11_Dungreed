#include "BossUI.h"
#include "UI/UIProgressBar.h"
#include "UI/UIImage.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Device.h"

CBossUI::CBossUI()
{
    m_WindowTypeName = "CBossUI";
}

CBossUI::CBossUI(const CBossUI& Window) :
    CUIWindow(Window)
{
    m_HPBack = FindWidget<CUIImage>("HPBack");
    m_HPBar = FindWidget<CUIProgressBar>("HPBar");
    m_HPBase = FindWidget<CUIImage>("HPBase");
    m_BossImage = FindWidget<CUIImage>("BossImage");
}

CBossUI::~CBossUI()
{
}

void CBossUI::SetHP(int HP)
{
    int _HP = HP;

    if (HP < 0)
        _HP = 0;

    m_HPBar->SetValue((float)_HP);
}

void CBossUI::SetHPMax(int HPMax)
{
    int _HPMax = HPMax;

    if (HPMax < 0)
        _HPMax = 0;

    m_HPBar->SetProgressBarMax(float(_HPMax));
    m_HPBar->SetValue(float(_HPMax));
}

void CBossUI::Start()
{
    CUIWindow::Start();
}

bool CBossUI::Init()
{
    CUIWindow::Init();

    Resolution Resolution = CDevice::GetInst()->GetResolution();

    SetSize((float)Resolution.Width / 2.5f, (float)Resolution.Height / 9.f);
    SetPos(((float)Resolution.Width - GetSize().x) / 2.f, 5.f);

    m_HPBack = CreateWidget<CUIImage>("HPBack");
    m_HPBack->SetTexture("BossLifeBack", TEXT("gameScene/ui/BossLifeBack.png"));
    m_HPBack->SetSize(m_Size);
    m_HPBack->SetPos(0.f, 0.f);
    m_HPBack->SetZOrder(3);

    m_HPBar = CreateWidget<CUIProgressBar>("HPBar");
    m_HPBar->SetTexture(EProgressBarTextureType::Bar, "LifeBar", TEXT("gameScene/ui/LifeBar.png"));
    m_HPBar->SetOpacity(0.f);
    m_HPBar->SetSize(410.f, 80.f);
    m_HPBar->SetPos(90.f, 0.f);
    m_HPBar->SetProgressBarMin(0.f);
    m_HPBar->SetProgressBarMax(100.f);
    m_HPBar->SetValue(100.f);
    m_HPBar->SetZOrder(2);

    m_HPBase = CreateWidget<CUIImage>("HPBase");
    m_HPBase->SetTexture("BossLifeBase", TEXT("gameScene/ui/BossLifeBase.png"));
    m_HPBase->SetSize(m_Size);
    m_HPBase->SetPos(0.f, 0.f);
    m_HPBase->SetZOrder(1);

    m_BossImage = CreateWidget<CUIImage>("BossImage");
    m_BossImage->SetTexture("BossSkellPortrait", TEXT("gameScene/ui/BossSkellPortrait.png"));
    m_BossImage->SetSize(70.f, 50.f);
    m_BossImage->SetPos(12.f, 15.f);
    m_BossImage->SetZOrder(2);

    return true;
}

void CBossUI::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);
}

void CBossUI::PostUpdate(float DeltaTime)
{
    CUIWindow::PostUpdate(DeltaTime);
}

void CBossUI::Render()
{
    CUIWindow::Render();
}

CBossUI* CBossUI::Clone()
{
    return new CBossUI(*this);
}

void CBossUI::Save(FILE* File)
{
    CUIWindow::Save(File);
}

void CBossUI::Load(FILE* File)
{
    CUIWindow::Load(File);
}