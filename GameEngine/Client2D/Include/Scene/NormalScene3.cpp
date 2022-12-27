#include "NormalScene3.h"
#include "Scene/Scene.h"
#include "../GameObject/NormalMap3.h"

CNormalScene3::CNormalScene3()
{
	m_ClassTypeName = "NormalScene3";
}

CNormalScene3::CNormalScene3(const CNormalScene3& SceneInfo) :
	CSceneInfo(SceneInfo)
{
}

CNormalScene3::~CNormalScene3()
{
	CSceneInfo::Start();
}

void CNormalScene3::Start()
{
}

bool CNormalScene3::Init()
{
	m_Owner->CreateObject<CNormalMap3>("NormalMap3");

	return true;
}

void CNormalScene3::Update(float DeltaTime)
{
	CSceneInfo::Update(DeltaTime);
}

void CNormalScene3::SceneChangeComplete()
{
	CSceneInfo::SceneChangeComplete();
}