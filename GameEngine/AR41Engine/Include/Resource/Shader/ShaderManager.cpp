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
	// SpriteColorShader를 생성
	CreateShader<CSpriteColorShader>("SpriteColorShader", true);

	// SpriteShader를 생성(이미지 출력용)
	CreateShader<CSpriteShader>("SpriteShader", true);

	// SpriteScrollShader를 생성(이미지 스크롤 출력용)
	CreateShader<CSpriteScrollShader>("SpriteScrollShader", true);

	// ColliderShader를 생성(충돌체 출력용)
	CreateShader<CColliderShader>("ColliderShader", true);

	// ColliderImageShader를 생성(Pixel 충돌체 출력용)
	CreateShader<CColliderImageShader>("ColliderImageShader", true);

	// ColliderLIne2DShader를 생성(선 충돌체 출력용)
	CreateShader<CColliderLIne2DShader>("ColliderLine2DShader", true);

	// UIShader를 생성(UI 출력용)
	CreateShader<CUIShader>("UIShader", true);

	// UIProgressBarShader를 생성(UI 출력용)
	CreateShader<CUIProgressBarShader>("UIProgressBarShader", true);

	// TileMapShader를 생성(TileMap 출력용)
	CreateShader<CTileMapShader>("TileMapShader", true);

	// TileMapBackShader를 생성(TileMapBack 출력용)
	CreateShader<CTileMapBackShader>("TileMapBackShader", true);

	// TileMapGridShader를 생성(TileMapGrid 출력용)
	CreateShader<CTileMapGridShader>("TileMapGridShader", true);

	// MouseShader를 생성
	CreateShader<CMouseShader>("MouseShader", true);


	// Transform 전용 상수 버퍼를 생성
	CreateConstantBuffer("Transform", sizeof(TransformCBuffer), 0);

	// Material 전용 상수 버퍼 생성
	CreateConstantBuffer("Material", sizeof(MaterialCBuffer), 1);

	// Animation2D 전용 상수 버퍼 생성
	CreateConstantBuffer("Animation2D", sizeof(Animation2DCBuffer), 2);

	// Collider 전용 상수 버퍼 생성
	CreateConstantBuffer("Collider", sizeof(ColliderCBuffer), 10);

	// ColliderLine2D 전용 상수 버퍼 생성
	CreateConstantBuffer("ColliderLine2D", sizeof(ColliderLine2DCBuffer), 11);

	// UI 전용 상수 버퍼 생성
	CreateConstantBuffer("UI", sizeof(UICBuffer), 10);

	// UIProgressBar 전용 상수 버퍼 생성
	CreateConstantBuffer("UIProgressBar", sizeof(UIProgressBarCBuffer), 11);

	// TileMap 전용 상수 버퍼 생성
	CreateConstantBuffer("TileMap", sizeof(TileMapCBuffer), 10);

	// Mouse 전용 상수 버퍼 생성
	CreateConstantBuffer("Mouse", sizeof(MouseCBuffer), 3);



	// Collider 전용 상수 버퍼는 해당 멤버변수를 만들어 놓고 하나로 돌려쓸것임
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
