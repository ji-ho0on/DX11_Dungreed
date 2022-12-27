#include "NormalMap3.h"
#include "Component/TileMapComponent.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../Animation2D/DoorAnimation.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "PathManager.h"
#include "Character.h"
#include "../TransferInfo/TransferCharacterInfo.h"

CNormalMap3::CNormalMap3()
{
	SetTypeID<CNormalMap3>();

	m_ObjectTypeName = "NormalMap3";
}

CNormalMap3::CNormalMap3(const CNormalMap3& Obj) :
	CGameObject(Obj)
{
	m_NormalMapTile = (CTileMapComponent*)FindComponent("NormalMapTile");
	m_SceneTrigger1 = (CColliderBox2D*)FindComponent("SceneTrigger1");
	m_SceneTrigger2 = (CColliderBox2D*)FindComponent("SceneTrigger2");
	m_SceneTrigger3 = (CColliderBox2D*)FindComponent("SceneTrigger3");
}

CNormalMap3::~CNormalMap3()
{
}

void CNormalMap3::Start()
{
	CGameObject::Start();

	m_SceneTrigger1->SetCollisionCallback<CNormalMap3>(ECollision_Result::Collision, this, &CNormalMap3::TriggerCollision1);
	m_SceneTrigger2->SetCollisionCallback<CNormalMap3>(ECollision_Result::Collision, this, &CNormalMap3::TriggerCollision2);
	m_SceneTrigger3->SetCollisionCallback<CNormalMap3>(ECollision_Result::Collision, this, &CNormalMap3::TriggerCollision3);
}

bool CNormalMap3::Init()
{
	CGameObject::Init();

	m_NormalMapTile = CreateComponent<CTileMapComponent>("NormalMapTile");
	m_NormalMapTile->SetRenderLayerName("Back");
	m_NormalMapTile->SetTileTexture(10, 10, Vector2(64.f, 64.f), "TileAtlas_Revision", TEXT("Map/TileAtlas_Revision.png"));

	m_SceneTrigger1 = CreateComponent<CColliderBox2D>("SceneTrigger1");
	m_SceneTrigger1->SetBoxSize(10.f, 256.f);
	m_SceneTrigger1->SetWorldPosition(0.f, 128.f);
	m_SceneTrigger1->SetCollisionProfile("Trigger");

	m_SceneTrigger2 = CreateComponent<CColliderBox2D>("SceneTrigger2");
	m_SceneTrigger2->SetBoxSize(10.f, 256.f);
	m_SceneTrigger2->SetWorldPosition(1526.f, 448.f);
	m_SceneTrigger2->SetCollisionProfile("Trigger");

	m_SceneTrigger3 = CreateComponent<CColliderBox2D>("SceneTrigger3");
	m_SceneTrigger3->SetBoxSize(256.f, 10.f);
	m_SceneTrigger3->SetWorldPosition(640.f, 886.f);
	m_SceneTrigger3->SetCollisionProfile("Trigger");

	m_NormalMapTile->AddChild(m_SceneTrigger1);
	m_NormalMapTile->AddChild(m_SceneTrigger2);
	m_NormalMapTile->AddChild(m_SceneTrigger3);

	return true;
}

void CNormalMap3::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CNormalMap3::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CNormalMap3* CNormalMap3::Clone() const
{
	return new CNormalMap3(*this);
}

void CNormalMap3::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CNormalMap3::Load(FILE* File)
{
	CGameObject::Load(File);

	m_NormalMapTile = (CTileMapComponent*)FindComponent("NormalMapTile");
	m_SceneTrigger1 = (CColliderBox2D*)FindComponent("SceneTrigger1");
	m_SceneTrigger2 = (CColliderBox2D*)FindComponent("SceneTrigger2");
	m_SceneTrigger3 = (CColliderBox2D*)FindComponent("SceneTrigger3");
}

void CNormalMap3::DoorClose()
{
}

