#include "MeshManager.h"
#include "SpriteMesh.h"

CMeshManager::CMeshManager()
{
}

CMeshManager::~CMeshManager()
{
}

bool CMeshManager::Init()
{
	// �⺻ Mesh�� �����صд�.
	// VertexColor�� �̿��� ������ ��ġ�� ���� �����صд�.

	// �����߽� ColorMesh
	VertexColor	CenterColorMesh[4] =
	{
		VertexColor(Vector3(-0.5f, 0.5f, 0.f), Vector4::Red),
		VertexColor(Vector3(0.5f, 0.5f, 0.f), Vector4::Green),
		VertexColor(Vector3(-0.5f, -0.5f, 0.f), Vector4::Blue),
		VertexColor(Vector3(0.5f, -0.5f, 0.f), Vector4(1.f, 0.f, 1.f, 1.f))
	};

	unsigned int	RectIndex[6] = { 0, 1, 3, 0, 3, 2 };

	CreateMesh(nullptr, EMeshType::Sprite, "CenterColorRect", CenterColorMesh, sizeof(VertexColor), 4,
		D3D11_USAGE_IMMUTABLE, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, RectIndex, 4, 6,
		D3D11_USAGE_IMMUTABLE, DXGI_FORMAT_R32_UINT);

	CMesh* Mesh = FindMesh("CenterColorRect");

	Mesh->SetMaterial(0, 0, "DefaultColor");

	VertexColor	LBColorMesh[4] =
	{
		VertexColor(Vector3(0.f, 1.f, 0.f), Vector4::Red),
		VertexColor(Vector3(1.f, 1.f, 0.f), Vector4::Green),
		VertexColor(Vector3(0.f, 0.f, 0.f), Vector4::Blue),
		VertexColor(Vector3(1.f, 0.f, 0.f), Vector4(1.f, 0.f, 1.f, 1.f))
	};

	CreateMesh(nullptr, EMeshType::Sprite, "LBColorRect", LBColorMesh, sizeof(VertexColor), 4,
		D3D11_USAGE_IMMUTABLE,	D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, RectIndex, 4, 6,
		D3D11_USAGE_IMMUTABLE, DXGI_FORMAT_R32_UINT);

	Mesh = FindMesh("LBColorRect");

	Mesh->SetMaterial(0, 0, "DefaultColor");


	VertexUV	CenterUVMesh[4] =
	{
		VertexUV(Vector3(-0.5f, 0.5f, 0.f), Vector2(0.f, 0.f)),
		VertexUV(Vector3(0.5f, 0.5f, 0.f), Vector2(1.f, 0.f)),
		VertexUV(Vector3(-0.5f, -0.5f, 0.f), Vector2(0.f, 1.f)),
		VertexUV(Vector3(0.5f, -0.5f, 0.f), Vector2(1.f, 1.f))
	};

	CreateMesh(nullptr, EMeshType::Sprite, "CenterUVRect", CenterUVMesh, sizeof(VertexUV), 4,
		D3D11_USAGE_IMMUTABLE, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, RectIndex, 4, 6,
		D3D11_USAGE_IMMUTABLE, DXGI_FORMAT_R32_UINT);

	Mesh = FindMesh("CenterUVRect");

	Mesh->SetMaterial(0, 0, "DefaultTexture");

	VertexUV	LBUVMesh[4] =
	{
		VertexUV(Vector3(0.f, 1.f, 0.f), Vector2(0.f, 0.f)),
		VertexUV(Vector3(1.f, 1.f, 0.f), Vector2(1.f, 0.f)),
		VertexUV(Vector3(0.f, 0.f, 0.f), Vector2(0.f, 1.f)),
		VertexUV(Vector3(1.f, 0.f, 0.f), Vector2(1.f, 1.f))
	};

	CreateMesh(nullptr, EMeshType::Sprite, "LBUVRect", LBUVMesh, sizeof(VertexUV), 4,
		D3D11_USAGE_IMMUTABLE, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, RectIndex, 4, 6,
		D3D11_USAGE_IMMUTABLE, DXGI_FORMAT_R32_UINT);

	Mesh = FindMesh("LBUVRect");

	Mesh->SetMaterial(0, 0, "DefaultTexture");


	VertexUV	CenterUVScrollMesh[4] =
	{
		VertexUV(Vector3(-0.5f, 0.5f, 0.f), Vector2(0.f, 0.f)),
		VertexUV(Vector3(0.5f, 0.5f, 0.f), Vector2(1.f, 0.f)),
		VertexUV(Vector3(-0.5f, -0.5f, 0.f), Vector2(0.f, 1.f)),
		VertexUV(Vector3(0.5f, -0.5f, 0.f), Vector2(1.f, 1.f))
	};

	CreateMesh(nullptr, EMeshType::Sprite, "CenterUVScrollRect", CenterUVScrollMesh, sizeof(VertexUV), 4,
		D3D11_USAGE_IMMUTABLE, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, RectIndex, 4, 6,
		D3D11_USAGE_IMMUTABLE, DXGI_FORMAT_R32_UINT);

	Mesh = FindMesh("CenterUVScrollRect");

	Mesh->SetMaterial(0, 0, "ScrollTexture");

	VertexUV	LBUVScrollMesh[4] =
	{
		VertexUV(Vector3(0.f, 1.f, 0.f), Vector2(0.f, 0.f)),
		VertexUV(Vector3(1.f, 1.f, 0.f), Vector2(1.f, 0.f)),
		VertexUV(Vector3(0.f, 0.f, 0.f), Vector2(0.f, 1.f)),
		VertexUV(Vector3(1.f, 0.f, 0.f), Vector2(1.f, 1.f))
	};

	CreateMesh(nullptr, EMeshType::Sprite, "LBUVScrollRect", LBUVScrollMesh, sizeof(VertexUV), 4,
		D3D11_USAGE_IMMUTABLE, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, RectIndex, 4, 6,
		D3D11_USAGE_IMMUTABLE, DXGI_FORMAT_R32_UINT);

	Mesh = FindMesh("LBUVScrollRect");

	Mesh->SetMaterial(0, 0, "ScrollTexture");

	Vector3	Box2DLineMesh[5] =
	{
		Vector3(-0.5f, 0.5f, 0.f),
		Vector3(0.5f, 0.5f, 0.f),
		Vector3(0.5f, -0.5f, 0.f),
		Vector3(-0.5f, -0.5f, 0.f),
		Vector3(-0.5f, 0.5f, 0.f)
	};

	CreateMesh(nullptr, EMeshType::Sprite, "Box2DLineMesh", Box2DLineMesh, sizeof(Vector3), 5,
		D3D11_USAGE_IMMUTABLE, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	Vector3	LBBox2DLineMesh[5] =
	{
		Vector3(0.f, 1.f, 0.f),
		Vector3(1.f, 1.f, 0.f),
		Vector3(1.f, 0.f, 0.f),
		Vector3(0.f, 0.f, 0.f),
		Vector3(0.f, 1.f, 0.f)
	};

	CreateMesh(nullptr, EMeshType::Sprite, "LBBox2DLineMesh", LBBox2DLineMesh, sizeof(Vector3), 5,
		D3D11_USAGE_IMMUTABLE, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	Vector3	Sphere2DLineMesh[361];

	Sphere2DLineMesh[0].x = 1.f;
	Sphere2DLineMesh[0].y = 0.f;

	for (int i = 0; i < 360; ++i)
	{
		float Radian = (i + 1) * PI / 180.f;

		Sphere2DLineMesh[i + 1].x = cosf(Radian);
		Sphere2DLineMesh[i + 1].y = sinf(Radian);
	}

	Sphere2DLineMesh[360].x = 1.f;
	Sphere2DLineMesh[360].y = 0.f;

	CreateMesh(nullptr, EMeshType::Sprite, "Sphere2DLineMesh", Sphere2DLineMesh, sizeof(Vector3), 361,
		D3D11_USAGE_IMMUTABLE, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	Vector3	Line2DLineMesh[2] =
	{
		Vector3(0.f, 0.f, 0.f),
		Vector3(1.f, 1.f, 0.f)
	};

	CreateMesh(nullptr, EMeshType::Sprite, "Line2DLineMesh", Line2DLineMesh, sizeof(Vector3), 2,
		D3D11_USAGE_IMMUTABLE, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	Vector3	TileMapGridMesh[5] =
	{
		Vector3(0.01f, 0.99f, 0.f),
		Vector3(0.99f, 0.99f, 0.f),
		Vector3(0.99f, 0.01f, 0.f),
		Vector3(0.01f, 0.01f, 0.f),
		Vector3(0.01f, 0.99f, 0.f)
	};

	CreateMesh(nullptr, EMeshType::Sprite, "TileMapGridMesh", TileMapGridMesh, sizeof(Vector3), 5,
		D3D11_USAGE_IMMUTABLE, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	return true;
}

bool CMeshManager::CreateMesh(CScene* Scene, EMeshType Type, const std::string& Name,
	void* VtxData, int Size, int Count, D3D11_USAGE VtxUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive,
	void* IdxData, int IdxSize,	int IdxCount, D3D11_USAGE IdxUsage, DXGI_FORMAT Fmt)
{
	// map�� �̹� ���� Mesh�� ������ return
	if (FindMesh(Name))
		return true;

	// Mesh�� �����Ѵ�.
	CMesh* Mesh = nullptr;

	// Mesh�� Type�� ���� Mesh�� ���� �Ҵ��Ѵ�.
	switch (Type)
	{
	case EMeshType::Sprite:
		Mesh = new CSpriteMesh;
		break;
	case EMeshType::UI:
		break;
	case EMeshType::Static:
		break;
	case EMeshType::Animation:
		break;
	}

	// Scene�� �̸��� �����Ѵ�.
	Mesh->SetScene(Scene);
	Mesh->SetName(Name);

	// Mesh�� �����Ѵ�.
	if (!Mesh->CreateMesh(VtxData, Size, Count, VtxUsage, Primitive, IdxData, IdxSize, IdxCount, IdxUsage, Fmt))
	{
		// ���� �� Release����
		SAFE_RELEASE(Mesh);
		return false;
	}

	// ������ �Ϸ�Ǹ� Map�� �־���
	m_mapMesh.insert(std::make_pair(Name, Mesh));

	return true;
}

CMesh* CMeshManager::FindMesh(const std::string& Name)
{
	// MeshManager�� Map���� �̸��� ���� ã��
	auto	iter = m_mapMesh.find(Name);

	if (iter == m_mapMesh.end())
		return nullptr;

	return iter->second;
}

void CMeshManager::ReleaseMesh(const std::string& Name)
{
	// MeshManager�� Map���� �̸��� ���� ã�Ƽ� ReferenceCount�� 1�̶�� Map���� �����ش�.
	auto	iter = m_mapMesh.find(Name);

	if (iter != m_mapMesh.end())
	{
		if (iter->second->GetRefCount() == 1)
			m_mapMesh.erase(iter);
	}
}
