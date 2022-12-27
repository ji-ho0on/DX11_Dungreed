#include "TownBack.h"
#include "Component/SpriteComponent.h"
#include "Component/TileMapComponent.h"

CTownBack::CTownBack()
{
	SetTypeID<CTownBack>();

	m_ObjectTypeName = "TownBack";
}

CTownBack::CTownBack(const CTownBack& Obj) :
	CGameObject(Obj)
{
}

CTownBack::~CTownBack()
{
}

void CTownBack::Start()
{
	CGameObject::Start();
}

bool CTownBack::Init()
{
	CGameObject::Init();

	//m_TownCloud = CreateComponent<CSpriteComponent>("TownCloud");
	//m_TownCloud->SetRenderLayerName("Back");
	//m_TownCloud->SetTexture("Town_BGL", TEXT("Map/Town_BGL.png"));
	//m_TownCloud->SetWorldScale(1364.f, 759.f);

	//m_TownForest1 = CreateComponent<CSpriteComponent>("TownForest1");
	//m_TownForest1->SetRenderLayerName("Back1");
	//m_TownForest1->SetTexture("TownBG_Day", TEXT("Map/TownBG_Day.png"));
	//m_TownForest1->SetWorldScale(1364.f, 605.f);

	//m_TownForest2 = CreateComponent<CSpriteComponent>("TownForest2");
	//m_TownForest2->SetRenderLayerName("Back2");
	//m_TownForest2->SetTexture("TownBG_Day", TEXT("Map/TownLayer_Day.png"));
	//m_TownForest2->SetWorldScale(1122.f, 333.f);

	m_TownTileMap = CreateComponent<CTileMapComponent>("TownTileMap");
	m_TownTileMap->SetRenderLayerName("Back3");
	m_TownTileMap->SetTileTexture(10, 10, Vector2(64.f, 64.f), "townAtlas1", TEXT("Map/townAtlas1.png"));
	//m_TownTileMap->SetWorldPositionY(-128.f);

	m_TownTileMap->CreateTile(ETileShape::Rect, 119, 21, Vector2(64.f, 64.f));
	int CountX = m_TownTileMap->GetCountX();
	int CountY = m_TownTileMap->GetCountY();

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < CountX; ++j)
		{
			m_TownTileMap->ChangeTileOption((i * CountX + j), ETileOption::Wall);
		}
	}

	for (int i = 2; i < CountY; ++i)
	{
		for (int j = 0; j < CountX; ++j)
		{
			m_TownTileMap->ChangeTileFrame((i * CountX + j), 10);
		}
	}

	for (int i = 0; i < CountX; ++i)
	{
		m_TownTileMap->ChangeTileFrame(i, 95);
	}

	m_TownTileMap->ChangeTileFrame(CountX + 0, 82);
	m_TownTileMap->ChangeTileFrame(CountX + 1, 82);
	m_TownTileMap->ChangeTileFrame(CountX + 2, 84);

	for (int i = 1; i <= 32; ++i)
	{
		m_TownTileMap->ChangeTileFrame(CountX + 2 + i, 85);
	}

	m_TownTileMap->ChangeTileFrame(CountX + 24, 84);

	m_TownTileMap->ChangeTileFrame(CountX + 35, 87);
	m_TownTileMap->ChangeTileFrame(CountX + 36, 82);
	m_TownTileMap->ChangeTileFrame(CountX + 37, 82);
	m_TownTileMap->ChangeTileFrame(CountX + 38, 82);
	m_TownTileMap->ChangeTileFrame(CountX + 39, 82);
	m_TownTileMap->ChangeTileFrame(CountX + 40, 82);
	m_TownTileMap->ChangeTileFrame(CountX + 41, 82);

	m_TownTileMap->ChangeTileFrame(CountX + 42, 88);

	m_TownTileMap->ChangeTileFrame(CountX + 43, 64);

	m_TownTileMap->ChangeTileFrame(CountX + 44, 62);
	m_TownTileMap->ChangeTileFrame(CountX + 45, 62);

	m_TownTileMap->ChangeTileFrame(CountX + 46, 64);

	m_TownTileMap->ChangeTileFrame(CountX + 47, 62);
	m_TownTileMap->ChangeTileFrame(CountX + 48, 62);
	m_TownTileMap->ChangeTileFrame(CountX + 49, 62);

	for (int i = 1; i <= 18; ++i)
	{
		m_TownTileMap->ChangeTileFrame(CountX + 49 + i, 64);
	}

	m_TownTileMap->ChangeTileFrame(CountX + 68, 62);

	m_TownTileMap->ChangeTileFrame(CountX + 69, 64);

	m_TownTileMap->ChangeTileFrame(CountX + 70, 62);
	m_TownTileMap->ChangeTileFrame(CountX + 71, 62);
	m_TownTileMap->ChangeTileFrame(CountX + 72, 62);

	m_TownTileMap->ChangeTileFrame(CountX + 73, 64);
	m_TownTileMap->ChangeTileFrame(CountX + 74, 64);

	m_TownTileMap->ChangeTileFrame(CountX + 75, 62);

	m_TownTileMap->ChangeTileFrame(CountX + 76, 81);

	for (int i = 1; i <= 8; ++i)
	{
		m_TownTileMap->ChangeTileFrame(CountX + 76 + i, 82);
	}

	m_TownTileMap->ChangeTileFrame(CountX + 85, 84);

	for (int i = 1; i <= 26; ++i)
	{
		m_TownTileMap->ChangeTileFrame(CountX + 85 + i, 85);
	}

	m_TownTileMap->ChangeTileFrame(CountX + 112, 87);

	m_TownTileMap->ChangeTileFrame(CountX + 113, 82);

	m_TownTileMap->ChangeTileFrame(CountX + 114, 83);
	m_TownTileMap->ChangeTileFrame(CountX + 115, 83);
	m_TownTileMap->ChangeTileFrame(CountX + 116, 83);

	m_TownTileMap->ChangeTileFrame(CountX + 117, 82);

	m_TownTileMap->ChangeTileFrame(CountX + 118, 83);


	// TownFloor
	m_TownFloor = CreateComponent<CSpriteComponent>("TownFloor");
	m_TownFloor->SetRenderLayerName("Back");
	m_TownFloor->SetTexture("TownFloor", TEXT("Map/TownFloor.png"));
	m_TownFloor->SetWorldScale(8000.f, 1068.f);
	m_TownFloor->SetRelativePosition(-72.f, 128.f);
	m_TownFloor->Set2DZOffset(500.f);

	// TrainingSchool
	m_TrainingSchool = CreateComponent<CSpriteComponent>("TrainingSchool");
	m_TrainingSchool->SetRenderLayerName("Back1");
	m_TrainingSchool->SetTexture("TrainingSchool", TEXT("Villiage/TrainingSchool.png"));
	m_TrainingSchool->SetWorldScale(1024.f, 288.f);
	m_TrainingSchool->SetRelativePosition(96.f, 128.f);
	m_TrainingSchool->Set2DZOffset(200.f);

	// StreetLight0_1
	m_StreetLight0_1 = CreateComponent<CSpriteComponent>("m_StreetLight0_1");
	m_StreetLight0_1->SetRenderLayerName("Back2");
	m_StreetLight0_1->SetTexture("StreetLight0", TEXT("Villiage/StreetLight_0.png"));
	m_StreetLight0_1->SetWorldScale(128.f, 192.f);
	m_StreetLight0_1->SetRelativePosition(0.f, 128.f);
	m_StreetLight0_1->Set2DZOffset(200.f);

	// Target
	m_Target = CreateComponent<CSpriteComponent>("Target");
	m_Target->SetRenderLayerName("Back2");
	m_Target->SetTexture("Target", TEXT("Villiage/Target.png"));
	m_Target->SetWorldScale(256.f, 96.f);
	m_Target->SetRelativePosition(1024.f, 128.f);
	m_Target->Set2DZOffset(100.f);

	// Tree1_1
	m_Tree1_1 = CreateComponent<CSpriteComponent>("Tree1_1");
	m_Tree1_1->SetRenderLayerName("Back2");
	m_Tree1_1->SetTexture("Tree1", TEXT("Villiage/Tree1.png"));
	m_Tree1_1->SetWorldScale(256.f, 270.f);
	m_Tree1_1->SetRelativePosition(-20.f, 640.f);
	m_Tree1_1->Set2DZOffset(100.f);

	// Wagon
	m_Wagon = CreateComponent<CSpriteComponent>("Wagon");
	m_Wagon->SetRenderLayerName("Front");
	m_Wagon->SetTexture("Wagon", TEXT("Villiage/Wagon.png"));
	m_Wagon->SetWorldScale(256.f, 96.f);
	m_Wagon->SetRelativePosition(40.f, 640.f);
	m_Wagon->Set2DZOffset(100.f);

	// Boutique
	m_Boutique = CreateComponent<CSpriteComponent>("Boutique");
	m_Boutique->SetRenderLayerName("Back1");
	m_Boutique->SetTexture("Boutique", TEXT("Villiage/Boutique.png"));
	m_Boutique->SetWorldScale(950.f, 550.f);
	m_Boutique->SetRelativePosition(390.f, 640.f);
	m_Boutique->Set2DZOffset(100.f);


	// Grass2_1
	m_Grass2_1 = CreateComponent<CSpriteComponent>("m_Grass2_1");
	m_Grass2_1->SetRenderLayerName("Back2");
	m_Grass2_1->SetTexture("Grass2", TEXT("Villiage/Grass2.png"));
	m_Grass2_1->SetWorldScale(384.f, 96.f);
	m_Grass2_1->SetRelativePosition(1180.f, 640.f);
	m_Grass2_1->Set2DZOffset(100.f);


	// StreetLight0_2
	m_StreetLight0_2 = CreateComponent<CSpriteComponent>("m_StreetLight0_2");
	m_StreetLight0_2->SetRenderLayerName("Back2");
	m_StreetLight0_2->SetTexture("StreetLight0", TEXT("Villiage/StreetLight_0.png"));
	m_StreetLight0_2->SetWorldScale(128.f, 192.f);
	m_StreetLight0_2->SetRelativePosition(1760.f, 128.f);
	m_StreetLight0_2->Set2DZOffset(100.f);


	// Grass1_1
	m_Grass1_1 = CreateComponent<CSpriteComponent>("m_Grass1_1");
	m_Grass1_1->SetRenderLayerName("Back2");
	m_Grass1_1->SetTexture("Grass1", TEXT("Villiage/Grass1.png"));
	m_Grass1_1->SetWorldScale(160.f, 30.f);
	m_Grass1_1->SetRelativePosition(1740.f, 128.f);
	m_Grass1_1->Set2DZOffset(100.f);

	// Tree1_2
	m_Tree1_2 = CreateComponent<CSpriteComponent>("Tree1_2");
	m_Tree1_2->SetRenderLayerName("Back");
	m_Tree1_2->SetTexture("Tree1", TEXT("Villiage/Tree1.png"));
	m_Tree1_2->SetWorldScale(256.f, 270.f);
	m_Tree1_2->SetRelativePosition(2015.f, 128.f);
	m_Tree1_2->Set2DZOffset(300.f);



	m_TownTileMap->AddChild(m_TownFloor);
	m_TownTileMap->AddChild(m_TrainingSchool);
	m_TownTileMap->AddChild(m_StreetLight0_1);
	m_TownTileMap->AddChild(m_Target);
	m_TownTileMap->AddChild(m_Tree1_1);
	m_TownTileMap->AddChild(m_Wagon);
	m_TownTileMap->AddChild(m_Boutique);
	m_TownTileMap->AddChild(m_Grass2_1);
	m_TownTileMap->AddChild(m_StreetLight0_2);
	m_TownTileMap->AddChild(m_Grass1_1);
	m_TownTileMap->AddChild(m_Tree1_2);

	return true;
}

void CTownBack::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTownBack::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTownBack* CTownBack::Clone() const
{
	return new CTownBack(*this);
}

void CTownBack::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CTownBack::Load(FILE* File)
{
	CGameObject::Load(File);
}
