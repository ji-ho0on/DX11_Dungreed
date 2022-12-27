#include "TownScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneViewport.h"
#include "../GameObject/TownBack.h"

CTownScene::CTownScene()
{
	m_ClassTypeName = "TownScene";
}

CTownScene::CTownScene(const CTownScene& SceneInfo)
{
}

CTownScene::~CTownScene()
{
}

void CTownScene::Start()
{
}

bool CTownScene::Init()
{
	m_Owner->CreateObject<CTownBack>("TownBack");

	return true;
}

void CTownScene::Update(float DeltaTime)
{
	CSceneInfo::Update(DeltaTime);
}

void CTownScene::SceneChangeComplete()
{
}
