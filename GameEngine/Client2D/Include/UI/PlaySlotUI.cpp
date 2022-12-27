#include "PlaySlotUI.h"
#include "UI/UIImage.h"
#include "UI/UIButton.h"
#include "UI/UIText.h"
#include "Device.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Sound/Sound.h"
#include "Scene/SceneManager.h"
#include "PathManager.h"

CPlaySlotUI::CPlaySlotUI()
{
    m_WindowTypeName = "PlaySlotUI";
}

CPlaySlotUI::CPlaySlotUI(const CPlaySlotUI& Window) :
    CUIWindow(Window)
{
    m_SlotBackImage = FindWidget<CUIImage>("SlotBack");
    m_SlotButton1 = FindWidget<CUIButton>("SlotButton1");
    m_SlotButton2 = FindWidget<CUIButton>("SlotButton2");
    m_SlotButton3 = FindWidget<CUIButton>("SlotButton3");
    m_SlotImage1 = FindWidget<CUIImage>("SlotImage1");
    m_SlotImage2 = FindWidget<CUIImage>("SlotImage2");
    m_SlotImage3 = FindWidget<CUIImage>("SlotImage3");
    m_SlotDeleteButton1 = FindWidget<CUIButton>("SlotDeleteButton1");
    m_SlotDeleteButton2 = FindWidget<CUIButton>("SlotDeleteButton2");
    m_SlotDeleteButton3 = FindWidget<CUIButton>("SlotDeleteButton3");
    m_SlotDeleteText1 = FindWidget<CUIText>("SlotDeleteText1");
    m_SlotDeleteText2 = FindWidget<CUIText>("SlotDeleteText2");
    m_SlotDeleteText3 = FindWidget<CUIText>("SlotDeleteText3");
    m_SlotExitButton = FindWidget<CUIButton>("SlotExitButton");
}

CPlaySlotUI::~CPlaySlotUI()
{
}

void CPlaySlotUI::Start()
{
    CUIWindow::Start();

    m_SlotButton1->SetCallback<CPlaySlotUI>(EButtonEventState::Click, this, &CPlaySlotUI::SlotButton1Click);
    m_SlotButton2->SetCallback<CPlaySlotUI>(EButtonEventState::Click, this, &CPlaySlotUI::SlotButton2Click);
    m_SlotButton3->SetCallback<CPlaySlotUI>(EButtonEventState::Click, this, &CPlaySlotUI::SlotButton3Click);

    m_SlotExitButton->SetCallback<CPlaySlotUI>(EButtonEventState::Click, this, &CPlaySlotUI::SlotExitButtonClick);
}

