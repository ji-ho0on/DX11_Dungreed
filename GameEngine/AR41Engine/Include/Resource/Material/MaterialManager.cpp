#include "MaterialManager.h"

CMaterialManager::CMaterialManager()
{
}

CMaterialManager::~CMaterialManager()
{
}

bool CMaterialManager::Init()
{
	CMaterial* Material = CreateMaterial<CMaterial>("DefaultColor");
	Material->SetShader("SpriteColorShader");


	Material = CreateMaterial<CMaterial>("DefaultTexture");
	Material->SetShader("SpriteShader");
	Material->AddTexture(0, (int)EShaderBufferType::Pixel, "DefaultTexture", TEXT("Example/teemo.png"));


	Material = CreateMaterial<CMaterial>("ScrollTexture");
	Material->SetShader("SpriteScrollShader");
	Material->AddTexture(0, (int)EShaderBufferType::Pixel, "DefaultTexture", TEXT("Example/teemo.png"));


	Material = CreateMaterial<CMaterial>("TileMap");
	Material->SetShader("TileMapShader");
	Material->AddTexture(0, (int)EShaderBufferType::Pixel, "DefaultTile", TEXT("Example/Floors.png"));
	Material->SetRenderState("DepthLessEqual");
	Material->SetRenderState("AlphaBlend");

	// TileMapBack�� Material, ���� Texture�� �����Ǿ����� �ʱ� ������ Texture�� �����Ͽ� ����ؾ���.
	Material = CreateMaterial<CMaterial>("DefaultTileMapBack");
	Material->SetShader("TileMapBackShader");
	Material->SetRenderState("DepthLessEqual");

	// ���콺 ��¿� Material
	Material = CreateMaterial<CMaterial>("MouseMaterial");
	Material->SetShader("MouseShader");
	Material->SetRenderState("AlphaBlend");
	Material->AddTexture(0, (int)EShaderBufferType::Pixel, "DefaultMouse", TEXT("common/cursor/BasicCursor.png"));

	return true;
}

CMaterial* CMaterialManager::FindMaterial(const std::string& Name)
{
	auto	iter = m_mapMaterial.find(Name);

	if (iter == m_mapMaterial.end())
		return nullptr;

	return iter->second;
}

void CMaterialManager::ReleaseMaterial(const std::string& Name)
{
	auto	iter = m_mapMaterial.find(Name);

	if (iter != m_mapMaterial.end())
	{
		if (iter->second->GetRefCount() == 1)
			m_mapMaterial.erase(iter);
	}
}
