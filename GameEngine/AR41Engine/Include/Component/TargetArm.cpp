#include "TargetArm.h"
#include "../GameObject/GameObject.h"
#include "../Scene/Scene.h"
#include "TileMapComponent.h"
#include "../Device.h"

CTargetArm::CTargetArm() :
	m_TargetDistance(0.f)
{
	SetTypeID<CTargetArm>();

	m_ComponentTypeName = "TargetArm";
}

CTargetArm::CTargetArm(const CTargetArm& component) :
	CSceneComponent(component)
{
	m_TargetDistance = component.m_TargetDistance;
	m_TargetOffset = component.m_TargetOffset;
	m_TargetDistanceAxis = component.m_TargetDistanceAxis;
}

CTargetArm::~CTargetArm()
{
}

void CTargetArm::Destroy()
{
	CSceneComponent::Destroy();
}

void CTargetArm::Start()
{
	CSceneComponent::Start();

	// Start시 Scene에 소속되어 있는 TileMap을 하나 받아둔다.
	if (m_Scene)
	{
		CTileMapComponent* TileMap = m_Owner->GetScene()->GetTileMap();

		if (TileMap)
		{
			float TileMapSizeX = TileMap->GetCountX() * TileMap->GetTileSize().x;
			float TileMapSizeY = TileMap->GetCountY() * TileMap->GetTileSize().y;

			Vector2 TileMapPos = TileMap->GetWorldPos();

			Resolution RS = CDevice::GetInst()->GetResolution();

			m_MinX = TileMapPos.x;
			m_MaxX = m_MinX + TileMapSizeX;// -(float)RS.Width;

			m_MinY = TileMapPos.y;
			m_MaxY = m_MinY + TileMapSizeY;// -(float)RS.Height;
		}
	}
}

bool CTargetArm::Init()
{
	CSceneComponent::Init();

	return true;
}

void CTargetArm::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);

	if (m_Parent)
	{
		Vector3	ParentPos = m_Parent->GetWorldPos();

		Vector3 Pos = ParentPos - GetWorldAxis(m_TargetDistanceAxis) * m_TargetDistance;

		Resolution RS = CDevice::GetInst()->GetResolution();

		Vector3 Resolution = Vector3((float)RS.Width, (float)RS.Height, 0.f);

		//Vector2 MyPos = GetWorldPos();

		//float EndX = MyPos.x + Resolution.x;

		//if (EndX >= m_MaxX)
		//{
		//	m_TargetOffset.x -= (EndX - m_MaxX);
		//}

		//else if (EndX < m_MaxX && m_TargetOffset.x < -660.f)
		//{
		//	m_TargetOffset.x += (m_MaxX - EndX);
		//}

		//else if (MyPos.x <= m_MinX)
		//{
		//	m_TargetOffset.x += (m_MinX - MyPos.x);
		//}

		//else if (EndX < m_MaxX && m_TargetOffset.x > -620.f)
		//{
		//	m_TargetOffset.x -= (MyPos.x - m_MinX);
		//}

		//float EndY = MyPos.y + Resolution.y;

		//if (EndY >= m_MaxY)
		//{
		//	m_TargetOffset.y -= (EndY - m_MaxY);
		//}

		//else if (EndY < m_MaxY && abs(m_TargetOffset.y) > 380.f)
		//{
		//	m_TargetOffset.y += (m_MaxY - EndY);
		//}

		//float StartY = MyPos.y;

		//if (StartY < m_MinY)
		//{
		//	m_TargetOffset.y += (m_MinY - StartY);
		//}

		//else if (StartY > m_MinY && abs(m_TargetOffset.y) < 320.f)
		//{
		//	m_TargetOffset.y -= (StartY - m_MinY);
		//}

		//SetWorldPosition(Pos + m_TargetOffset);


		Vector3 RevisionPos = Pos + m_TargetOffset;

		if (RevisionPos.x < m_MinX)
			RevisionPos.x = m_MinX;

		else if(RevisionPos.x > m_MaxX - Resolution.x)
			RevisionPos.x = m_MaxX - Resolution.x;

		if (RevisionPos.y < m_MinY)
			RevisionPos.y = m_MinY;

		else if (RevisionPos.y > m_MaxY - Resolution.y)
			RevisionPos.y = m_MaxY - Resolution.y;

		SetWorldPosition(RevisionPos);
	}


	//float Yend = CameraPos.y  + (float)RS.Height;
//if (m_CameraMaxY <= Yend)// 
//{
//	float YValue = Yend - m_CameraMaxY;

//	m_TargetOffset.y -= YValue;
//}

//else if (m_CameraMaxY >= Yend && (abs)(m_TargetOffset.y) > 600)
//{
//	float YValue = m_CameraMaxY - Yend;

//	m_TargetOffset.y += YValue;
//}

//float YStart = CameraPos.y;

//if (m_CameraMinY > YStart)
//{
//	float YValue = m_CameraMinY + YStart;

//	m_TargetOffset.y -= YValue;
//}

//else if (m_CameraMinY < YStart &&(abs)(m_TargetOffset.y) < 100)
//{
//	float YValue = m_CameraMinY - YStart;

//	m_TargetOffset.y += YValue;
//}



	//float Xend = CameraPos.x + (float)RS.Width;

	//if (m_CameraMaxX <= Xend)
	//{
	//	float XValue =  Xend - m_CameraMaxX;

	//	m_TargetOffset.x -= XValue;
	//}


/*	if (Pos.x - Resolution.x / 2.f < m_MinX)
	{
		m_TargetOffset.x = m_MinX - Pos.x;
	}*/

	//else if (Pos.x + Resolution.x / 2.f > m_MaxX)
	//{
	//	m_TargetOffset.x = -Resolution.x / 2.f - (Pos.x + Resolution.x / 2.f - m_MaxX);
	//}
}

void CTargetArm::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
}

void CTargetArm::Render()
{
	CSceneComponent::Render();
}

CTargetArm* CTargetArm::Clone() const
{
	return new CTargetArm(*this);
}

void CTargetArm::Save(FILE* File)
{
	CSceneComponent::Save(File);

	fwrite(&m_TargetDistance, sizeof(float), 1, File);
	fwrite(&m_TargetDistanceAxis, sizeof(AXIS), 1, File);
}

void CTargetArm::Load(FILE* File)
{
	CSceneComponent::Load(File);

	fread(&m_TargetDistance, sizeof(float), 1, File);
	fread(&m_TargetDistanceAxis, sizeof(AXIS), 1, File);
}
