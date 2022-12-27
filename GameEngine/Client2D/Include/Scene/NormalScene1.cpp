#include "NormalScene1.h"
#include "Scene/Scene.h"
#include "../GameObject/NormalMap1.h"

CNormalScene1::CNormalScene1()
{
	m_ClassTypeName = "NormalScene1";
}

CNormalScene1::CNormalScene1(const CNormalScene1& SceneInfo) :
	CSceneInfo(SceneInfo)
{
}

CNormalScene1::~CNormalScene1()
{
}

void CNormalScene1::Start()
{
	CSceneInfo::Start();
}

bool CNormalScene1::Init()
{
	m_Owner->CreateObject<CNormalMap1>("NormalMap1");

	return true;
}

void CNormalScene1::Update(float DeltaTime)
{
	CSceneInfo::Update(DeltaTime);
}

void CNormalScene1::SceneChangeComplete()
{
	CSceneInfo::SceneChangeComplete();
}