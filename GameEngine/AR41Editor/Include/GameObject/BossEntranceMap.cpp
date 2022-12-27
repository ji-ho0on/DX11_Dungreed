#include "BossEntranceMap.h"
#include "Component/TileMapComponent.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../Animation2D/DoorAnimation.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "PathManager.h"
#include "Character.h"
#include "../TransferInfo/TransferCharacterInfo.h"

CBossEntranceMap::CBossEntranceMap()
{
	SetTypeID<CBossEntranceMap>();

	m_ObjectTypeName = "BossEntranceMap";
}

CBossEntranceMap::CBossEntranceMap(const CBossEntranceMap& Obj) :
	CGameObject(Obj)
{
	m_BossEntranceMapTile = (CTileMapComponent*)FindComponent("BossEntranceMapTile");
	m_Door = (CSpriteComponent*)FindComponent("Door");
	m_NextSceneTrigger = (CColliderBox2D*)FindComponent("NextSceneTrigger");
}

CBossEntranceMap::~CBossEntranceMap()
{
}

void CBossEntranceMap::Start()
{
	CGameObject::Start();

	m_NextSceneTrigger->SetCollisionCallback<CBossEntranceMap>(ECollision_Result::Collision, this, &CBossEntranceMap::TriggerCollision);

	m_Scene->GetResource()->FindSound("ambience_prison")->Play();
}

bool CBossEntranceMap::Init()
{
	CGameObject::Init();

	m_BossEntranceMapTile = CreateComponent<CTileMapComponent>("BossEntranceMapTile");
	m_BossEntranceMapTile->SetRenderLayerName("Back");
	m_BossEntranceMapTile->SetTileTexture(10, 10, Vector2(64.f, 64.f), "TileAtlas_Revision", TEXT("Map/TileAtlas_Revision.png"));

	m_Door = CreateComponent<CSpriteComponent>("Door");
	m_Door->SetAnimation<CDoorAnimation>("DoorAnimation");
	m_Door->SetPivot(0.5f, 0.f);
	m_Door->SetWorldScale(200.f, 230.f);
	m_Door->SetWorldPosition(480.f, 192.f);
	m_Door->SetRenderLayerName("Back1");
	m_Door->Set2DZOffset(500.f);
	m_Door->GetAnimation()->SetPlay(false);

	m_NextSceneTrigger = CreateComponent<CColliderBox2D>("NextSceneTrigger");
	m_NextSceneTrigger->SetBoxSize(10.f, 256.f);
	m_NextSceneTrigger->SetWorldPosition(1334.f, 192.f);
	m_NextSceneTrigger->SetCollisionProfile("Trigger");

	m_BossEntranceMapTile->AddChild(m_Door);
	m_BossEntranceMapTile->AddChild(m_NextSceneTrigger);

	if (m_Scene)
	{
		// 보스 시작 BGM
		m_Scene->GetResource()->LoadSound("BGM", "ambience_prison", true, "stage/bgm/ambience_prison.wav");
	}

	else
	{
		// 보스 시작 BGM
		CResourceManager::GetInst()->LoadSound("BGM", "ambience_prison", true, "stage/bgm/ambience_prison.wav");
	}

	return true;
}

void CBossEntranceMap::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBossEntranceMap::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBossEntranceMap* CBossEntranceMap::Clone() const
{
	return new CBossEntranceMap(*this);
}

void CBossEntranceMap::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CBossEntranceMap::Load(FILE* File)
{
	CGameObject::Load(File);

	m_BossEntranceMapTile = (CTileMapComponent*)FindComponent("BossEntranceMapTile");
	m_Door = (CSpriteComponent*)FindComponent("Door");
	m_NextSceneTrigger = (CColliderBox2D*)FindComponent("NextSceneTrigger");
}

void CBossEntranceMap::DoorClose()
{
	m_Door->GetAnimation()->SetPlay(true);
}

void CBossEntranceMap::TriggerCollision(const CollisionResult& Result)
{
	// BossScene으로 넘어감
	CSceneManager::GetInst()->CreateNextScene();
	CScene* CurrentScene = CSceneManager::GetInst()->GetScene();
	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();

	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	FullPath[MAX_PATH] = {};

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, "Scene/");
	strcat_s(FullPath, "BossScene");
	strcat_s(FullPath, ".scn");

	NextScene->Load(FullPath);

	CTransferCharacterInfo::GetInst()->ReadInfo((CCharacter*)(CurrentScene->GetSceneInfo()->GetPlayerObject()));

	CCharacter* Character = (CCharacter*)(NextScene->GetSceneInfo()->GetPlayerObject());

	if (Character)
	{
		CTransferCharacterInfo::GetInst()->SetInfo(Character);
		Character->SetCharacterPosition(Vector2(100.f, 192.f));
	}
}