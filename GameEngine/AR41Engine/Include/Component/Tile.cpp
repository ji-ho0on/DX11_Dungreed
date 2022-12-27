#include "Tile.h"
#include "TileMapComponent.h"

CTile::CTile() :
	m_Owner(nullptr),
	m_Enable(true),
	m_TileOption(ETileOption::None),
	m_IndexX(0),
	m_IndexY(0),
	m_Index(0),
	m_Anim2DType(EAnimation2DType::None),
	m_Frame(0),
	m_Time(0.f),
	m_FrameTime(0.f),
	m_PlayTime(1.f),
	m_PlayScale(1.f),
	m_Loop(true),
	m_Reverse(false),
	m_Opacity(1.f)
{
}

CTile::CTile(const CTile& Tile)
{
	m_Enable = Tile.m_Enable;
	m_TileOption = Tile.m_TileOption;
	m_Pos = Tile.m_Pos;
	m_Size = Tile.m_Size;
	m_matWorld = Tile.m_matWorld;
	m_IndexX = Tile.m_IndexX;
	m_IndexY = Tile.m_IndexY;
	m_Index = Tile.m_Index;
	m_Opacity = Tile.m_Opacity;
	m_TileStart = Tile.m_TileStart;
	m_TileEnd = Tile.m_TileEnd;

	m_Anim2DType = Tile.m_Anim2DType;
	m_Frame = Tile.m_Frame;
	m_Time = Tile.m_Time;
	m_FrameTime = Tile.m_FrameTime;
	m_PlayTime = Tile.m_PlayTime;
	m_PlayScale = Tile.m_PlayScale;
	m_Loop = Tile.m_Loop;
	m_Reverse = Tile.m_Reverse;

	size_t Size = Tile.m_vecFrameData.size();

	m_vecFrameData.resize(Size);

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecFrameData[i] = Tile.m_vecFrameData[i];
	}

	m_Owner = nullptr;
}

CTile::~CTile()
{
}

void CTile::Update(float DeltaTime)
{
	// 애니메이션 연산

	if (!m_vecFrameData.empty())
	{
		m_Time += DeltaTime * m_PlayScale;

		bool	AnimEnd = false;

		if (m_Time >= m_FrameTime)
		{
			m_Time -= m_FrameTime;

			if (m_Reverse)
			{
				--m_Frame;

				if (m_Frame < 0)
					AnimEnd = true;
			}

			else
			{
				++m_Frame;

				if (m_Frame == (int)m_vecFrameData.size())
					AnimEnd = true;
			}
		}

		if (AnimEnd)
		{
			if (m_Loop)
			{
				if (m_Reverse)
					m_Frame = (int)m_vecFrameData.size() - 1;

				else
					m_Frame = 0;
			}

			else
			{
				if (m_Reverse)
					m_Frame = 0;

				else
					m_Frame = (int)m_vecFrameData.size() - 1;
			}
		}
	}
}

void CTile::UpdateTransform(float DeltaTime)
{
	// 트랜스폼 연산
	Vector3	OwnerPos = m_Owner->GetWorldPos();

	Vector3	Pos = OwnerPos + m_Pos;

	Matrix	matScale, matTranslate;

	matScale.Scaling(m_Size.x, m_Size.y, 1.f);
	matTranslate.Translation(Pos);

	m_matWorld = matScale * matTranslate;
}

CTile* CTile::Clone()	const
{
	return new CTile(*this);
}

void CTile::Save(FILE* File)
{
	/*
	bool						m_Enable;
	class CTileMapComponent*	m_Owner;		->Load할 때 세팅
	ETileOption					m_TileOption;
	Vector3						m_Pos;
	Vector3						m_Size;
	Vector3						m_Center;		// 타일의 Center Position
	Matrix						m_matWorld;
	int							m_IndexX;
	int							m_IndexY;
	int							m_Index;
	float						m_Opacity;
	Vector2						m_TileStart;
	Vector2						m_TileEnd;

	// Animation이 적용될 경우 필요한 정보들
	std::vector<Animation2DFrameData>   m_vecFrameData;	
	EAnimation2DType                    m_Anim2DType;
	int									m_Frame;
	float								m_Time;
	float								m_FrameTime;
	float								m_PlayTime;
	float								m_PlayScale;
	bool								m_Loop;
	bool								m_Reverse;
	*/

	fwrite(&m_Enable, sizeof(bool), 1, File);
	fwrite(&m_TileOption, sizeof(ETileOption), 1, File);
	fwrite(&m_Pos, sizeof(Vector3), 1, File);
	fwrite(&m_Size, sizeof(Vector3), 1, File);
	fwrite(&m_Center, sizeof(Vector3), 1, File);
	fwrite(&m_matWorld, sizeof(Matrix), 1, File);
	fwrite(&m_IndexX, sizeof(int), 1, File);
	fwrite(&m_IndexY, sizeof(int), 1, File);
	fwrite(&m_Index, sizeof(int), 1, File);
	fwrite(&m_Opacity, sizeof(float), 1, File);
	fwrite(&m_TileStart, sizeof(Vector2), 1, File);
	fwrite(&m_TileEnd, sizeof(Vector2), 1, File);

	int	FrameCount = (int)m_vecFrameData.size();
	fwrite(&FrameCount, 4, 1, File);

	if (FrameCount > 0)
		fwrite(&m_vecFrameData[0], sizeof(Animation2DFrameData), FrameCount, File);

	fwrite(&m_Anim2DType, sizeof(EAnimation2DType), 1, File);
	fwrite(&m_Frame, sizeof(int), 1, File);
	fwrite(&m_Time, sizeof(float), 1, File);
	fwrite(&m_FrameTime, sizeof(float), 1, File);
	fwrite(&m_PlayTime, sizeof(float), 1, File);
	fwrite(&m_PlayScale, sizeof(float), 1, File);
	fwrite(&m_Loop, sizeof(bool), 1, File);
	fwrite(&m_Reverse, sizeof(bool), 1, File);
}

void CTile::Load(FILE* File)
{
	fread(&m_Enable, sizeof(bool), 1, File);
	fread(&m_TileOption, sizeof(ETileOption), 1, File);
	fread(&m_Pos, sizeof(Vector3), 1, File);
	fread(&m_Size, sizeof(Vector3), 1, File);
	fread(&m_Center, sizeof(Vector3), 1, File);
	fread(&m_matWorld, sizeof(Matrix), 1, File);
	fread(&m_IndexX, sizeof(int), 1, File);
	fread(&m_IndexY, sizeof(int), 1, File);
	fread(&m_Index, sizeof(int), 1, File);
	fread(&m_Opacity, sizeof(float), 1, File);
	fread(&m_TileStart, sizeof(Vector2), 1, File);
	fread(&m_TileEnd, sizeof(Vector2), 1, File);

	int	FrameCount = 0;
	fread(&FrameCount, 4, 1, File);

	m_vecFrameData.resize(FrameCount);

	if (FrameCount > 0)
		fread(&m_vecFrameData[0], sizeof(Animation2DFrameData), FrameCount, File);

	fread(&m_Anim2DType, sizeof(EAnimation2DType), 1, File);
	fread(&m_Frame, sizeof(int), 1, File);
	fread(&m_Time, sizeof(float), 1, File);
	fread(&m_FrameTime, sizeof(float), 1, File);
	fread(&m_PlayTime, sizeof(float), 1, File);
	fread(&m_PlayScale, sizeof(float), 1, File);
	fread(&m_Loop, sizeof(bool), 1, File);
	fread(&m_Reverse, sizeof(bool), 1, File);
}
