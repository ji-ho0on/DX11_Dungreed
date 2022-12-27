#include "NormalMap1.h"
#include "Component/TileMapComponent.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../Animation2D/DoorAnimation.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "PathManager.h"
#include "Character.h"
#include "../TransferInfo/TransferCharacterInfo.h"

CNormalMap1::CNormalMap1()
{
	SetTypeID<CNormalMap1>();

	m_ObjectTypeName = "NormalMap1";
}

CNormalMap1::CNormalMap1(const CNormalMap1& Obj) :
	CGameObject(Obj)
{
	m_NormalMapTile = (CTileMapComponent*)FindComponent("NormalMapTile");
	m_NextSceneTrigger = (CColliderBox2D*)FindComponent("NextSceneTrigger");
}

CNormalMap1::~CNormalMap1()
{
}

void CNormalMap1::Start()
{
	CGameObject::Start();

	m_NextSceneTrigger->SetCollisionCallback<CNormalMap1>(ECollision_Result::Collision, this, &CNormalMap1::TriggerCollision);
}

bool CNormalMap1::Init()
{
	CGameObject::Init();

	m_NormalMapTile = CreateComponent<CTileMapComponent>("NormalMapTile");
	m_NormalMapTile->SetRenderLayerName("Back");
	m_NormalMapTile->SetTileTexture(10, 10, Vector2(64.f, 64.f), "TileAtlas_Revision", TEXT("Map/TileAtlas_Revision.png"));

	m_NextSceneTrigger = CreateComponent<CColliderBox2D>("NextSceneTrigger");
	m_NextSceneTrigger->SetBoxSize(10.f, 256.f);
	m_NextSceneTrigger->SetWorldPosition(1590.f, 192.f);
	m_NextSceneTrigger->SetCollisionProfile("Trigger");

	m_NormalMapTile->AddChild(m_NextSceneTrigger);

	return true;
}

void CNormalMap1::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CNormalMap1::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CNormalMap1* CNormalMap1::Clone() const
{
	return new CNormalMap1(*this);
}

void CNormalMap1::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CNormalMap1::Load(FILE* File)
{
	CGameObject::Load(File);

	m_NormalMapTile = (CTileMapComponent*)FindComponent("NormalMapTile");
	m_NextSceneTrigger = (CColliderBox2D*)FindComponent("NextSceneTrigger");
}

void CNormalMap1::DoorClose()
{
}

void CNormalMap1::TriggerCollision(const CollisionResult& Result)
{
	
	// 다음 씬으로 넘어감
	CSceneManager::GetInst()->CreateNextScene();
	CScene* CurrentScene = CSceneManager::GetInst()->GetScene();
	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();



	// 현재 씬의 MonsterClear 여부를 true로 바꾸고 저장
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	FullPath[MAX_PATH] = {};

	strcpy_s(FullPath, Info->PathMultibyte);
	strcat_s(FullPath, "Scene/NormalScene1.scn");

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
		Character->SetCharacterPosition(Vector2(100.f, 192.f));
	}
}