#include "NormalScene5.h"
#include "Scene/Scene.h"
#include "../GameObject/NormalMap5.h"

CNormalScene5::CNormalScene5()
{
	m_ClassTypeName = "NormalScene5";
}

CNormalScene5::CNormalScene5(const CNormalScene5& SceneInfo) :
	CSceneInfo(SceneInfo)
{
}

CNormalScene5::~CNormalScene5()
{
}

void CNormalScene5::Start()
{
	CSceneInfo::Start();
}

bool CNormalScene5::Init()
{
	m_Owner->CreateObject<CNormalMap5>("NormalMap5");

	return true;
}

void CNormalScene5::Update(float DeltaTime)
{
	CSceneInfo::Update(DeltaTime);
}

void CNormalScene5::SceneChangeComplete()
{
	CSceneInfo::SceneChangeComplete();
}