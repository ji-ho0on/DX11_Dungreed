#include "NormalScene4.h"
#include "Scene/Scene.h"
#include "../GameObject/NormalMap4.h"

CNormalScene4::CNormalScene4()
{
	m_ClassTypeName = "NormalScene4";
}

CNormalScene4::CNormalScene4(const CNormalScene4& SceneInfo) :
	CSceneInfo(SceneInfo)
{
}

CNormalScene4::~CNormalScene4()
{
}

void CNormalScene4::Start()
{
	CSceneInfo::Start();
}

bool CNormalScene4::Init()
{
	m_Owner->CreateObject<CNormalMap4>("NormalMap4");

	return true;
}

void CNormalScene4::Update(float DeltaTime)
{
	CSceneInfo::Update(DeltaTime);
}

void CNormalScene4::SceneChangeComplete()
{
	CSceneInfo::SceneChangeComplete();
}