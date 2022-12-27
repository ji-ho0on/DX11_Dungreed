#include "NormalScene.h"
#include "GameObject/GameObject.h"
#include "Scene/Scene.h"

CNormalScene::CNormalScene()
{
	m_ClassTypeName = "NormalScene";
}

CNormalScene::CNormalScene(const CNormalScene& SceneInfo) :
	CSceneInfo(SceneInfo)
{
}

CNormalScene::~CNormalScene()
{
}

void CNormalScene::Start()
{
}

bool CNormalScene::Init()
{
	return true;
}

void CNormalScene::Update(float DeltaTime)
{
	CSceneInfo::Update(DeltaTime);
}

void CNormalScene::SceneChangeComplete()
{
}