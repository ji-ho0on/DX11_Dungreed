#include "CharacterHitUI.h"
#include "UI/UIImage.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Device.h"

CCharacterHitUI::CCharacterHitUI()
{
    m_WindowTypeName = "CharacterHitUI";
}

CCharacterHitUI::CCharacterHitUI(const CCharacterHitUI& Window) :
    CUIWindow(Window)
{
    m_RedWarningLeft = FindWidget<CUIImage>("RedWarningLeft");
    m_RedWarningRight = FindWidget<CUIImage>("RedWarningRight");
}

CCharacterHitUI::~CCharacterHitUI()
{
}

void CCharacterHitUI::Start()
{
    CUIWindow::Start();
}

bool CCharacterHitUI::Init()
{
    CUIWindow::Init();

    Resolution Resolution = CDevice::GetInst()->GetResolution();

    SetSize((float)Resolution.Width, (float)Resolution.Height);
    SetPos(0.f, 0.f);

    m_RedWarningLeft = CreateWidget<CUIImage>("RedWarningLeft");
    m_RedWarningLeft->SetTexture("RedWarningOnHit_0", TEXT("gameScene/ui/RedWarningOnHit_0.png"));
    m_RedWarningLeft->SetSize((float)Resolution.Width / 2.f, (float)Resolution.Height);
    m_RedWarningLeft->SetPos(0.f, 0.f);

    m_RedWarningRight = CreateWidget<CUIImage>("RedWarningRight");
    m_RedWarningRight->SetTexture("RedWarningOnHit_1", TEXT("gameScene/ui/RedWarningOnHit_1.png"));
    m_RedWarningRight->SetSize((float)Resolution.Width / 2.f, (float)Resolution.Height);
    m_RedWarningRight->SetPos(m_RedWarningLeft->GetSize().x, 0.f);

    return true;
}

void CCharacterHitUI::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);
}

void CCharacterHitUI::PostUpdate(float DeltaTime)
{
    CUIWindow::PostUpdate(DeltaTime);
}

void CCharacterHitUI::Render()
{
    CUIWindow::Render();
}

CCharacterHitUI* CCharacterHitUI::Clone()
{
    return new CCharacterHitUI(*this);
}

void CCharacterHitUI::Save(FILE* File)
{
    CUIWindow::Save(File);
}

void CCharacterHitUI::Load(FILE* File)
{
    CUIWindow::Load(File);
}