#include "NormalMap5.h"
#include "Component/TileMapComponent.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../Animation2D/DoorAnimation.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "PathManager.h"
#include "Character.h"
#include "../TransferInfo/TransferCharacterInfo.h"

CNormalMap5::CNormalMap5()
{
	SetTypeID<CNormalMap5>();

	m_ObjectTypeName = "NormalMap5";
}

CNormalMap5::CNormalMap5(const CNormalMap5& Obj) :
	CGameObject(Obj)
{
	m_NormalMapTile = (CTileMapComponent*)FindComponent("NormalMapTile");
	m_SceneTrigger1 = (CColliderBox2D*)FindComponent("SceneTrigger1");
	m_SceneTrigger2 = (CColliderBox2D*)FindComponent("SceneTrigger2");
}

CNormalMap5::~CNormalMap5()
{
}

void CNormalMap5::Start()
{
	CGameObject::Start();

	m_SceneTrigger1->SetCollisionCallback<CNormalMap5>(ECollision_Result::Collision, this, &CNormalMap5::TriggerCollision1);
	m_SceneTrigger2->SetCollisionCallback<CNormalMap5>(ECollision_Result::Collision, this, &CNormalMap5::TriggerCollision2);
}

bool CNormalMap5::Init()
{
	CGameObject::Init();

	m_NormalMapTile = CreateComponent<CTileMapComponent>("NormalMapTile");
	m_NormalMapTile->SetRenderLayerName("Back");
	m_NormalMapTile->SetTileTexture(10, 10, Vector2(64.f, 64.f), "TileAtlas_Revision", TEXT("Map/TileAtlas_Revision.png"));

	m_SceneTrigger1 = CreateComponent<CColliderBox2D>("SceneTrigger1");
	m_SceneTrigger1->SetBoxSize(256.f, 10.f);
	m_SceneTrigger1->SetWorldPosition(512.f, 886.f);
	m_SceneTrigger1->SetCollisionProfile("Trigger");

	m_SceneTrigger2 = CreateComponent<CColliderBox2D>("SceneTrigger2");
	m_SceneTrigger2->SetBoxSize(256.f, 10.f);
	m_SceneTrigger2->SetWorldPosition(576.f, 0.f);
	m_SceneTrigger2->SetCollisionProfile("Trigger");

	m_NormalMapTile->AddChild(m_SceneTrigger1);
	m_NormalMapTile->AddChild(m_SceneTrigger2);

	return true;
}

void CNormalMap5::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CNormalMap5::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CNormalMap5* CNormalMap5::Clone() const
{
	return new CNormalMap5(*this);
}

void CNormalMap5::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CNormalMap5::Load(FILE* File)
{
	CGameObject::Load(File);

	m_NormalMapTile = (CTileMapComponent*)FindComponent("NormalMapTile");
	m_SceneTrigger1 = (CColliderBox2D*)FindComponent("SceneTrigger1");
	m_SceneTrigger2 = (CColliderBox2D*)FindComponent("SceneTrigger2");
}

void CNormalMap5::DoorClose()
{
}

void CNormalMap5::TriggerCollision1(const CollisionResult& Result)
{

	// 다음 씬으로 넘어감
	CSceneManager::GetInst()->CreateNextScene();
	CScene* CurrentScene = CSceneManager::GetInst()->GetScene();
	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();



	// 현재 씬의 MonsterClear 여부를 true로 바꾸고 저장
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	FullPath[MAX_PATH] = {};

	strcpy_s(FullPath, Info->PathMultibyte);
	strcat_s(FullPath, "Scene/NormalScene5.scn");

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

	NextScene->Load(FullPath1);

	// 현재 씬의 캐릭터 정보를 받아와서 다음 씬의 캐릭터에게 정보를 이전시킴
	CTransferCharacterInfo::GetInst()->ReadInfo((CCharacter*)(CurrentScene->GetSceneInfo()->GetPlayerObject()));

	CCharacter* Character = (CCharacter*)(NextScene->GetSceneInfo()->GetPlayerObject());

	if (Character)
	{
		CTransferCharacterInfo::GetInst()->SetInfo(Character);

		// 조정해야함
		Character->SetCharacterPosition(Vector2(770.f, 760.f));
	}
}

void CNormalMap5::TriggerCollision2(const CollisionResult& Result)
{

	// 다음 씬으로 넘어감
	CSceneManager::GetInst()->CreateNextScene();
	CScene* CurrentScene = CSceneManager::GetInst()->GetScene();
	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();



	// 현재 씬의 MonsterClear 여부를 true로 바꾸고 저장
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	FullPath[MAX_PATH] = {};

	strcpy_s(FullPath, Info->PathMultibyte);
	strcat_s(FullPath, "Scene/NormalScene5.scn");

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
	strcat_s(FullPath1, "Scene/NormalScene6.scn");

	NextScene->Load(FullPath1);

	// 현재 씬의 캐릭터 정보를 받아와서 다음 씬의 캐릭터에게 정보를 이전시킴
	CTransferCharacterInfo::GetInst()->ReadInfo((CCharacter*)(CurrentScene->GetSceneInfo()->GetPlayerObject()));

	CCharacter* Character = (CCharacter*)(NextScene->GetSceneInfo()->GetPlayerObject());

	if (Character)
	{
		CTransferCharacterInfo::GetInst()->SetInfo(Character);

		// 조정해야함
		Character->SetCharacterPosition(Vector2(252.f, 128.f));
	}
}