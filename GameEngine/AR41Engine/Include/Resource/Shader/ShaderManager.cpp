#include "ShaderManager.h"

// Shader
#include "SpriteColorShader.h"
#include "SpriteShader.h"
#include "SpriteScrollShader.h"
#include "ColliderShader.h"
#include "ColliderImageShader.h"
#include "ColliderLIne2DShader.h"
#include "UIShader.h"
#include "UIProgressBarShader.h"
#include "TileMapShader.h"
#include "TileMapBackShader.h"
#include "TileMapGridShader.h"
#include "MouseShader.h"

// ConstantBuffer
#include "ConstantBuffer.h"
#include "ColliderConstantBuffer.h"
#include "ColliderLine2DConstantBuffer.h"
//#include "TileMapConstantBuffer.h"
//#include "MouseConstantBuffer.h"

CShaderManager::CShaderManager()
{
}

CShaderManager::~CShaderManager()
{
	SAFE_DELETE(m_ColliderLine2DCBuffer);
	SAFE_DELETE(m_ColliderCBuffer);
}

bool CShaderManager::Init()
{
	// SpriteColorShader�� ����
	CreateShader<CSpriteColorShader>("SpriteColorShader", true);

	// SpriteShader�� ����(�̹��� ��¿�)
	CreateShader<CSpriteShader>("SpriteShader", true);

	// SpriteScrollShader�� ����(�̹��� ��ũ�� ��¿�)
	CreateShader<CSpriteScrollShader>("SpriteScrollShader", true);

	// ColliderShader�� ����(�浹ü ��¿�)
	CreateShader<CColliderShader>("ColliderShader", true);

	// ColliderImageShader�� ����(Pixel �浹ü ��¿�)
	CreateShader<CColliderImageShader>("ColliderImageShader", true);

	// ColliderLIne2DShader�� ����(�� �浹ü ��¿�)
	CreateShader<CColliderLIne2DShader>("ColliderLine2DShader", true);

	// UIShader�� ����(UI ��¿�)
	CreateShader<CUIShader>("UIShader", true);

	// UIProgressBarShader�� ����(UI ��¿�)
	CreateShader<CUIProgressBarShader>("UIProgressBarShader", true);

	// TileMapShader�� ����(TileMap ��¿�)
	CreateShader<CTileMapShader>("TileMapShader", true);

	// TileMapBackShader�� ����(TileMapBack ��¿�)
	CreateShader<CTileMapBackShader>("TileMapBackShader", true);

	// TileMapGridShader�� ����(TileMapGrid ��¿�)
	CreateShader<CTileMapGridShader>("TileMapGridShader", true);

	// MouseShader�� ����
	CreateShader<CMouseShader>("MouseShader", true);


	// Transform ���� ��� ���۸� ����
	CreateConstantBuffer("Transform", sizeof(TransformCBuffer), 0);

	// Material ���� ��� ���� ����
	CreateConstantBuffer("Material", sizeof(MaterialCBuffer), 1);

	// Animation2D ���� ��� ���� ����
	CreateConstantBuffer("Animation2D", sizeof(Animation2DCBuffer), 2);

	// Collider ���� ��� ���� ����
	CreateConstantBuffer("Collider", sizeof(ColliderCBuffer), 10);

	// ColliderLine2D ���� ��� ���� ����
	CreateConstantBuffer("ColliderLine2D", sizeof(ColliderLine2DCBuffer), 11);

	// UI ���� ��� ���� ����
	CreateConstantBuffer("UI", sizeof(UICBuffer), 10);

	// UIProgressBar ���� ��� ���� ����
	CreateConstantBuffer("UIProgressBar", sizeof(UIProgressBarCBuffer), 11);

	// TileMap ���� ��� ���� ����
	CreateConstantBuffer("TileMap", sizeof(TileMapCBuffer), 10);

	// Mouse ���� ��� ���� ����
	CreateConstantBuffer("Mouse", sizeof(MouseCBuffer), 3);



	// Collider ���� ��� ���۴� �ش� ��������� ����� ���� �ϳ��� ����������
	m_ColliderCBuffer = new CColliderConstantBuffer;

	m_ColliderCBuffer->Init();

	m_ColliderLine2DCBuffer = new CColliderLine2DConstantBuffer;

	m_ColliderLine2DCBuffer->Init();

	return true;
}

CShader* CShaderManager::FindShader(const std::string& Name)
{
	auto	iter = m_mapShader.find(Name);

	if (iter == m_mapShader.end())
		return nullptr;

	return iter->second;
}

void CShaderManager::ReleaseShader(const std::string& Name)
{
	auto	iter = m_mapShader.find(Name);

	if (iter != m_mapShader.end())
	{
		if (iter->second->GetRefCount() == 1)
			m_mapShader.erase(iter);
	}
}

bool CShaderManager::CreateConstantBuffer(const std::string& Name, int Size, int Register, int ShaderBufferType)
{
	CConstantBuffer* Buffer = FindConstantBuffer(Name);

	if (Buffer)
		return true;

	Buffer = new CConstantBuffer;

	Buffer->SetName(Name);

	if (!Buffer->Init(Size, Register, ShaderBufferType))
	{
		SAFE_RELEASE(Buffer);
		return false;
	}

	m_mapCBuffer.insert(std::make_pair(Name, Buffer));

	return true;
}

CConstantBuffer* CShaderManager::FindConstantBuffer(const std::string& Name)
{
	auto	iter = m_mapCBuffer.find(Name);

	if (iter == m_mapCBuffer.end())
		return nullptr;

	return iter->second;
}
