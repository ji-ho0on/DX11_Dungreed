#include "BossEntranceScene.h"
#include "Scene/Scene.h"
#include "../GameObject/BossEntranceMap.h"

CBossEntranceScene::CBossEntranceScene()
{
	m_ClassTypeName = "BossEntranceScene";
}

CBossEntranceScene::CBossEntranceScene(const CBossEntranceScene& SceneInfo) :
	CSceneInfo(SceneInfo)
{
}

CBossEntranceScene::~CBossEntranceScene()
{
}

void CBossEntranceScene::Start()
{
}

bool CBossEntranceScene::Init()
{
	m_BossEntranceMap = m_Owner->CreateObject<CBossEntranceMap>("BossEntranceMap");

	return true;
}

void CBossEntranceScene::Update(float DeltaTime)
{
	CSceneInfo::Update(DeltaTime);
}

void CBossEntranceScene::SceneChangeComplete()
{
	m_BossEntranceMap->DoorClose();
}