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
	
	// ���� ������ �Ѿ
	CSceneManager::GetInst()->CreateNextScene();
	CScene* CurrentScene = CSceneManager::GetInst()->GetScene();
	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();



	// ���� ���� MonsterClear ���θ� true�� �ٲٰ� ����
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	FullPath[MAX_PATH] = {};

	strcpy_s(FullPath, Info->PathMultibyte);
	strcat_s(FullPath, "Scene/NormalScene1.scn");

	// ���� �ε��ؿͼ� MonsterClear ���θ� �ٲ��ְ� �ٽ� ����
	NextScene->Load(FullPath);
	NextScene->GetSceneInfo()->SetMonsterClear(true);
	NextScene->Save(FullPath);



	// ���� ���� ����
	CSceneManager::GetInst()->CreateNextScene();

	NextScene = CSceneManager::GetInst()->GetNextScene();


	// ���� �� �ε�
	char	FullPath1[MAX_PATH] = {};

	strcpy_s(FullPath1, Info->PathMultibyte);
	strcat_s(FullPath1, "Scene/NormalScene2.scn");

	NextScene->Load(FullPath1);

	// ���� ���� ĳ���� ������ �޾ƿͼ� ���� ���� ĳ���Ϳ��� ������ ������Ŵ
	CTransferCharacterInfo::GetInst()->ReadInfo((CCharacter*)(CurrentScene->GetSceneInfo()->GetPlayerObject()));

	CCharacter* Character = (CCharacter*)(NextScene->GetSceneInfo()->GetPlayerObject());

	if (Character)
	{
		CTransferCharacterInfo::GetInst()->SetInfo(Character);
		Character->SetCharacterPosition(Vector2(100.f, 192.f));
	}
}