bool CPlaySlotUI::Init()
{
    Resolution Resolution = CDevice::GetInst()->GetResolution();

    m_SlotBackImage = CreateWidget<CUIImage>("SlotBack");
    m_SlotBackImage->SetSize((float)Resolution.Width, (float)Resolution.Height);
    m_SlotBackImage->SetTint(Vector4::Black);
    m_SlotBackImage->SetOpacity(0.7f);
    m_SlotBackImage->SetZOrder(3);

    m_SlotButton1 = CreateWidget<CUIButton>("SlotButton1");
    m_SlotButton1->SetTexture(EButtonState::Normal, "SlotBase", TEXT("MainScene/SlotBase.png"));
    m_SlotButton1->SetTexture(EButtonState::Hovered, "SlotBase_Selected", TEXT("MainScene/SlotBase_Selected.png"));
    m_SlotButton1->SetTexture(EButtonState::Click, "SlotBase_Selected", TEXT("MainScene/SlotBase_Selected.png"));
    m_SlotButton1->SetSize(380.f, 580.f);
    m_SlotButton1->SetPos(40.f, 30.f);
    m_SlotButton1->SetZOrder(2);


    m_SlotImage1 = CreateWidget<CUIImage>("SlotImage1");
    m_SlotImage1->SetTexture("SlotImage1", TEXT("MainScene/SlotText1_EN.png"));
    m_SlotImage1->SetSize(180.f, 50.f);
    m_SlotImage1->SetPos(m_SlotButton1->GetPos() + Vector2(100.f, 485.f));



    m_SlotButton2 = CreateWidget<CUIButton>("SlotButton2");
    m_SlotButton2->SetTexture(EButtonState::Normal, "SlotBase", TEXT("MainScene/SlotBase.png"));
    m_SlotButton2->SetTexture(EButtonState::Hovered, "SlotBase_Selected", TEXT("MainScene/SlotBase_Selected.png"));
    m_SlotButton2->SetTexture(EButtonState::Click, "SlotBase_Selected", TEXT("MainScene/SlotBase_Selected.png"));
    m_SlotButton2->SetSize(380.f, 580.f);
    m_SlotButton2->SetPos(450.f, 30.f);
    m_SlotButton2->SetZOrder(2);


    m_SlotImage2 = CreateWidget<CUIImage>("SlotImage2");
    m_SlotImage2->SetTexture("SlotImage2", TEXT("MainScene/SlotText2_EN.png"));
    m_SlotImage2->SetSize(180.f, 50.f);
    m_SlotImage2->SetPos(m_SlotButton2->GetPos() + Vector2(100.f, 485.f));



    m_SlotButton3 = CreateWidget<CUIButton>("SlotButton3");
    m_SlotButton3->SetTexture(EButtonState::Normal, "SlotBase", TEXT("MainScene/SlotBase.png"));
    m_SlotButton3->SetTexture(EButtonState::Hovered, "SlotBase_Selected", TEXT("MainScene/SlotBase_Selected.png"));
    m_SlotButton3->SetTexture(EButtonState::Click, "SlotBase_Selected", TEXT("MainScene/SlotBase_Selected.png"));
    m_SlotButton3->SetSize(380.f, 580.f);
    m_SlotButton3->SetPos(860.f, 30.f);
    m_SlotButton3->SetZOrder(2);


    m_SlotImage3 = CreateWidget<CUIImage>("SlotImage3");
    m_SlotImage3->SetTexture("SlotImage3", TEXT("MainScene/SlotText3_EN.png"));
    m_SlotImage3->SetSize(180.f, 50.f);
    m_SlotImage3->SetPos(m_SlotButton3->GetPos() + Vector2(100.f, 485.f));


    m_SlotDeleteButton1 = CreateWidget<CUIButton>("SlotDeleteButton1");
    m_SlotDeleteButton1->SetTexture(EButtonState::Normal, "SlotDeleteButton", TEXT("MainScene/SlotDeleteButton.png"));
    m_SlotDeleteButton1->SetTexture(EButtonState::Hovered, "SlotDeleteButton_Selected", TEXT("MainScene/SlotDeleteButton_Selected.png"));
    m_SlotDeleteButton1->SetTexture(EButtonState::Click, "SlotDeleteButton_Selected", TEXT("MainScene/SlotDeleteButton_Selected.png"));
    m_SlotDeleteButton1->SetSize(240.f, 70.f);
    m_SlotDeleteButton1->SetPos(m_SlotButton1->GetPos() + Vector2(70.f, 30.f));
    m_SlotDeleteButton1->SetZOrder(1);

    m_SlotDeleteButton2 = CreateWidget<CUIButton>("SlotDeleteButton2");
    m_SlotDeleteButton2->SetTexture(EButtonState::Normal, "SlotDeleteButton", TEXT("MainScene/SlotDeleteButton.png"));
    m_SlotDeleteButton2->SetTexture(EButtonState::Hovered, "SlotDeleteButton_Selected", TEXT("MainScene/SlotDeleteButton_Selected.png"));
    m_SlotDeleteButton2->SetTexture(EButtonState::Click, "SlotDeleteButton_Selected", TEXT("MainScene/SlotDeleteButton_Selected.png"));
    m_SlotDeleteButton2->SetSize(240.f, 70.f);
    m_SlotDeleteButton2->SetPos(m_SlotButton2->GetPos() + Vector2(70.f, 30.f));
    m_SlotDeleteButton2->SetZOrder(1);

    m_SlotDeleteButton3 = CreateWidget<CUIButton>("SlotDeleteButton3");
    m_SlotDeleteButton3->SetTexture(EButtonState::Normal, "SlotDeleteButton", TEXT("MainScene/SlotDeleteButton.png"));
    m_SlotDeleteButton3->SetTexture(EButtonState::Hovered, "SlotDeleteButton_Selected", TEXT("MainScene/SlotDeleteButton_Selected.png"));
    m_SlotDeleteButton3->SetTexture(EButtonState::Click, "SlotDeleteButton_Selected", TEXT("MainScene/SlotDeleteButton_Selected.png"));
    m_SlotDeleteButton3->SetSize(240.f, 70.f);
    m_SlotDeleteButton3->SetPos(m_SlotButton3->GetPos() + Vector2(70.f, 30.f));
    m_SlotDeleteButton3->SetZOrder(1);

    m_SlotDeleteText1 = CreateWidget<CUIText>("SlotDeleteText1");
    m_SlotDeleteText1->SetText(TEXT("삭제"));
    m_SlotDeleteText1->SetSize(70.f, 50.f);
    m_SlotDeleteText1->SetFontSize(25.f);
    m_SlotDeleteText1->SetColor(83, 45, 46);
    m_SlotDeleteText1->SetAlignH(EText_Align_H::Center);
    m_SlotDeleteText1->SetAlignV(EText_Align_V::Middle);
    m_SlotDeleteText1->SetPos(m_SlotDeleteButton1->GetPos() + Vector2(85.f, 10.f));

    m_SlotDeleteText2 = CreateWidget<CUIText>("SlotDeleteText2");
    m_SlotDeleteText2->SetText(TEXT("삭제"));
    m_SlotDeleteText2->SetSize(70.f, 50.f);
    m_SlotDeleteText2->SetFontSize(25.f);
    m_SlotDeleteText2->SetColor(83, 45, 46);
    m_SlotDeleteText2->SetAlignH(EText_Align_H::Center);
    m_SlotDeleteText2->SetAlignV(EText_Align_V::Middle);
    m_SlotDeleteText2->SetPos(m_SlotDeleteButton2->GetPos() + Vector2(85.f, 10.f));

    m_SlotDeleteText3 = CreateWidget<CUIText>("SlotDeleteText3");
    m_SlotDeleteText3->SetText(TEXT("삭제"));
    m_SlotDeleteText3->SetSize(70.f, 50.f);
    m_SlotDeleteText3->SetFontSize(25.f);
    m_SlotDeleteText3->SetColor(83, 45, 46);
    m_SlotDeleteText3->SetAlignH(EText_Align_H::Center);
    m_SlotDeleteText3->SetAlignV(EText_Align_V::Middle);
    m_SlotDeleteText3->SetPos(m_SlotDeleteButton3->GetPos() + Vector2(85.f, 10.f));

    
    m_SlotExitButton = CreateWidget<CUIButton>("SlotExitButton");
    m_SlotExitButton->SetTexture(EButtonState::Normal, "FullWindowExitButton", TEXT("MainScene/FullWindowExitButton.png"));
    m_SlotExitButton->SetTexture(EButtonState::Hovered, "FullWindowExitButton_Selected", TEXT("MainScene/FullWindowExitButton_Selected.png"));
    m_SlotExitButton->SetTexture(EButtonState::Click, "FullWindowExitButton_Selected", TEXT("MainScene/FullWindowExitButton_Selected.png"));
    m_SlotExitButton->SetSize(80.f, 70.f);
    m_SlotExitButton->SetPos(1190.f, 640.f);
    m_SlotExitButton->SetZOrder(0);

    return true;
}

