#include "NormalMap4.h"
#include "Component/TileMapComponent.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../Animation2D/DoorAnimation.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "PathManager.h"
#include "Character.h"
#include "../TransferInfo/TransferCharacterInfo.h"

CNormalMap4::CNormalMap4()
{
	SetTypeID<CNormalMap4>();

	m_ObjectTypeName = "NormalMap4";
}

CNormalMap4::CNormalMap4(const CNormalMap4& Obj) :
	CGameObject(Obj)
{
	m_NormalMapTile = (CTileMapComponent*)FindComponent("NormalMapTile");
	m_SceneTrigger = (CColliderBox2D*)FindComponent("SceneTrigger");
}

CNormalMap4::~CNormalMap4()
{
}

void CNormalMap4::Start()
{
	CGameObject::Start();

	m_SceneTrigger->SetCollisionCallback<CNormalMap4>(ECollision_Result::Collision, this, &CNormalMap4::TriggerCollision);
}

bool CNormalMap4::Init()
{
	CGameObject::Init();

	m_NormalMapTile = CreateComponent<CTileMapComponent>("NormalMapTile");
	m_NormalMapTile->SetRenderLayerName("Back");
	m_NormalMapTile->SetTileTexture(10, 10, Vector2(64.f, 64.f), "TileAtlas_Revision", TEXT("Map/TileAtlas_Revision.png"));

	m_SceneTrigger = CreateComponent<CColliderBox2D>("SceneTrigger");
	m_SceneTrigger->SetBoxSize(10.f, 256.f);
	m_SceneTrigger->SetWorldPosition(1590.f, 192.f);
	m_SceneTrigger->SetCollisionProfile("Trigger");

	m_NormalMapTile->AddChild(m_SceneTrigger);

	return true;
}

void CNormalMap4::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CNormalMap4::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CNormalMap4* CNormalMap4::Clone() const
{
	return new CNormalMap4(*this);
}

void CNormalMap4::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CNormalMap4::Load(FILE* File)
{
	CGameObject::Load(File);

	m_NormalMapTile = (CTileMapComponent*)FindComponent("NormalMapTile");
	m_SceneTrigger = (CColliderBox2D*)FindComponent("SceneTrigger");
}

void CNormalMap4::DoorClose()
{
}

void CNormalMap4::TriggerCollision(const CollisionResult& Result)
{

	// 다음 씬으로 넘어감
	CSceneManager::GetInst()->CreateNextScene();
	CScene* CurrentScene = CSceneManager::GetInst()->GetScene();
	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();



	// 현재 씬의 MonsterClear 여부를 true로 바꾸고 저장
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	FullPath[MAX_PATH] = {};

	strcpy_s(FullPath, Info->PathMultibyte);
	strcat_s(FullPath, "Scene/NormalScene4.scn");

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
		Character->SetCharacterPosition(Vector2(1450.f, 448.f));
	}
}