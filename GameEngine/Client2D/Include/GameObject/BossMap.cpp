#include "BossMap.h"
#include "Component/TileMapComponent.h"
#include "Component/ColliderBox2D.h"
#include "Scene/Scene.h"
#include "Belial.h"

CBossMap::CBossMap()
{
	SetTypeID<CBossMap>();

	m_ObjectTypeName = "BossMap";
}

CBossMap::CBossMap(const CBossMap& Obj) :
	CGameObject(Obj)
{
	m_BossMapTile = (CTileMapComponent*)FindComponent("BossMapTile");
	m_BossTrigger = (CColliderBox2D*)FindComponent("BossTrigger");
}

CBossMap::~CBossMap()
{
}

void CBossMap::Start()
{
	CGameObject::Start();

	m_BossTrigger->SetCollisionCallback<CBossMap>(ECollision_Result::Collision, this, &CBossMap::TriggerCollision);



}

bool CBossMap::Init()
{
	CGameObject::Init();

	m_BossMapTile = CreateComponent<CTileMapComponent>("BossMapTile");
	m_BossMapTile->SetRenderLayerName("Back");
	m_BossMapTile->SetTileTexture(10, 10, Vector2(64.f, 64.f), "TileAtlas_Revision", TEXT("Map/TileAtlas_Revision.png"));

	m_BossTrigger = CreateComponent<CColliderBox2D>("BossTrigger");
	m_BossTrigger->SetBoxSize(10.f, 1300.f);
	m_BossTrigger->SetWorldPositionX(650.f);
	m_BossTrigger->SetCollisionProfile("Trigger");

	m_BossMapTile->AddChild(m_BossTrigger);

	//m_BossMapTile->CreateTile(ETileShape::Rect, 22, 20, Vector2(64.f, 64.f));
	//int CountX = m_BossMapTile->GetCountX();
	//int CountY = m_BossMapTile->GetCountY();

	//for (int i = 0; i < 2; ++i)
	//{
	//	for (int j = 0; j < CountX; ++j)
	//	{
	//		m_BossMapTile->ChangeTileOption((i * CountX + j), ETileOption::Wall);
	//		m_BossMapTile->ChangeTileFrame((i * CountX + j), 72);
	//	}
	//}

	//for (int i = 2; i < 3; ++i)
	//{
	//	for (int j = 0; j < CountX; ++j)
	//	{
	//		m_BossMapTile->ChangeTileOption((i * CountX + j), ETileOption::Wall);
	//		m_BossMapTile->ChangeTileFrame((i * CountX + j), 62);
	//	}
	//}

	//for (int i = 3; i < CountY; ++i)
	//{
	//	for (int j = 0; j < CountX; ++j)
	//	{
	//		m_BossMapTile->ChangeTileFrame((i * CountX + j), 11);
	//	}
	//}


	//// X : 0번 줄
	//for (int i = 3; i <= 5; ++i)
	//{
	//	for (int j = 0; j < 1; ++j)
	//	{
	//		m_BossMapTile->ChangeTileFrame((i * CountX + j), 10);

	//		//m_BossMapTile->ChangeTileFrame((i * CountY + (CountX - j)), 10);
	//	}
	//}

	//m_BossMapTile->ChangeTileFrame((6 * CountX + 0), 0);
	////m_BossMapTile->ChangeTileFrame((6 * CountY + (CountX - 0)), 0);


	//m_BossMapTile->ChangeTileFrame((7 * CountX + 0), 82);
	////m_BossMapTile->ChangeTileFrame((7 * CountY + (CountX - 0)), 62);

	//for (int i = 8; i <= CountY; ++i)
	//{
	//	for (int j = 0; j < 1; ++j)
	//	{
	//		m_BossMapTile->ChangeTileFrame((i * CountX + j), 99);

	//		//m_BossMapTile->ChangeTileFrame((i * CountY + (CountX - j)), 99);
	//	}
	//}

	//// X : 1번 줄 + 반대쪽
	//m_BossMapTile->ChangeTileFrame((6 * CountX + 1), 1);
	////m_BossMapTile->ChangeTileFrame((6 * CountY + (CountX - 1)), 1);

	//m_BossMapTile->ChangeTileFrame((7 * CountX + 1), 83);
	////m_BossMapTile->ChangeTileFrame((7 * CountY + (CountX - 1)), 83);

	//for (int i = 8; i <= 18; ++i)
	//{
	//	for (int j = 1; j < 2; ++j)
	//	{
	//		m_BossMapTile->ChangeTileFrame((i * CountX + j), 73);

	//		//m_BossMapTile->ChangeTileFrame((i * CountY + (CountX - j)), 73);
	//	}
	//}

	//m_BossMapTile->ChangeTileFrame((19 * CountX + 1), 95);
	////m_BossMapTile->ChangeTileFrame((19 * CountY + (CountX - 1)), 95);

	//m_BossMapTile->ChangeTileFrame((20 * CountX + 1), 99);
	////m_BossMapTile->ChangeTileFrame((20 * CountY + (CountX - 1)), 99);

	return true;
}

void CBossMap::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBossMap::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBossMap* CBossMap::Clone() const
{
	return new CBossMap(*this);
}

void CBossMap::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CBossMap::Load(FILE* File)
{
	CGameObject::Load(File);

	m_BossMapTile = (CTileMapComponent*)FindComponent("BossMapTile");
	m_BossTrigger = (CColliderBox2D*)FindComponent("BossTrigger");
}

void CBossMap::TriggerCollision(const CollisionResult& Result)
{
	m_BossTrigger->SetEnable(false);

	// Belial을 소환하고 입장 연출 재생, 재생이 끝나면 Belial->BossStart();
	CBelial* Belial = m_Scene->CreateObject<CBelial>("Belial");
	Belial->SetBossStart();
}