void CPlaySlotUI::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);
}

void CPlaySlotUI::PostUpdate(float DeltaTime)
{
    CUIWindow::PostUpdate(DeltaTime);
}

void CPlaySlotUI::Render()
{
    CUIWindow::Render();
}

CPlaySlotUI* CPlaySlotUI::Clone()
{
    return new CPlaySlotUI(*this);
}

void CPlaySlotUI::Save(FILE* File)
{
    CUIWindow::Save(File);
}

void CPlaySlotUI::Load(FILE* File)
{
    CUIWindow::Load(File);
}

void CPlaySlotUI::SlotButton1Click()
{
   CSound* MainBGM = m_Scene->GetResource()->FindSound("MainBGM");
   MainBGM->Stop();

   CSound* JailField = m_Scene->GetResource()->FindSound("JailField");
   JailField->Play();

   // 나머지 Scene들 불러와서 MonsterClear상태만 바꿔주고 다시 저장
   CSceneManager::GetInst()->CreateNextScene();
   CScene* NextScene = CSceneManager::GetInst()->GetNextScene();

   const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

   char	FullPath[MAX_PATH] = {};

   if (Info)
       strcpy_s(FullPath, Info->PathMultibyte);

   strcat_s(FullPath, "Scene/NormalScene2.scn");

   NextScene->Load(FullPath);
   NextScene->GetSceneInfo()->SetMonsterClear(false);
   NextScene->Save(FullPath);


   CSceneManager::GetInst()->CreateNextScene();
   NextScene = CSceneManager::GetInst()->GetNextScene();

   char	FullPath2[MAX_PATH] = {};

   if (Info)
       strcpy_s(FullPath2, Info->PathMultibyte);

   strcat_s(FullPath2, "Scene/NormalScene3.scn");

   NextScene->Load(FullPath2);
   NextScene->GetSceneInfo()->SetMonsterClear(false);
   NextScene->Save(FullPath2);


   CSceneManager::GetInst()->CreateNextScene();
   NextScene = CSceneManager::GetInst()->GetNextScene();

   char	FullPath3[MAX_PATH] = {};

   if (Info)
       strcpy_s(FullPath3, Info->PathMultibyte);

   strcat_s(FullPath3, "Scene/NormalScene4.scn");

   NextScene->Load(FullPath3);
   NextScene->GetSceneInfo()->SetMonsterClear(false);
   NextScene->Save(FullPath3);


   CSceneManager::GetInst()->CreateNextScene();
   NextScene = CSceneManager::GetInst()->GetNextScene();

   char	FullPath4[MAX_PATH] = {};

   if (Info)
       strcpy_s(FullPath4, Info->PathMultibyte);

   strcat_s(FullPath4, "Scene/NormalScene5.scn");

   NextScene->Load(FullPath4);
   NextScene->GetSceneInfo()->SetMonsterClear(false);
   NextScene->Save(FullPath4);


   CSceneManager::GetInst()->CreateNextScene();
   NextScene = CSceneManager::GetInst()->GetNextScene();

   char	FullPath5[MAX_PATH] = {};

   if (Info)
       strcpy_s(FullPath5, Info->PathMultibyte);

   strcat_s(FullPath5, "Scene/NormalScene6.scn");

   NextScene->Load(FullPath5);
   NextScene->GetSceneInfo()->SetMonsterClear(false);
   NextScene->Save(FullPath5);




   // 첫번째 Scene으로 전환
   CSceneManager::GetInst()->CreateNextScene();
   NextScene = CSceneManager::GetInst()->GetNextScene();

   char	FullPath6[MAX_PATH] = {};

   if (Info)
       strcpy_s(FullPath6, Info->PathMultibyte);

   strcat_s(FullPath6, "Scene/NormalScene1.scn");

   NextScene->Load(FullPath6);
   NextScene->GetSceneInfo()->SetMonsterClear(false);
}

void CPlaySlotUI::SlotButton2Click()
{
    CSound* MainBGM = m_Scene->GetResource()->FindSound("MainBGM");
    MainBGM->Stop();

    // 첫번째 Scene으로 전환
}

void CPlaySlotUI::SlotButton3Click()
{
    CSound* MainBGM = m_Scene->GetResource()->FindSound("MainBGM");
    MainBGM->Stop();

    // 첫번째 Scene으로 전환
}

void CPlaySlotUI::SlotExitButtonClick()
{
    SetEnable(false);
}
