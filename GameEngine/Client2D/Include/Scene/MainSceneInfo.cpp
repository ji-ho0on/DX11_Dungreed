#include "MainSceneInfo.h"
#include "Scene/Scene.h"
#include "../GameObject/Player2D.h"
#include "../GameObject/Monster.h"

CMainSceneInfo::CMainSceneInfo()
{
	m_ClassTypeName = "MainSceneInfo";
}

CMainSceneInfo::~CMainSceneInfo()
{
}

bool CMainSceneInfo::Init()
{
	// SceneInfo를 상속받아서 필요한 Scene마다 생성
	CSceneInfo::Init();

	CMonster* Monster = m_Owner->CreateObject<CMonster>("Monster");

	// Scene을 통해 GameObject 생성
	CPlayer2D* Player = m_Owner->CreateObject<CPlayer2D>("Player2D");

	// Scene에 Player를 지정
	SetPlayerObject(Player);

	//CMonster* Monster = m_Owner->CreateObject<CMonster>("Monster");


	return true;
}
