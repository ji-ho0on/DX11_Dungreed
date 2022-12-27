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
	// SceneInfo�� ��ӹ޾Ƽ� �ʿ��� Scene���� ����
	CSceneInfo::Init();

	CMonster* Monster = m_Owner->CreateObject<CMonster>("Monster");

	// Scene�� ���� GameObject ����
	CPlayer2D* Player = m_Owner->CreateObject<CPlayer2D>("Player2D");

	// Scene�� Player�� ����
	SetPlayerObject(Player);

	//CMonster* Monster = m_Owner->CreateObject<CMonster>("Monster");


	return true;
}
