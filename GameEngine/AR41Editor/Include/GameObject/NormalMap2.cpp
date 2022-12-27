#include "NormalMap2.h"
#include "Component/TileMapComponent.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../Animation2D/DoorAnimation.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "PathManager.h"
#include "Character.h"
#include "../TransferInfo/TransferCharacterInfo.h"

CNormalMap2::CNormalMap2()
{
	SetTypeID<CNormalMap2>();

	m_ObjectTypeName = "NormalMap2";
}

CNormalMap2::CNormalMap2(const CNormalMap2& Obj) :
	CGameObject(Obj)
{
	m_NormalMapTile = (CTileMapComponent*)FindComponent("NormalMapTile");
	m_PrevSceneTrigger = (CColliderBox2D*)FindComponent("PrevSceneTrigger");
	m_NextSceneTrigger = (CColliderBox2D*)FindComponent("NextSceneTrigger");
}

CNormalMap2::~CNormalMap2()
{
}

void CNormalMap2::Start()
{
	CGameObject::Start();

	m_PrevSceneTrigger->SetCollisionCallback<CNormalMap2>(ECollision_Result::Collision, this, &CNormalMap2::TriggerCollision1);
	m_NextSceneTrigger->SetCollisionCallback<CNormalMap2>(ECollision_Result::Collision, this, &CNormalMap2::TriggerCollision2);
}

bool CNormalMap2::Init()
{
	CGameObject::Init();

	m_NormalMapTile = CreateComponent<CTileMapComponent>("NormalMapTile");
	m_NormalMapTile->SetRenderLayerName("Back");
	m_NormalMapTile->SetTileTexture(10, 10, Vector2(64.f, 64.f), "TileAtlas_Revision", TEXT("Map/TileAtlas_Revision.png"));

	m_PrevSceneTrigger = CreateComponent<CColliderBox2D>("PrevSceneTrigger");
	m_PrevSceneTrigger->SetBoxSize(10.f, 256.f);
	m_PrevSceneTrigger->SetWorldPosition(0.f, 192.f);
	m_PrevSceneTrigger->SetCollisionProfile("Trigger");

	m_NextSceneTrigger = CreateComponent<CColliderBox2D>("NextSceneTrigger");
	m_NextSceneTrigger->SetBoxSize(10.f, 256.f);
	m_NextSceneTrigger->SetWorldPosition(1590.f, 192.f);
	m_NextSceneTrigger->SetCollisionProfile("Trigger");

	m_NormalMapTile->AddChild(m_PrevSceneTrigger);
	m_NormalMapTile->AddChild(m_NextSceneTrigger);

	return true;
}

void CNormalMap2::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CNormalMap2::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CNormalMap2* CNormalMap2::Clone() const
{
	return new CNormalMap2(*this);
}

void CNormalMap2::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CNormalMap2::Load(FILE* File)
{
	CGameObject::Load(File);

	m_NormalMapTile = (CTileMapComponent*)FindComponent("NormalMapTile");
	m_PrevSceneTrigger = (CColliderBox2D*)FindComponent("PrevSceneTrigger");
	m_NextSceneTrigger = (CColliderBox2D*)FindComponent("NextSceneTrigger");
}

void CNormalMap2::DoorClose()
{
}

void CNormalMap2::TriggerCollision1(const CollisionResult& Result)
{

	// 다음 씬으로 넘어감
	CSceneManager::GetInst()->CreateNextScene();
	CScene* CurrentScene = CSceneManager::GetInst()->GetScene();
	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();



	// 현재 씬의 MonsterClear 여부를 true로 바꾸고 저장
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	FullPath[MAX_PATH] = {};

	strcpy_s(FullPath, Info->PathMultibyte);
	strcat_s(FullPath, "Scene/NormalScene2.scn");

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
	strcat_s(FullPath1, "Scene/NormalScene1.scn");

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

void CNormalMap2::TriggerCollision2(const CollisionResult& Result)
{

	// 다음 씬으로 넘어감
	CSceneManager::GetInst()->CreateNextScene();
	CScene* CurrentScene = CSceneManager::GetInst()->GetScene();
	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();



	// 현재 씬의 MonsterClear 여부를 true로 바꾸고 저장
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	FullPath[MAX_PATH] = {};

	strcpy_s(FullPath, Info->PathMultibyte);
	strcat_s(FullPath, "Scene/NormalScene2.scn");

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
	strcat_s(FullPath1, "Scene/NormalScene3.scn");
	//strcat_s(FullPath1, "Scene/BossEntranceScene.scn");

	NextScene->Load(FullPath1);

	// 현재 씬의 캐릭터 정보를 받아와서 다음 씬의 캐릭터에게 정보를 이전시킴
	CTransferCharacterInfo::GetInst()->ReadInfo((CCharacter*)(CurrentScene->GetSceneInfo()->GetPlayerObject()));

	CCharacter* Character = (CCharacter*)(NextScene->GetSceneInfo()->GetPlayerObject());

	if (Character)
	{
		CTransferCharacterInfo::GetInst()->SetInfo(Character);
		Character->SetCharacterPosition(Vector2(100.f, 192.f));
	}
}