#include "NormalScene2.h"
#include "Scene/Scene.h"
#include "../GameObject/NormalMap2.h"

CNormalScene2::CNormalScene2()
{
	m_ClassTypeName = "NormalScene2";
}

CNormalScene2::CNormalScene2(const CNormalScene2& SceneInfo) :
	CSceneInfo(SceneInfo)
{
}

CNormalScene2::~CNormalScene2()
{
	CSceneInfo::Start();
}

void CNormalScene2::Start()
{
}

bool CNormalScene2::Init()
{
	m_Owner->CreateObject<CNormalMap2>("NormalMap2");

	return true;
}

void CNormalScene2::Update(float DeltaTime)
{
	CSceneInfo::Update(DeltaTime);
}

void CNormalScene2::SceneChangeComplete()
{
	CSceneInfo::SceneChangeComplete();
}