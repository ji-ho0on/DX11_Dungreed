#include "TestSceneInfo.h"
#include "Scene/Scene.h"
#include "Scene/SceneViewport.h"
#include "../UI/TestUIWindow.h"
#include "../GameObject/Character.h"

CTestSceneInfo::CTestSceneInfo()
{
	m_ClassTypeName = "TestSceneInfo";
}

CTestSceneInfo::~CTestSceneInfo()
{
}

bool CTestSceneInfo::Init()
{
	// UI ����
	//m_Owner->GetViewport()->CreateUIWindow<CTestUIWindow>("TestUIWindow");


	// GameObject ����
	CCharacter* Character = m_Owner->CreateObject<CCharacter>("Character");

	//m_Owner->CreateObject<CMonster>("Monster");

    return true;
}