void CNormalMap3::TriggerCollision1(const CollisionResult& Result)
{

	// 다음 씬으로 넘어감
	CSceneManager::GetInst()->CreateNextScene();
	CScene* CurrentScene = CSceneManager::GetInst()->GetScene();
	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();



	// 현재 씬의 MonsterClear 여부를 true로 바꾸고 저장
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	FullPath[MAX_PATH] = {};

	strcpy_s(FullPath, Info->PathMultibyte);
	strcat_s(FullPath, "Scene/NormalScene3.scn");

	// 새로 로드해와서 MonsterClear 여부만 바꿔주고 다시 저장
	NextScene->Load(FullPath);
	NextScene->GetSceneInfo()->SetMonsterClear(true);
	NextScene->Save(FullPath);



	// 씬을 새로 만듬
	CSceneManager::GetInst()->CreateNextScene();

	NextScene = CSceneManager::GetInst()->GetNextScene();


	// 다음 씬 로드
	char	FullPath1[MAX_PATH] = {};

	strcpy_s(FullPath1, Info->PathMultibyte);
	strcat_s(FullPath1, "Scene/NormalScene2.scn");

	NextScene->Load(FullPath1);

	// 현재 씬의 캐릭터 정보를 받아와서 다음 씬의 캐릭터에게 정보를 이전시킴
	CTransferCharacterInfo::GetInst()->ReadInfo((CCharacter*)(CurrentScene->GetSceneInfo()->GetPlayerObject()));

	CCharacter* Character = (CCharacter*)(NextScene->GetSceneInfo()->GetPlayerObject());

	if (Character)
	{
		CTransferCharacterInfo::GetInst()->SetInfo(Character);
		Character->SetCharacterPosition(Vector2(1500.f, 192.f));
	}
}

void CNormalMap3::TriggerCollision2(const CollisionResult& Result)
{

	// 다음 씬으로 넘어감
	CSceneManager::GetInst()->CreateNextScene();
	CScene* CurrentScene = CSceneManager::GetInst()->GetScene();
	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();



	// 현재 씬의 MonsterClear 여부를 true로 바꾸고 저장
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	FullPath[MAX_PATH] = {};

	strcpy_s(FullPath, Info->PathMultibyte);
	strcat_s(FullPath, "Scene/NormalScene3.scn");

	// 새로 로드해와서 MonsterClear 여부만 바꿔주고 다시 저장
	NextScene->Load(FullPath);
	NextScene->GetSceneInfo()->SetMonsterClear(true);
	NextScene->Save(FullPath);



	// 씬을 새로 만듬
	CSceneManager::GetInst()->CreateNextScene();

	NextScene = CSceneManager::GetInst()->GetNextScene();


	// 다음 씬 로드
	char	FullPath1[MAX_PATH] = {};

	strcpy_s(FullPath1, Info->PathMultibyte);
	strcat_s(FullPath1, "Scene/NormalScene4.scn");

	NextScene->Load(FullPath1);

	// 현재 씬의 캐릭터 정보를 받아와서 다음 씬의 캐릭터에게 정보를 이전시킴
	CTransferCharacterInfo::GetInst()->ReadInfo((CCharacter*)(CurrentScene->GetSceneInfo()->GetPlayerObject()));

	CCharacter* Character = (CCharacter*)(NextScene->GetSceneInfo()->GetPlayerObject());

	if (Character)
	{
		CTransferCharacterInfo::GetInst()->SetInfo(Character);
		Character->SetCharacterPosition(Vector2(80.f, 448.f));
	}
}

void CNormalMap3::TriggerCollision3(const CollisionResult& Result)
{

	// 다음 씬으로 넘어감
	CSceneManager::GetInst()->CreateNextScene();
	CScene* CurrentScene = CSceneManager::GetInst()->GetScene();
	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();



	// 현재 씬의 MonsterClear 여부를 true로 바꾸고 저장
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	FullPath[MAX_PATH] = {};

	strcpy_s(FullPath, Info->PathMultibyte);
	strcat_s(FullPath, "Scene/NormalScene3.scn");

	// 새로 로드해와서 MonsterClear 여부만 바꿔주고 다시 저장
	NextScene->Load(FullPath);
	NextScene->GetSceneInfo()->SetMonsterClear(true);
	NextScene->Save(FullPath);



	// 씬을 새로 만듬
	CSceneManager::GetInst()->CreateNextScene();

	NextScene = CSceneManager::GetInst()->GetNextScene();


	// 다음 씬 로드
	char	FullPath1[MAX_PATH] = {};

	strcpy_s(FullPath1, Info->PathMultibyte);
	strcat_s(FullPath1, "Scene/NormalScene5.scn");

	NextScene->Load(FullPath1);

	// 현재 씬의 캐릭터 정보를 받아와서 다음 씬의 캐릭터에게 정보를 이전시킴
	CTransferCharacterInfo::GetInst()->ReadInfo((CCharacter*)(CurrentScene->GetSceneInfo()->GetPlayerObject()));

	CCharacter* Character = (CCharacter*)(NextScene->GetSceneInfo()->GetPlayerObject());

	if (Character)
	{
		CTransferCharacterInfo::GetInst()->SetInfo(Character);
		Character->SetCharacterPosition(Vector2(710.f, 128.f));
	}
}