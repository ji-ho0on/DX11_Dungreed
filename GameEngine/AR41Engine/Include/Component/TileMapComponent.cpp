#include "TileMapComponent.h"
#include "../Resource/Material/Material.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Mesh/Mesh.h"
#include "../Resource/Shader/Animation2DConstantBuffer.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Resource/Shader/TileMapConstantBuffer.h"
#include "../Device.h"
#include "../Resource/Shader/StructuredBuffer.h"
#include "CameraComponent.h"
#include "../Scene/CameraManager.h"
#include "../Engine.h"
#include "../Thread/ThreadManager.h"

CTileMapComponent::CTileMapComponent() :
	m_CountX(0),
	m_CountY(0),
	m_Count(0),
	m_RenderCount(0),
	m_TileMapCBuffer(nullptr),
	m_TileInfoBuffer(nullptr),
	m_TileInfoCount(0)
{
	SetTypeID<CTileMapComponent>();

	m_ComponentTypeName = "TileMapComponent";

	m_TileTypeColor[(int)ETileOption::None] = Vector4::White;
	m_TileTypeColor[(int)ETileOption::Wall] = Vector4::Red;
	m_TileTypeColor[(int)ETileOption::SideWall] = Vector4::Blue;
	m_TileTypeColor[(int)ETileOption::OneWay] = Vector4::Yellow;
}

CTileMapComponent::CTileMapComponent(const CTileMapComponent& component) :
	CPrimitiveComponent(component)
{
	/*
    CSharedPtr<class CTexture>          m_TileBackTexture;
    std::vector<Animation2DFrameData>   m_vecTileFrame;
	*/

	m_TileMesh = component.m_TileMesh;

	if (component.m_TileMaterial)
		m_TileMaterial = component.m_TileMaterial->Clone();

	if (component.m_TileMapCBuffer)
		m_TileMapCBuffer = component.m_TileMapCBuffer->Clone();

	if (component.m_TileInfoBuffer)
		m_TileInfoBuffer = component.m_TileInfoBuffer->Clone();


	m_Shape = component.m_Shape;
	m_CountX = component.m_CountX;
	m_CountY = component.m_CountY;
	m_Count = component.m_Count;
	m_TileInfoCount = component.m_TileInfoCount;
	m_RenderCount = component.m_RenderCount;
	m_TileSize = component.m_TileSize;

	for (int i = 0; i < (int)ETileOption::End; ++i)
	{
		m_TileTypeColor[i] = component.m_TileTypeColor[i];
	}

	m_vecTileFrame.clear();

	size_t	Size = component.m_vecTileFrame.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecTileFrame.push_back(component.m_vecTileFrame[i]);
	}

	m_vecTile.clear();

	Size = component.m_vecTile.size();

	for (size_t i = 0; i < Size; ++i)
	{
		CTile* Tile = component.m_vecTile[i]->Clone();

		Tile->m_Owner = this;

		m_vecTile.push_back(Tile);
	}

	m_vecTileInfo.resize(m_vecTile.size());
}

CTileMapComponent::~CTileMapComponent()
{
	//CThreadManager::GetInst()->DeleteNavigationThread(this);

	SAFE_DELETE(m_TileMapCBuffer);
	SAFE_DELETE(m_TileInfoBuffer);

	auto	iter = m_vecTile.begin();
	auto	iterEnd = m_vecTile.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	m_vecTile.clear();
}

CTexture* CTileMapComponent::GetTileTexture() const
{
	return m_TileMaterial->GetTexture();
}

void CTileMapComponent::SetTileBackTexture(CTexture* Texture)
{
	m_TileBackTexture = Texture;

	if (m_TileBackTexture)
	{
		if (m_TileBackTexture->GetImageType() != EImageType::Array)
		{
			m_vecMaterial[0]->SetTexture(0, 0, (int)EShaderBufferType::Pixel, Texture->GetName(), Texture);
		}

		else
		{
			m_vecMaterial[0]->SetTexture(10, 0, (int)EShaderBufferType::Pixel, Texture->GetName(), Texture);
		}
	}
}

void CTileMapComponent::SetTileBackTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	CTexture* Texture = nullptr;

	if (m_Scene)
	{
		if (!m_Scene->GetResource()->LoadTexture(Name, FileName, PathName))
			return;

		Texture = m_Scene->GetResource()->FindTexture(Name);
	}

	else
	{
		if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
			return;

		Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	m_TileBackTexture = Texture;

	if (m_TileBackTexture)
	{
		m_vecMaterial[0]->SetTexture(0, 0, (int)EShaderBufferType::Pixel, Texture->GetName(), Texture);
	}
}

void CTileMapComponent::SetTileBackTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	CTexture* Texture = nullptr;

	if (m_Scene)
	{
		if (!m_Scene->GetResource()->LoadTextureFullPath(Name, FullPath))
			return;

		Texture = m_Scene->GetResource()->FindTexture(Name);
	}

	else
	{
		if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath))
			return;

		Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	m_TileBackTexture = Texture;

	if (m_TileBackTexture)
	{
		m_vecMaterial[0]->SetTexture(0, 0, (int)EShaderBufferType::Pixel, Texture->GetName(), Texture);
	}
}

