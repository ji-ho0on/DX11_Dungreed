#include "TestUIWindow.h"
#include "UI/UIButton.h"
#include "UI/UIText.h"
#include "UI/UIProgressBar.h"
#include "UI/UINumber.h"

CTestUIWindow::CTestUIWindow()
{
    m_WindowTypeName = "TestUIWindow";
}

CTestUIWindow::CTestUIWindow(const CTestUIWindow& Window) :
    CUIWindow(Window)
{
    m_TestButton = FindWidget<CUIButton>("TestButton");
    m_TestText = FindWidget<CUIText>("TestText");
    m_TestProgressBar = FindWidget<CUIProgressBar>("TestProgressBar");
    m_TestNumber = FindWidget<CUINumber>("TestNumber");
}

CTestUIWindow::~CTestUIWindow()
{
}

void CTestUIWindow::Start()
{
    CUIWindow::Start();
}

bool CTestUIWindow::Init()
{
    CUIWindow::Init();

    m_TestButton = CreateWidget<CUIButton>("TestButton");

    m_TestButton->SetSize(100.f, 100.f);
    m_TestButton->SetPos(300.f, 300.f);
    m_TestButton->SetTint(255, 0, 0, 255);

    m_TestButton->SetTexture(EButtonState::Normal, "StartButton", TEXT("Start.png"));
    m_TestButton->SetTexture(EButtonState::Hovered, "StartButton", TEXT("Start.png"));
    m_TestButton->SetTexture(EButtonState::Click, "StartButton", TEXT("Start.png"));
    m_TestButton->SetTexture(EButtonState::Disable, "StartButton", TEXT("Start.png"));

    //m_TestButton->SetSound(EButtonEventState::Hovered, "UI", "ButtonHovered", false, "Demasia.mp3");
    //m_TestButton->SetSound(EButtonEventState::Click, "UI", "ButtonClick", false, "TeemoSmile.mp3");

    m_TestText = CreateWidget<CUIText>("TestText");

    m_TestText->SetSize(300.f, 100.f);
    m_TestText->SetPos(200.f, 500.f);

    m_TestText->SetFontSize(25.f);
    m_TestText->SetText(TEXT("텍스트 UI 테스트"));
    m_TestText->SetColor(255, 255, 0);
    m_TestText->SetTransparency(true);
    m_TestText->SetOpacity(0.8f);

    m_TestText->SetShadowEnable(true);
    m_TestText->SetShadowColor(128, 128, 128);
    m_TestText->SetShadowTransparency(true);
    m_TestText->SetShadowOpacity(0.5f);

    m_TestProgressBar = CreateWidget<CUIProgressBar>("TestProgressBar");

    m_TestProgressBar->SetPos(200.f, 600.f);
    m_TestProgressBar->SetSize(200.f, 40.f);

    m_TestProgressBar->SetTint(100, 100, 100, 255);
    m_TestProgressBar->SetImageTint(EProgressBarTextureType::Back, 100, 100, 100, 255);
    m_TestProgressBar->SetImageTint(EProgressBarTextureType::Bar, 255, 255, 255, 255);

    m_TestProgressBar->SetTexture(EProgressBarTextureType::Bar, "HPBar", TEXT("HPBar.png"));

    m_TestProgressBar->SetProgressBarMin(0.f);
    m_TestProgressBar->SetProgressBarMax(100.f);
    m_TestProgressBar->SetValue(80.f);

    m_TestNumber = CreateWidget<CUINumber>("TestNumber");

    m_TestNumber->SetPos(200.f, 400.f);
    m_TestNumber->SetSize(20.f, 30.f);

    m_TestNumber->SetNumber(2392);

    m_TestNumber->SetTexture("Number", TEXT("Number.png"));

    for (int i = 0; i < 10; ++i)
    {
        m_TestNumber->AddFrameData(Vector2(i * 46.4f, 0.f), Vector2((i + 1) * 46.4f, 68.5f));
    }

    return true;
}

void CTestUIWindow::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);
}

void CTestUIWindow::PostUpdate(float DeltaTime)
{
    CUIWindow::PostUpdate(DeltaTime);
}

void CTestUIWindow::Render()
{
    CUIWindow::Render();
}

CTestUIWindow* CTestUIWindow::Clone()
{
    return new CTestUIWindow(*this);
}

void CTestUIWindow::Save(FILE* File)
{
    CUIWindow::Save(File);
}

void CTestUIWindow::Load(FILE* File)
{
    CUIWindow::Load(File);

    m_TestButton = FindWidget<CUIButton>("TestButton");
    m_TestText = FindWidget<CUIText>("TestText");
    m_TestProgressBar = FindWidget<CUIProgressBar>("TestProgressBar");
    m_TestNumber = FindWidget<CUINumber>("TestNumber");
}