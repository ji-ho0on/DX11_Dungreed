#include "BossScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneViewport.h"
#include "../GameObject/BossMap.h"
#include "../GameObject/Belial.h"

CBossScene::CBossScene()
{
	m_ClassTypeName = "BossScene";
}

CBossScene::CBossScene(const CBossScene& SceneInfo) :
	CSceneInfo(SceneInfo)
{
}

CBossScene::~CBossScene()
{
}

void CBossScene::Start()
{
}

bool CBossScene::Init()
{
	m_Owner->CreateObject<CBossMap>("BossMap");

	return true;
}

void CBossScene::Update(float DeltaTime)
{
	CSceneInfo::Update(DeltaTime);
}

void CBossScene::SceneChangeComplete()
{
}