void CTileMapComponent::SetTileBackTextureArray(const std::string& Name, const std::vector<const TCHAR*>& vecFileName, const std::string& PathName)
{
	CTexture* Texture = nullptr;

	if (m_Scene)
	{
		if (!m_Scene->GetResource()->LoadTextureArray(Name, vecFileName, PathName))
			return;

		Texture = m_Scene->GetResource()->FindTexture(Name);
	}

	else
	{
		if (!CResourceManager::GetInst()->LoadTextureArray(Name, vecFileName, PathName))
			return;

		Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	m_TileBackTexture = Texture;

	if (m_TileBackTexture)
	{
		m_vecMaterial[0]->SetTexture(0, 10, (int)EShaderBufferType::Pixel, Texture->GetName(), Texture);
	}
}

void CTileMapComponent::SetTileBackTextureArrayFullPath(const std::string& Name, const std::vector<const TCHAR*>& vecFullPath)
{
	CTexture* Texture = nullptr;

	if (m_Scene)
	{
		if (!m_Scene->GetResource()->LoadTextureArrayFullPath(Name, vecFullPath))
			return;

		Texture = m_Scene->GetResource()->FindTexture(Name);
	}

	else
	{
		if (!CResourceManager::GetInst()->LoadTextureArrayFullPath(Name, vecFullPath))
			return;

		Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	m_TileBackTexture = Texture;

	if (m_TileBackTexture)
	{
		m_vecMaterial[0]->SetTexture(0, 10, (int)EShaderBufferType::Pixel, Texture->GetName(), Texture);
	}
}

void CTileMapComponent::SetTileMesh(const std::string& Name)
{
	if (m_Scene)
		m_TileMesh = m_Scene->GetResource()->FindMesh(Name);

	else
		m_TileMesh = CResourceManager::GetInst()->FindMesh(Name);

	if (m_TileMesh)
		SetMeshSize(m_TileMesh->GetMeshSize());
}

void CTileMapComponent::SetTileMesh(CMesh* Mesh)
{
	m_TileMesh = Mesh;

	if (m_TileMesh)
		SetMeshSize(m_TileMesh->GetMeshSize());
}

void CTileMapComponent::SetTileMaterial(const std::string& Name)
{
	if (m_Scene)
		m_TileMaterial = m_Scene->GetResource()->FindMaterial(Name);

	else
		m_TileMaterial = CResourceManager::GetInst()->FindMaterial(Name);

	if (m_TileMaterial)
	{
		m_TileMapCBuffer->SetImageSize(Vector2((float)m_TileMaterial->GetTexture()->GetWidth(), (float)m_TileMaterial->GetTexture()->GetHeight()));

		// Atlas 일 경우
		if (m_TileMaterial->GetTexture()->GetImageCount() == 1)
		{
			//m_TileMapCBuffer->SetStart();
			//m_TileMapCBuffer->SetEnd();
		}

		// Array일 경우, TileTexture에 Frame은 안씀
		else
		{
			m_TileMapCBuffer->SetStart(Vector2(0.f, 0.f));
			m_TileMapCBuffer->SetEnd(Vector2((float)m_TileMaterial->GetTexture()->GetWidth(), (float)m_TileMaterial->GetTexture()->GetHeight()));
		}
	}
}

void CTileMapComponent::SetTileMaterial(CMaterial* Material)
{
	m_TileMaterial = Material;

	if (m_TileMaterial)
	{
		m_TileMapCBuffer->SetImageSize(Vector2((float)m_TileMaterial->GetTexture()->GetWidth(), (float)m_TileMaterial->GetTexture()->GetHeight()));

		// Atlas 일 경우
		if (m_TileMaterial->GetTexture()->GetImageCount() == 1)
		{
			//m_TileMapCBuffer->SetStart();
			//m_TileMapCBuffer->SetEnd();
		}

		// Array일 경우, TileTexture에 Frame은 안씀
		else
		{
			m_TileMapCBuffer->SetStart(Vector2(0.f, 0.f));
			m_TileMapCBuffer->SetEnd(Vector2((float)m_TileMaterial->GetTexture()->GetWidth(), (float)m_TileMaterial->GetTexture()->GetHeight()));
		}
	}
}

void CTileMapComponent::SetTileTexture(CTexture* Texture)
{
	m_TileMaterial->SetTexture(0, 0, (int)EShaderBufferType::Pixel,	Texture->GetName(), Texture);

	m_TileMapCBuffer->SetImageSize(Vector2((float)m_TileMaterial->GetTexture()->GetWidth(), (float)m_TileMaterial->GetTexture()->GetHeight()));

	// Atlas 일 경우
	if (m_TileMaterial->GetTexture()->GetImageCount() == 1)
	{
		//m_TileMapCBuffer->SetStart();
		//m_TileMapCBuffer->SetEnd();
	}

	// Array일 경우, TileTexture에 Frame은 안씀
	else
	{
		m_TileMapCBuffer->SetStart(Vector2(0.f, 0.f));
		m_TileMapCBuffer->SetEnd(Vector2((float)m_TileMaterial->GetTexture()->GetWidth(), (float)m_TileMaterial->GetTexture()->GetHeight()));
	}
}

void CTileMapComponent::SetTileTexture(int CountX, int CountY, const Vector2& TileSize, const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	m_TileMaterial->SetTexture(0, 0, (int)EShaderBufferType::Pixel,	Name, FileName, PathName);

	m_TileMapCBuffer->SetImageSize(Vector2((float)m_TileMaterial->GetTexture()->GetWidth(), (float)m_TileMaterial->GetTexture()->GetHeight()));

	for (int i = 0; i < CountY; ++i)
	{
		for (int j = 0; j < CountX; ++j)
		{
			Animation2DFrameData Data = {};
			Data.Start = Vector2(TileSize.x * j, TileSize.y * i);
			Data.End = Vector2(TileSize.x * (j + 1), TileSize.y * (i + 1));

			m_vecTileFrame.push_back(Data);
		}
	}
}

void CTileMapComponent::SetTileTextureFullPath(int CountX, int CountY, const Vector2& TileSize, const std::string& Name, const TCHAR* FullPath)
{
	m_TileMaterial->SetTextureFullPath(0, 0, (int)EShaderBufferType::Pixel,	Name, FullPath);

	m_TileMapCBuffer->SetImageSize(Vector2((float)m_TileMaterial->GetTexture()->GetWidth(), (float)m_TileMaterial->GetTexture()->GetHeight()));

	for (int i = 0; i < CountY; ++i)
	{
		for (int j = 0; j < CountX; ++j)
		{
			Animation2DFrameData Data = {};
			Data.Start = Vector2(TileSize.x * j, TileSize.y * i);
			Data.End = Vector2(TileSize.x * (j + 1), TileSize.y * (i + 1));

			m_vecTileFrame.push_back(Data);
		}
	}
}

void CTileMapComponent::SetTileTextureArray(const std::string& Name, const std::vector<const TCHAR*>& vecFileName,
	const std::string& PathName)
{
	m_TileMaterial->SetTextureArray(0, 10, (int)EShaderBufferType::Pixel, Name, vecFileName, PathName);

	m_TileMapCBuffer->SetImageSize(Vector2((float)m_TileMaterial->GetTexture()->GetWidth(), (float)m_TileMaterial->GetTexture()->GetHeight()));

	m_TileMapCBuffer->SetStart(Vector2(0.f, 0.f));
	m_TileMapCBuffer->SetEnd(Vector2((float)m_TileMaterial->GetTexture()->GetWidth(), (float)m_TileMaterial->GetTexture()->GetHeight()));

	CTexture* Texture = m_TileMaterial->GetTexture();

	int Count = Texture->GetImageCount();

	for (int i = 0; i < Count; ++i)
	{
		Animation2DFrameData Data = {};
		Data.Start = Vector2(0.f, 0.f);
		Data.End = Vector2((float)Texture->GetWidth(), (float)Texture->GetHeight());

		m_vecTileFrame.push_back(Data);
	}
}

void CTileMapComponent::SetTileTextureArrayFullPath(const std::string& Name, const std::vector<const TCHAR*>& vecFullPath)
{
	m_TileMaterial->SetTextureArrayFullPath(0, 10, (int)EShaderBufferType::Pixel, Name, vecFullPath);

	m_TileMapCBuffer->SetImageSize(Vector2((float)m_TileMaterial->GetTexture()->GetWidth(), (float)m_TileMaterial->GetTexture()->GetHeight()));

	m_TileMapCBuffer->SetStart(Vector2(0.f, 0.f));
	m_TileMapCBuffer->SetEnd(Vector2((float)m_TileMaterial->GetTexture()->GetWidth(), (float)m_TileMaterial->GetTexture()->GetHeight()));

	CTexture* Texture = m_TileMaterial->GetTexture();

	int Count = Texture->GetImageCount();

	for (int i = 0; i < Count; ++i)
	{
		Animation2DFrameData Data = {};
		Data.Start = Vector2(0.f, 0.f);
		Data.End = Vector2((float)Texture->GetWidth(), (float)Texture->GetHeight());

		m_vecTileFrame.push_back(Data);
	}
}

void CTileMapComponent::SetTileBaseColor(const Vector4& Color)
{
	m_TileMaterial->SetBaseColor(Color);
}

void CTileMapComponent::SetEditorMouseOnTile(int Index)
{
	if (Index < 0 || Index >= m_Count)
		m_EditorMouseOnTile = nullptr;

	else
		m_EditorMouseOnTile = m_vecTile[Index];
}

void CTileMapComponent::CreateTile(ETileShape Shape, int CountX, int CountY, const Vector2& TileSize)
{
	m_Shape = Shape;

	m_CountX = CountX;
	m_CountY = CountY;
	m_Count = m_CountX * m_CountY;

	m_TileSize = TileSize;

	auto	iter = m_vecTile.begin();
	auto	iterEnd = m_vecTile.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	m_vecTile.clear();

	m_vecTile.resize((size_t)(m_CountX * m_CountY));

	for (int i = 0; i < m_CountY; ++i)
	{
		for (int j = 0; j < m_CountX; ++j)
		{
			CTile* Tile = new CTile;

			Tile->m_Owner = this;

			int	Index = i * m_CountX + j;

			Tile->m_IndexX = j;
			Tile->m_IndexY = i;
			Tile->m_Index = Index;

			Tile->m_Size.x = m_TileSize.x;
			Tile->m_Size.y = m_TileSize.y;

			// 여기 바꿔야함.
			Tile->m_TileStart = m_vecTileFrame[0].Start;
			Tile->m_TileEnd = m_vecTileFrame[0].End;

			m_vecTile[Index] = Tile;
		}
	}

	int	RenderCountX = 0, RenderCountY = 0;

	switch (m_Shape)
	{
	case ETileShape::Rect:
		RenderCountX = (int)(CDevice::GetInst()->GetResolution().Width / m_TileSize.x) + 6;
		RenderCountY = (int)(CDevice::GetInst()->GetResolution().Height / m_TileSize.y) + 6;

		for (int i = 0; i < m_CountY; ++i)
		{
			for (int j = 0; j < m_CountX; ++j)
			{
				int	Index = i * m_CountX + j;

				m_vecTile[Index]->m_Pos.x = j * m_TileSize.x;
				m_vecTile[Index]->m_Pos.y = i * m_TileSize.y;
			}
		}
		break;
	case ETileShape::Isometric:
	{
		RenderCountX = (int)(CDevice::GetInst()->GetResolution().Width / m_TileSize.x) + 3;
		RenderCountY = (int)(CDevice::GetInst()->GetResolution().Height / m_TileSize.y) * 2 + 6;

		float	StartX = 0.f;

		for (int i = 0; i < m_CountY; ++i)
		{
			if (i % 2 == 0)
				StartX = 0.f;

			else
				StartX = m_TileSize.x * 0.5f;

			for (int j = 0; j < m_CountX; ++j)
			{
				int	Index = i * m_CountX + j;

				m_vecTile[Index]->m_Pos.x = StartX + j * m_TileSize.x;
				m_vecTile[Index]->m_Pos.y = i * m_TileSize.y * 0.5f;
			}
		}
	}
	break;
	}

	m_TileMapCBuffer->SetTileSize(m_TileSize);

	// 구조화 버퍼를 생성한다. 구조화버퍼에는 출력할 타일정보가 들어가야하기 때문에 출력되는 최대 타일 개수를 이용해서 생성한다.
	SAFE_DELETE(m_TileInfoBuffer);

	m_TileInfoCount = RenderCountX * RenderCountY;

	m_TileInfoBuffer = new CStructuredBuffer;

	m_TileInfoBuffer->Init("TileInfo", sizeof(TileInfo), m_TileInfoCount, 40, true,	(int)EShaderBufferType::Vertex);

	m_vecTileInfo.resize((size_t)m_Count);

	for (int i = 0; i < m_Count; ++i)
	{
		m_vecTileInfo[i].TypeColor = Vector4(1.f, 1.f, 1.f, 1.f);
		m_vecTileInfo[i].Opacity = 1.f;
	}

	//m_SceneName = m_Scene->GetName();

	// 타일이 생성되었기 때문에 해당 타일맵의 길을 찾아줄 내비게이션 스레드를 생성해준다.
	//CThreadManager::GetInst()->CreateNavigationThread(this);
}

void CTileMapComponent::ChangeTileFrame(int Frame)
{
	if (m_EditorMouseOnTile)
	{
		m_EditorMouseOnTile->m_TileStart = m_vecTileFrame[Frame].Start;
		m_EditorMouseOnTile->m_TileEnd = m_vecTileFrame[Frame].End;
		m_EditorMouseOnTile->m_Frame = Frame;
	}
}

void CTileMapComponent::ChangeTileOption(ETileOption Option)
{
	if (m_EditorMouseOnTile)
		m_EditorMouseOnTile->m_TileOption = Option;
}

void CTileMapComponent::ChangeTileFrame(int Index, int Frame)
{
	if (Index < 0 || Index >= m_Count)
		return;

	m_vecTile[Index]->m_TileStart = m_vecTileFrame[Frame].Start;
	m_vecTile[Index]->m_TileEnd = m_vecTileFrame[Frame].End;
	m_vecTile[Index]->m_Frame = Frame;
}

void CTileMapComponent::ChangeTileOption(int Index, ETileOption Option)
{
	if (Index < 0 || Index >= m_Count)
		return;

	m_vecTile[Index]->m_TileOption = Option;
}

int CTileMapComponent::GetTileIndexX(const Vector2& Pos)
{
	if (m_Shape == ETileShape::Rect)
	{
		float ConvertX = Pos.x - GetWorldPos().x;

		if (ConvertX < 0.f)
			return -1;

		int	IndexX = (int)(ConvertX / m_TileSize.x);

		if (IndexX < 0 || IndexX >= m_CountX)
			return -1;

		return IndexX;
	}

	int	IndexY = GetTileIndexY(Pos);

	if (IndexY < 0 || IndexY >= m_CountY)
		return -1;

	int	IndexX = -1;

	float	ConvertX = Pos.x - GetWorldPos().x;

	if (IndexY % 2 == 0)
		IndexX = (int)(ConvertX / m_TileSize.x);

	else
		IndexX = (int)((ConvertX - m_TileSize.x * 0.5f) / m_TileSize.x);

	if (IndexX < 0 || IndexX >= m_CountX)
		return -1;

	return IndexX;
}

int CTileMapComponent::GetTileIndexX(const Vector3& Pos)
{
	return GetTileIndexX(Vector2(Pos.x, Pos.y));
}

int CTileMapComponent::GetTileIndexY(const Vector2& Pos)
{
	if (m_Shape == ETileShape::Rect)
	{
		float ConvertY = Pos.y - GetWorldPos().y;

		if (ConvertY < 0.f)
			return -1;

		int	IndexY = (int)(ConvertY / m_TileSize.y);

		if (IndexY < 0 || IndexY >= m_CountY)
			return -1;

		return IndexY;
	}

	Vector2	TileMapPos(GetWorldPos().x, GetWorldPos().y);

	Vector2	ConvertPos = Pos - TileMapPos;

	float RatioX = ConvertPos.x / m_TileSize.x;
	float RatioY = ConvertPos.y / m_TileSize.y;

	int	IndexX = (int)RatioX;
	int	IndexY = (int)RatioY;

	if (IndexX < 0 || IndexX > m_CountX)
		return -1;

	// 정수 부분을 제거하여 소수점 부분만 남겨준다.
	// 소수점 부분을 이용하여 사각형의 어느 지점에 있는지를 판단하기 위해서이다.
	RatioX -= (int)RatioX;
	RatioY -= (int)RatioY;

	// 사각형의 아래쪽 부분일 경우
	if (RatioY < 0.5f)
	{
		// 좌 하단 사각형의 좌 하단 삼각형일 경우가 된다.
		// RatioX가 0.5보다 크면 오른쪽 하단 사각형이 되는데 이경우 0.5에서 빼면 음수가 나오므로 RatioY는 절대 이 값보다 작아질 수 없다.
		// 이 경우 우측 상단의 삼각형 안에 존재하는 점은 RatioY가 절대 이 값보다 작을 수 없다. 좌측 하단의 삼각형을 구하는 식이다.
		if (RatioY < 0.5f - RatioX)
		{
			// Y인덱스가 0이면 가장 아래쪽 줄이라서 좌 하단 삼각형은 없다.
			if (IndexY == 0)
				return -1;

			else if (IndexX == 0)
				return -1;

			else
				return IndexY * 2 - 1;
		}

		// 오른쪽 사각형 안에서 우 하단 삼각형일 경우
		else if (RatioY < RatioX - 0.5f)
		{
			if (IndexY == 0)
				return -1;

			else
				return IndexY * 2 - 1;
		}

		else
			return IndexY * 2;
	}

	// 사각형의 위쪽 부분일 경우
	else if (RatioY > 0.5f)
	{
		// 좌 상단 사각형의 좌 상단 삼각형일 경우
		if (RatioY - 0.5f > RatioX)
		{
			if (IndexX == 0)
				return -1;

			else if (IndexY * 2 + 1 >= m_CountY)
				return -1;

			else
				return IndexY * 2 + 1;
		}

		// 우 상단 사각형의 우 상단 삼각형일 경우
		else if (RatioY - 0.5f > 1.f - RatioX)
		{
			if (IndexX >= m_CountX)
				return -1;

			else if (IndexY * 2 + 1 >= m_CountY)
				return -1;

			else
				return IndexY * 2 + 1;
		}

		else
			return IndexY * 2;
	}

	// 가운데
	else
		return IndexY * 2;

	return -1;
}

int CTileMapComponent::GetTileIndexY(const Vector3& Pos)
{
	return GetTileIndexY(Vector2(Pos.x, Pos.y));
}

int CTileMapComponent::GetTileIndex(const Vector2& Pos)
{
	int	IndexX = GetTileIndexX(Pos);
	int	IndexY = GetTileIndexY(Pos);

	if (IndexX == -1 || IndexY == -1)
		return -1;

	return IndexY * m_CountX + IndexX;
}

int CTileMapComponent::GetTileIndex(const Vector3& Pos)
{
	return GetTileIndex(Vector2(Pos.x, Pos.y));
}

CTile* CTileMapComponent::GetTile(const Vector2& Pos)
{
	int	Index = GetTileIndex(Pos);

	if (Index == -1)
		return nullptr;

	return m_vecTile[Index];
}

CTile* CTileMapComponent::GetTile(const Vector3& Pos)
{
	int	Index = GetTileIndex(Pos);

	if (Index == -1)
		return nullptr;

	return m_vecTile[Index];
}

CTile* CTileMapComponent::GetTile(int X, int Y)
{
	if (X < 0 || X >= m_CountX || Y < 0 || Y >= m_CountY)
		return nullptr;

	return m_vecTile[Y * m_CountX + X];
}

CTile* CTileMapComponent::GetTile(int Index)
{
	if (Index < 0 || Index >= m_Count)
		return nullptr;

	return m_vecTile[Index];
}

int CTileMapComponent::GetTileRenderIndexX(const Vector3& Pos)
{
	if (m_Shape == ETileShape::Rect)
	{
		float ConvertX = Pos.x - GetWorldPos().x;

		int	IndexX = (int)(ConvertX / m_TileSize.x);

		if (IndexX < 0)
			return 0;

		else if (IndexX >= m_CountX)
			return m_CountX - 1;

		return IndexX;
	}

	int	IndexY = GetTileRenderIndexY(Pos);

	if (IndexY < 0)
		IndexY = 0;

	else if (IndexY >= m_CountY)
		IndexY = m_CountY - 1;

	int	IndexX = -1;

	float	ConvertX = Pos.x - GetWorldPos().x;

	if (IndexY % 2 == 0)
		IndexX = (int)(ConvertX / m_TileSize.x);

	else
		IndexX = (int)((ConvertX - m_TileSize.x * 0.5f) / m_TileSize.x);

	if (IndexX < 0)
		return 0;

	else if (IndexX >= m_CountX)
		return m_CountX - 1;

	return IndexX;
}

int CTileMapComponent::GetTileRenderIndexY(const Vector3& Pos)
{
	if (m_Shape == ETileShape::Rect)
	{
		float ConvertY = Pos.y - GetWorldPos().y;

		int	IndexY = (int)(ConvertY / m_TileSize.y);

		if (IndexY < 0)
			return 0;

		else if (IndexY >= m_CountY)
			return m_CountY - 1;

		return IndexY;
	}

	Vector2	TileMapPos(GetWorldPos().x, GetWorldPos().y);

	Vector2	ConvertPos = Vector2(Pos.x, Pos.y) - TileMapPos;

	float RatioX = ConvertPos.x / m_TileSize.x;
	float RatioY = ConvertPos.y / m_TileSize.y;

	int	IndexX = (int)RatioX;
	int	IndexY = (int)RatioY;

	if (IndexX < 0)
		IndexX = 0;

	else if (IndexX > m_CountX)
		IndexX = m_CountX - 1;

	// 정수 부분을 제거하여 소수점 부분만 남겨준다.
	// 소수점 부분을 이용하여 사각형의 어느 지점에 있는지를 판단하기 위해서이다.
	RatioX -= (int)RatioX;
	RatioY -= (int)RatioY;

	// 사각형의 아래쪽 부분일 경우
	if (RatioY < 0.5f)
	{
		// 좌 하단 사각형의 좌 하단 삼각형일 경우가 된다.
		// RatioX가 0.5보다 크면 오른쪽 하단 사각형이 되는데 이경우 0.5에서 빼면 음수가 나오므로 RatioY는 절대 이 값보다 작아질 수 없다.
		// 이 경우 우측 상단의 삼각형 안에 존재하는 점은 RatioY가 절대 이 값보다 작을 수 없다. 좌측 하단의 삼각형을 구하는 식이다.
		if (RatioY < 0.5f - RatioX)
		{
			// Y인덱스가 0이면 가장 아래쪽 줄이라서 좌 하단 삼각형은 없다.
			if (IndexY == 0)
				return 0;

			else if (IndexX == 0)
			{
				if (IndexY < 0)
					return 0;

				else if (IndexY >= m_CountY)
					return m_CountY - 1;

				else
					return IndexY * 2 + 1;
			}

			else
				return IndexY * 2 - 1;
		}

		// 오른쪽 사각형 안에서 우 하단 삼각형일 경우
		else if (RatioY < RatioX - 0.5f)
		{
			if (IndexY == 0)
				return 0;

			else
				return IndexY * 2 - 1;
		}

		else
			return IndexY * 2;
	}

	// 사각형의 위쪽 부분일 경우
	else if (RatioY > 0.5f)
	{
		// 좌 상단 사각형의 좌 상단 삼각형일 경우
		if (RatioY - 0.5f > RatioX)
		{
			if (IndexX == 0)
			{
				if (IndexY < 0)
					return 0;

				else if (IndexY >= m_CountY)
					return m_CountY - 1;
			}

			if (IndexY * 2 + 1 >= m_CountY)
				return m_CountY - 1;

			else
				return IndexY * 2 + 1;
		}

		// 우 상단 사각형의 우 상단 삼각형일 경우
		else if (RatioY - 0.5f > 1.f - RatioX)
		{
			if (IndexX >= m_CountX)
			{
				if (IndexY < 0)
					return 0;

				else if (IndexY >= m_CountY)
					return m_CountY - 1;
			}

			if (IndexY * 2 + 1 >= m_CountY)
				return  m_CountY - 1;

			else
				return IndexY * 2 + 1;
		}

		else
			return IndexY * 2;
	}

	// 가운데
	else
		return IndexY * 2;

	return -1;
}

void CTileMapComponent::Start()
{
	CPrimitiveComponent::Start();

	if (m_Scene)
		m_Scene->SetTileMap(this);
}

bool CTileMapComponent::Init()
{
	if (!CPrimitiveComponent::Init())
		return false;

	m_Transform->Set2D(true);

	// Back 출력용 Mesh 지정
	SetMesh("LBUVRect");

	// Tile 출력용 Mesh 지정
	m_TileMesh = m_Mesh;

	// TileMap용 ConstantBuffer 생성
	m_TileMapCBuffer = new CTileMapConstantBuffer;
	m_TileMapCBuffer->Init();
	m_TileMapCBuffer->SetStart(Vector2(0.f, 0.f));
	m_TileMapCBuffer->SetEnd(Vector2(64.f, 64.f));
	m_TileMapCBuffer->SetFrame(0);

	if (CEngine::GetEditorMode())
		m_TileMapCBuffer->SetEditorMode(true);

	// Tile 출력용 Material 지정
	SetTileMaterial("TileMap");

	// Back출력용 Materail 지정
	m_vecMaterial.clear();
	AddMaterial("DefaultTileMapBack");

	// Tile Shape 지정
	m_Shape = ETileShape::Rect;

	// 기본 Tile 생성
	//CreateTile(ETileShape::Rect, 100, 100, Vector2(64.f, 64.f));


	//if (CEngine::GetEditorMode())
	//{
	//	m_TileGridMesh = CResourceManager::GetInst()->FindMesh("TileMapGridMesh");
	//	m_TileGridShader = CResourceManager::GetInst()->FindShader("TileMapGridShader");
	//}


	return true;
}

void CTileMapComponent::Update(float DeltaTime)
{
	CPrimitiveComponent::Update(DeltaTime);

	size_t	Size = m_vecTile.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecTile[i]->Update(DeltaTime);
	}
}

void CTileMapComponent::PostUpdate(float DeltaTime)
{
	CPrimitiveComponent::PostUpdate(DeltaTime);

	if (!m_vecTile.empty())
	{
		CCameraComponent* Camera = m_Scene->GetCameraManager()->GetCurrentCamera();

		Resolution	RS = CDevice::GetInst()->GetResolution();

		Vector3	LB = Camera->GetWorldPos();
		Vector3	RT = LB + Vector3((float)RS.Width, (float)RS.Height, 0.f);

		int	StartX, StartY, EndX, EndY;

		StartX = GetTileRenderIndexX(LB);
		StartY = GetTileRenderIndexY(LB);

		EndX = GetTileRenderIndexX(RT);
		EndY = GetTileRenderIndexY(RT);

		if (m_Shape == ETileShape::Isometric)
		{
			--StartX;
			--StartY;
			--StartY;

			++EndX;
			++EndY;
			++EndY;

			StartX = StartX < 0 ? 0 : StartX;
			StartY = StartY < 0 ? 0 : StartY;

			EndX = EndX >= m_CountX ? m_CountX - 1 : EndX;
			EndY = EndY >= m_CountY ? m_CountY - 1 : EndY;
		}

		Matrix	matView, matProj;
		matView = Camera->GetViewMatrix();
		matProj = Camera->GetProjMatrix();

		m_RenderCount = 0;

		for (int i = StartY; i <= EndY; ++i)
		{
			for (int j = StartX; j <= EndX; ++j)
			{
				int	Index = i * m_CountX + j;

				m_vecTile[Index]->UpdateTransform(DeltaTime);

				m_vecTileInfo[m_RenderCount].matWVP = m_vecTile[Index]->m_matWorld * matView * matProj;
				m_vecTileInfo[m_RenderCount].matWVP.Transpose();

				if (!m_vecTile[Index]->FrameEmpty())
				{
					m_vecTileInfo[m_RenderCount].Start = m_vecTile[Index]->GetFrameData().Start;
					m_vecTileInfo[m_RenderCount].End = m_vecTile[Index]->GetFrameData().End;
				}

				else
				{
					m_vecTileInfo[m_RenderCount].Start = m_vecTile[Index]->m_TileStart;
					m_vecTileInfo[m_RenderCount].End = m_vecTile[Index]->m_TileEnd;
				}

				m_vecTileInfo[m_RenderCount].Opacity = m_vecTile[Index]->m_Opacity;
				m_vecTileInfo[m_RenderCount].AnimationType = (int)m_vecTile[Index]->m_Anim2DType;
				m_vecTileInfo[m_RenderCount].Frame = m_vecTile[Index]->m_Frame;
				m_vecTileInfo[m_RenderCount].TypeColor = m_TileTypeColor[(int)m_vecTile[Index]->m_TileOption];

				// EidtorMode에서 마우스로 선택된 타일은 초록색으로 표현한다.
				if (m_EditorMouseOnTile == m_vecTile[Index])
					m_vecTileInfo[m_RenderCount].TypeColor = Vector4(0.f, 1.f, 0.f, 1.f);

				++m_RenderCount;
			}
		}

		// 위에서 만들어준 타일 정보를 구조화 버퍼에 갱신해준다.
		m_TileInfoBuffer->UpdateBuffer(&m_vecTileInfo[0], m_RenderCount);
	}
}

void CTileMapComponent::Render()
{
	// PrimitiveComponent의 Render를 수행하지 않고 상위 단계인 SceneComponent의 Render를 수행하여 Transform정보만 갱신하고 Back과 Tile들을 따로 출력한다.
	//CPrimitiveComponent::Render();
	CSceneComponent::Render();

	// TileBackTexture가 있다면 Back을 먼저 출력한다.
	if (m_TileBackTexture)
	{
		m_vecMaterial[0]->SetMaterial();

		m_Mesh->Render();

		m_vecMaterial[0]->ResetMaterial();
	}

	// Back 출력 후 출력할 Tile정보가 있다면 Tile을 출력한다.
	if (m_RenderCount > 0 && m_TileMaterial)
	{
		// 구조화버퍼의 내용을 Shader로 보내준다.
		m_TileInfoBuffer->SetShader();

		// TileMap 상수버퍼를 Shader로 보내준다.
		m_TileMapCBuffer->UpdateBuffer();

		// 재질 지정
		m_TileMaterial->SetMaterial();

		m_TileMesh->RenderInstancing(m_RenderCount);

		m_TileMaterial->ResetMaterial();

		m_TileInfoBuffer->ResetShader();
	}
}

CTileMapComponent* CTileMapComponent::Clone() const
{
	return new CTileMapComponent(*this);
}

void CTileMapComponent::Save(FILE* File)
{
	CPrimitiveComponent::Save(File);

	/*
	class CTileMapConstantBuffer*       m_TileMapCBuffer;
    class CStructuredBuffer*            m_TileInfoBuffer;
    std::vector<CTile*>                 m_vecTile;
    std::vector<TileInfo>               m_vecTileInfo;
    CSharedPtr<class CMesh>             m_TileMesh;
    CSharedPtr<class CMaterial>         m_TileMaterial;
    CSharedPtr<class CTexture>          m_TileBackTexture;
	*/

	// 기본 정보 저장
	fwrite(&m_Shape, sizeof(ETileShape), 1, File);
	fwrite(&m_CountX, sizeof(int), 1, File);
	fwrite(&m_CountY, sizeof(int), 1, File);
	fwrite(&m_Count, sizeof(int), 1, File);
	fwrite(&m_TileInfoCount, sizeof(int), 1, File);
	fwrite(&m_TileSize, sizeof(Vector2), 1, File);

	int	FrameCount = (int)m_vecTileFrame.size();

	fwrite(&FrameCount, 4, 1, File);
	fwrite(&m_vecTileFrame[0], sizeof(Animation2DFrameData), FrameCount, File);

	// TileMaterial Save
	bool	TileMaterial = false;

	if (m_TileMaterial)
		TileMaterial = true;

	fwrite(&TileMaterial, sizeof(bool), 1, File);

	if (TileMaterial)
	{
		int Length = (int)m_TileMaterial->GetName().length();

		fwrite(&Length, 4, 1, File);
		fwrite(m_TileMaterial->GetName().c_str(), 1, Length, File);

		m_TileMaterial->Save(File);
	}

	// Tile Save
	for (int i = 0; i < m_Count; ++i)
	{
		m_vecTile[i]->Save(File);
	}
}

void CTileMapComponent::Load(FILE* File)
{
	CPrimitiveComponent::Load(File);

	fread(&m_Shape, sizeof(ETileShape), 1, File);
	fread(&m_CountX, sizeof(int), 1, File);
	fread(&m_CountY, sizeof(int), 1, File);
	fread(&m_Count, sizeof(int), 1, File);
	fread(&m_TileInfoCount, sizeof(int), 1, File);
	fread(&m_TileSize, sizeof(Vector2), 1, File);

	int	FrameCount = 0;
	fread(&FrameCount, 4, 1, File);

	m_vecTileFrame.resize(FrameCount);
	fread(&m_vecTileFrame[0], sizeof(Animation2DFrameData), FrameCount, File);


	// m_TileInfoBuffer 생성
	SAFE_DELETE(m_TileInfoBuffer);
	m_TileInfoBuffer = new CStructuredBuffer;
	m_TileInfoBuffer->Init("TileInfo", sizeof(TileInfo), m_TileInfoCount, 40, true, (int)EShaderBufferType::Vertex);


	m_vecTileInfo.resize((size_t)m_Count);

	for (int i = 0; i < m_Count; ++i)
	{
		m_vecTileInfo[i].TypeColor = Vector4(1.f, 1.f, 1.f, 1.f);
		m_vecTileInfo[i].Opacity = 1.f;
	}

	m_SceneName = m_Scene->GetName();

	// TileMapCBuffer 생성
	SAFE_DELETE(m_TileMapCBuffer);

	m_TileMapCBuffer = new CTileMapConstantBuffer;
	m_TileMapCBuffer->Init();
	m_TileMapCBuffer->SetStart(m_vecTileFrame[0].Start);
	m_TileMapCBuffer->SetEnd(m_vecTileFrame[0].End);
	m_TileMapCBuffer->SetFrame(0);
	m_TileMapCBuffer->SetTileSize(m_TileSize);

	if (CEngine::GetEditorMode())
		m_TileMapCBuffer->SetEditorMode(true);

	// TileMesh 세팅
	m_TileMesh = CResourceManager::GetInst()->FindMesh("LBUVRect");

	// TileMaterial 세팅
	bool	TileMaterial = false;

	fread(&TileMaterial, sizeof(bool), 1, File);

	if (TileMaterial)
	{
		int Length = 0;
		char	TileMaterialName[256] = {};

		fread(&Length, 4, 1, File);
		fread(TileMaterialName, 1, Length, File);

		SetTileMaterial(TileMaterialName);
		m_TileMaterial->SetScene(m_Scene);
		m_TileMaterial->Load(File);
	}

	// Tile 세팅
	m_vecTile.resize((size_t)m_Count);

	for (int i = 0; i < m_Count; ++i)
	{
		CTile* Tile = new CTile;

		Tile->Load(File);
		Tile->m_Owner = this;

		m_vecTile[i] = Tile;
	}

	// TileBackTexture 세팅 -> Primitive의 Material에 Texture가 들어가있으면 꺼내서 대입만 시켜준다.
	CTexture* Texture = m_vecMaterial[0]->GetTexture();

	if (Texture)
		m_TileBackTexture = Texture;
}