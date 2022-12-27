#include "EndingScene.h"
#include "Scene/Scene.h"
#include "Device.h"
#include "../GameObject/EndingBack.h"
#include "../GameObject/EndingTree.h"
#include "../GameObject/EndingTile.h"
#include "../GameObject/Horse.h"
#include "../UI/EndingUI.h"

CEndingScene::CEndingScene()
{
	m_ClassTypeName = "EndingScene";
}

CEndingScene::CEndingScene(const CEndingScene& SceneInfo) :
	CSceneInfo(SceneInfo)
{
}

CEndingScene::~CEndingScene()
{
}

void CEndingScene::Start()
{
}

bool CEndingScene::Init()
{
	Resolution RS = CDevice::GetInst()->GetResolution();

	m_Owner->CreateObject<CEndingBack>("EndingBack");

	m_Owner->CreateObject<CEndingTree>("EndingTree1");
	m_Owner->CreateObject<CEndingTree>("EndingTree2")->SetWorldPositionX(-(float)RS.Width);

	m_Owner->CreateObject<CEndingTile>("Endingile1");
	m_Owner->CreateObject<CEndingTile>("Endingile2")->SetWorldPositionX(-(float)RS.Width);

	m_Owner->CreateObject<CHorse>("Horse");

	m_Owner->GetViewport()->CreateUIWindow<CEndingUI>("EndingUI");

	return true;
}

void CEndingScene::Update(float DeltaTime)
{
	CSceneInfo::Update(DeltaTime);
}

void CEndingScene::SceneChangeComplete()
{
}