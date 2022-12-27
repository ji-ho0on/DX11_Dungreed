#include "MainScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Scene/SceneViewport.h"
#include "../UI/MainUI.h"
#include "../UI/PlaySlotUI.h"
#include "../UI/SettingUI.h"
#include "../GameObject/Bird.h"
#include "../GameObject/FrontCloud.h"
#include "../GameObject/BackCloud.h"
#include "Device.h"
#include "Resource/Sound/Sound.h"
#include "Input.h"

CMainScene::CMainScene()
{
	m_ClassTypeName = "MainScene";
}

CMainScene::CMainScene(const CMainScene& SceneInfo)	:
	CSceneInfo(SceneInfo)
{
	m_MainUI = m_Owner->GetViewport()->FindUIWindow<CMainUI>("MainUI");
	m_PlaySlotUI = m_Owner->GetViewport()->FindUIWindow<CPlaySlotUI>("PlaySlotUI");
	m_SettingUI = m_Owner->GetViewport()->FindUIWindow<CSettingUI>("SettingUI");

	m_FrontCloud1 = (CFrontCloud*)m_Owner->FindObject("FrontCloud1");
	m_FrontCloud2 = (CFrontCloud*)m_Owner->FindObject("FrontCloud2");
	m_BackCloud1 = (CBackCloud*)m_Owner->FindObject("BackCloud1");
	m_BackCloud2 = (CBackCloud*)m_Owner->FindObject("BackCloud2");
}

CMainScene::~CMainScene()
{
	CInput::GetInst()->SetMouseTexture("ShootingMouse", TEXT("common/cursor/ShootingCursor2.png"));

	//CSound* MainBGM = m_Owner->GetResource()->FindSound("MainBGM");
	//MainBGM->Stop();
}

void CMainScene::Start()
{
	CreateBird(Vector2(-100.f, 40.f));		// Copyright 바로위
	CreateBird(Vector2(-500.f, 510.f));		// 눈알 가운데
	CreateBirds(Vector2(-1000.f, 270.f));	// 로고 바로 아래
	CreateBird(Vector2(-1650.f, 570.f));	// 눈알 조금 위
	CreateBird(Vector2(-1950.f, 100.f));	// 종료 아래랑 겹침
	CreateBird(Vector2(-2300.f, 380.f));	// 로고 D 가운데
	CreateBirds(Vector2(-2650.f, 520.f));	// 눈알 가운데

	CSound* MainBGM = m_Owner->GetResource()->FindSound("MainBGM");
	MainBGM->Stop();
	MainBGM->Play();
}

bool CMainScene::Init()
{
	m_MainUI = m_Owner->GetViewport()->CreateUIWindow<CMainUI>("MainUI");
	m_MainUI->SetZOrder(2);

	m_PlaySlotUI = m_Owner->GetViewport()->CreateUIWindow<CPlaySlotUI>("PlaySlotUI");
	m_PlaySlotUI->SetEnable(false);
	m_PlaySlotUI->SetZOrder(1);

	m_SettingUI = m_Owner->GetViewport()->CreateUIWindow<CSettingUI>("SettingUI");
	m_SettingUI->SetEnable(false);
	m_SettingUI->SetZOrder(0);

	Resolution Resolution = CDevice::GetInst()->GetResolution();

	m_FrontCloud1 = m_Owner->CreateObject<CFrontCloud>("FrontCloud1");
	m_FrontCloud1->SetWorldScale((float)Resolution.Width, (float)Resolution.Height);

	m_FrontCloud2 = m_Owner->CreateObject<CFrontCloud>("FrontCloud2");
	m_FrontCloud2->SetWorldScale((float)Resolution.Width, (float)Resolution.Height);
	m_FrontCloud2->SetWorldPositionX((float)Resolution.Width);

	m_BackCloud1 = m_Owner->CreateObject<CBackCloud>("BackCloud1");
	m_BackCloud1->SetWorldScale((float)Resolution.Width, (float)Resolution.Height);

	m_BackCloud2 = m_Owner->CreateObject<CBackCloud>("BackCloud2");
	m_BackCloud2->SetWorldScale((float)Resolution.Width, (float)Resolution.Height);
	m_BackCloud2->SetWorldPositionX((float)Resolution.Width);

	m_Owner->GetResource()->LoadSound("BGM", "MainBGM", true, "UI/bgm/title.wav");
	m_Owner->GetResource()->LoadSound("BGM", "JailField", true, "UI/bgm/1.JailField.wav");

	return true;
}

void CMainScene::Update(float DeltaTime)
{
	CSceneInfo::Update(DeltaTime);
}

void CMainScene::SceneChangeComplete()
{
}

void CMainScene::CreateBird(const Vector2& Pos)
{
	CBird* Bird = m_Owner->CreateObject<CBird>("Bird");
	Bird->SetWorldPosition(Pos);
}

void CMainScene::CreateBirds(const Vector2& Pos)
{
	CBird* Bird = m_Owner->CreateObject<CBird>("Bird");
	Bird->SetWorldPosition(Pos);

	Bird = m_Owner->CreateObject<CBird>("Bird");
	Bird->SetWorldPosition(Pos.x - 40.f, Pos.y + 30.f);

	Bird = m_Owner->CreateObject<CBird>("Bird");
	Bird->SetWorldPosition(Pos.x - 80.f, Pos.y + 60.f);

	Bird = m_Owner->CreateObject<CBird>("Bird");
	Bird->SetWorldPosition(Pos.x - 40.f, Pos.y - 30.f);

	Bird = m_Owner->CreateObject<CBird>("Bird");
	Bird->SetWorldPosition(Pos.x - 80.f, Pos.y - 60.f);
}
