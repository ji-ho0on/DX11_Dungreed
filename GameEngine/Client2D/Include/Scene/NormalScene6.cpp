#include "NormalScene6.h"
#include "Scene/Scene.h"
#include "../GameObject/NormalMap6.h"
#include "../GameObject/BossDoor.h"

CNormalScene6::CNormalScene6()
{
	m_ClassTypeName = "NormalScene6";
}

CNormalScene6::CNormalScene6(const CNormalScene6& SceneInfo) :
	CSceneInfo(SceneInfo)
{
}

CNormalScene6::~CNormalScene6()
{
}

void CNormalScene6::Start()
{
	CSceneInfo::Start();
}

bool CNormalScene6::Init()
{
	m_Owner->CreateObject<CNormalMap6>("NormalMap6");
	m_Owner->CreateObject<CBossDoor>("BossDoor");

	return true;
}

void CNormalScene6::Update(float DeltaTime)
{
	CSceneInfo::Update(DeltaTime);
}

void CNormalScene6::SceneChangeComplete()
{
	CSceneInfo::SceneChangeComplete();
}