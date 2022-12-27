#include "CollisionManager.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderOBB2D.h"
#include "Component/ColliderPixel.h"
#include "Component/ColliderLine2D.h"

DEFINITION_SINGLE(CCollisionManager)

CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
	{
		auto	iter = m_mapProfile.begin();
		auto	iterEnd = m_mapProfile.end();

		for (; iter != iterEnd; ++iter)
		{
			SAFE_DELETE(iter->second);
		}
	}

	{
		auto	iter = m_vecChannel.begin();
		auto	iterEnd = m_vecChannel.end();

		for (; iter != iterEnd; ++iter)
		{
			SAFE_DELETE((*iter));
		}
	}
}

bool CCollisionManager::Init()
{
	CreateChannel("Default", ECollision_Interaction::Collision);
	CreateChannel("Mouse", ECollision_Interaction::Collision);

	CreateProfile("Default", "Default", true);
	CreateProfile("Mouse", "Mouse", true);

	return true;
}

bool CCollisionManager::CreateProfile(const std::string& Name, const std::string& ChannelName, bool Enable,
	ECollision_Interaction BaseInteraction)
{
	CollisionProfile* Profile = FindProfile(Name);

	if (Profile)
		return false;

	CollisionChannel* Channel = nullptr;

	size_t	Count = m_vecChannel.size();

	for (size_t i = 0; i < Count; ++i)
	{
		if (m_vecChannel[i]->Name == ChannelName)
		{
			Channel = m_vecChannel[i];
			break;
		}
	}

	if (!Channel)
		return false;

	Profile = new CollisionProfile;

	Profile->Name = Name;
	Profile->Channel = Channel;
	Profile->Enable = Enable;
	Profile->vecCollisionInteraction.resize(m_vecChannel.size());

	Count = Profile->vecCollisionInteraction.size();

	for (size_t i = 0; i < Count; ++i)
	{
		Profile->vecCollisionInteraction[i] = BaseInteraction;
	}

	m_mapProfile.insert(std::make_pair(Name, Profile));

	return true;
}

bool CCollisionManager::SetCollisionInteraction(const std::string& Name, const std::string& ChannelName,
	ECollision_Interaction Interaction)
{
	CollisionProfile* Profile = FindProfile(Name);

	if (!Profile)
		return false;

	CollisionChannel* Channel = nullptr;

	size_t	Count = m_vecChannel.size();

	for (size_t i = 0; i < Count; ++i)
	{
		if (m_vecChannel[i]->Name == ChannelName)
		{
			Channel = m_vecChannel[i];
			break;
		}
	}

	if (!Channel)
		return false;

	Profile->vecCollisionInteraction[(int)Channel->Channel] = Interaction;

	return true;
}

bool CCollisionManager::CreateChannel(const std::string& Name, ECollision_Interaction Interaction)
{
	size_t	Count = m_vecChannel.size();

	for (size_t i = 0; i < Count; ++i)
	{
		if (m_vecChannel[i]->Name == Name)
			return false;
	}

	CollisionChannel* NewChannel = new CollisionChannel;

	NewChannel->Name = Name;
	NewChannel->Channel = (ECollision_Channel)m_vecChannel.size();
	NewChannel->Interaction = Interaction;

	m_vecChannel.push_back(NewChannel);

	auto	iter = m_mapProfile.begin();
	auto	iterEnd = m_mapProfile.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second->vecCollisionInteraction.push_back(Interaction);
	}

	return true;
}

CollisionProfile* CCollisionManager::FindProfile(const std::string& Name)
{
	auto	iter = m_mapProfile.find(Name);

	if (iter == m_mapProfile.end())
		return nullptr;

	return iter->second;
}

void CCollisionManager::GetAllProfileName(std::vector<std::string>& vecProfileName)
{
	auto iter = m_mapProfile.begin();
	auto iterEnd = m_mapProfile.end();

	for (; iter != iterEnd; ++iter)
	{
		vecProfileName.push_back(iter->second->Name);
	}
}

bool CCollisionManager::CollisionBox2DToBox2D(Vector2& HitPoint, CColliderBox2D* Src, CColliderBox2D* Dest)
{
	if (CollisionBox2DToBox2D(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionSphere2DToSphere2D(Vector2& HitPoint, CColliderSphere2D* Src, CColliderSphere2D* Dest)
{
	if (CollisionSphere2DToSphere2D(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionOBB2DToOBB2D(Vector2& HitPoint, CColliderOBB2D* Src, CColliderOBB2D* Dest)
{
	if (CollisionOBB2DToOBB2D(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionPixelToPixel(Vector2& HitPoint, CColliderPixel* Src, CColliderPixel* Dest)
{
	if (CollisionPixelToPixel(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionLine2DToLine2D(Vector2& HitPoint, CColliderLine2D* Src, CColliderLine2D* Dest)
{
	if (CollisionLine2DToLine2D(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionBox2DToSphere2D(Vector2& HitPoint, CColliderBox2D* Src, CColliderSphere2D* Dest)
{
	if (CollisionBox2DToSphere2D(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionBox2DToOBB2D(Vector2& HitPoint, CColliderBox2D* Src, CColliderOBB2D* Dest)
{
	if (CollisionBox2DToOBB2D(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionBox2DToPixel(Vector2& HitPoint, CColliderBox2D* Src, CColliderPixel* Dest)
{
	if (CollisionBox2DToPixel(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionSphere2DToOBB2D(Vector2& HitPoint, CColliderSphere2D* Src, CColliderOBB2D* Dest)
{
	if (CollisionSphere2DToOBB2D(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionSphere2DToPixel(Vector2& HitPoint, CColliderSphere2D* Src, CColliderPixel* Dest)
{
	if (CollisionSphere2DToPixel(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionOBB2DToPixel(Vector2& HitPoint, CColliderOBB2D* Src, CColliderPixel* Dest)
{
	if (CollisionOBB2DToPixel(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionPointToBox2D(Vector2& HitPoint, const Vector2& Src, CColliderBox2D* Dest)
{
	if (CollisionPointToBox2D(HitPoint, Src, Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionPointToSphere2D(Vector2& HitPoint, const Vector2& Src, CColliderSphere2D* Dest)
{
	if (CollisionPointToSphere2D(HitPoint, Src, Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionPointToOBB2D(Vector2& HitPoint, const Vector2& Src, CColliderOBB2D* Dest)
{
	if (CollisionPointToOBB2D(HitPoint, Src, Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionPointToPixel(Vector2& HitPoint, const Vector2& Src, CColliderPixel* Dest)
{
	if (CollisionPointToPixel(HitPoint, Src, Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionPointToLine2D(Vector2& HitPoint, const Vector2& Src, CColliderLine2D* Dest)
{
	if (CollisionPointToLine2D(HitPoint, Src, Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionBox2DToLine2D(Vector2& HitPoint, CColliderBox2D* Src, CColliderLine2D* Dest)
{
	if (CollisionBox2DToLine2D(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionSphere2DToLine2D(Vector2& HitPoint, CColliderSphere2D* Src, CColliderLine2D* Dest)
{
	if (CollisionSphere2DToLine2D(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionOBB2DToLine2D(Vector2& HitPoint, CColliderOBB2D* Src, CColliderLine2D* Dest)
{
	if (CollisionOBB2DToLine2D(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionPixelToLine2D(Vector2& HitPoint, CColliderPixel* Src, CColliderLine2D* Dest)
{
	if (CollisionPixelToLine2D(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionBox2DToBox2D(Vector2& HitPoint, const Box2DInfo& Src, const Box2DInfo& Dest)
{
	if (Src.Left > Dest.Right)
		return false;

	else if (Src.Right < Dest.Left)
		return false;

	else if (Src.Bottom > Dest.Top)
		return false;

	else if (Src.Top < Dest.Bottom)
		return false;

	ComputeHitPoint(HitPoint, Src, Dest);

	return true;
}

bool CCollisionManager::CollisionSphere2DToSphere2D(Vector2& HitPoint, const Sphere2DInfo& Src, const Sphere2DInfo& Dest)
{
	float	Distance = Src.Center.Distance(Dest.Center);

	bool result = Distance <= Src.Radius + Dest.Radius;

	HitPoint = (Src.Center + Dest.Center) / 2.f;

	return result;
}

bool CCollisionManager::CollisionOBB2DToOBB2D(Vector2& HitPoint, const OBB2DInfo& Src, const OBB2DInfo& Dest)
{
	Vector2	CenterLine = Src.Center - Dest.Center;

	Vector2	Axis = Src.Axis[AXIS2D_X];

	float CenterProjDist = abs(CenterLine.Dot(Axis));

	float SrcDist, DestDist;

	SrcDist = Src.Length[AXIS2D_X];
	DestDist = abs(Axis.Dot(Dest.Axis[AXIS2D_X]) * Dest.Length[AXIS2D_X]) +	abs(Axis.Dot(Dest.Axis[AXIS2D_Y]) * Dest.Length[AXIS2D_Y]);

	if (CenterProjDist > SrcDist + DestDist)
		return false;

	Axis = Src.Axis[AXIS2D_Y];

	CenterProjDist = abs(CenterLine.Dot(Axis));

	SrcDist = Src.Length[AXIS2D_Y];
	DestDist = abs(Axis.Dot(Dest.Axis[AXIS2D_X]) * Dest.Length[AXIS2D_X]) +	abs(Axis.Dot(Dest.Axis[AXIS2D_Y]) * Dest.Length[AXIS2D_Y]);

	if (CenterProjDist > SrcDist + DestDist)
		return false;

	Axis = Dest.Axis[AXIS2D_X];

	CenterProjDist = abs(CenterLine.Dot(Axis));

	SrcDist = abs(Axis.Dot(Src.Axis[AXIS2D_X]) * Src.Length[AXIS2D_X]) + abs(Axis.Dot(Src.Axis[AXIS2D_Y]) * Src.Length[AXIS2D_Y]);
	DestDist = Dest.Length[AXIS2D_X];

	if (CenterProjDist > SrcDist + DestDist)
		return false;

	Axis = Dest.Axis[AXIS2D_Y];

	CenterProjDist = abs(CenterLine.Dot(Axis));

	SrcDist = abs(Axis.Dot(Src.Axis[AXIS2D_X]) * Src.Length[AXIS2D_X]) + abs(Axis.Dot(Src.Axis[AXIS2D_Y]) * Src.Length[AXIS2D_Y]);;
	DestDist = Dest.Length[AXIS2D_Y];

	if (CenterProjDist > SrcDist + DestDist)
		return false;

	Box2DInfo	SrcInfo = ConvertBox2DInfo(Src);
	Box2DInfo	DestInfo = ConvertBox2DInfo(Dest);

	ComputeHitPoint(HitPoint, SrcInfo, DestInfo);

	return true;
}

bool CCollisionManager::CollisionPixelToPixel(Vector2& HitPoint, const PixelInfo& Src, const PixelInfo& Dest)
{
	// 각 픽셀충돌체를 구성하는 사각형과 충돌처리를 먼저 한다.
	if (!CollisionBox2DToBox2D(HitPoint, Src.Box2D, Dest.Box2D))
		return false;

	// 두 사각형이 겹쳐지는 영역을 구하고 해당 영역의 픽셀정보를 확인하여 충돌이 되었는지를 판단한다.
	Box2DInfo OverlapInfo = OverlapBox2D(Src.Box2D, Dest.Box2D);

	// 겹치는 영역의 좌표를 픽셀 이미지의 좌하단 좌표만큼 빼주어서 상대적인 좌표로 변환한다.
	OverlapInfo.Left -= Dest.Box2D.Left;
	OverlapInfo.Bottom -= Dest.Box2D.Bottom;
	OverlapInfo.Right -= Dest.Box2D.Left;
	OverlapInfo.Top -= Dest.Box2D.Bottom;

	float Width = (float)Dest.Width;
	float Height = (float)Dest.Height;

	// 만약 겹치는 영역의 좌표가 변환되었는데 좌하단이 0, 0보다 작거나, 우상단이 픽셀 이미지의 크기보다 크다면 교체한다.
	OverlapInfo.Left = OverlapInfo.Left < 0.f ? 0.f : OverlapInfo.Left;
	OverlapInfo.Bottom = OverlapInfo.Bottom < 0.f ? 0.f : OverlapInfo.Bottom;
	OverlapInfo.Right = OverlapInfo.Right > Width ? Width - 1.f : OverlapInfo.Right;
	OverlapInfo.Top = OverlapInfo.Top > Height ? Height - 1.f : OverlapInfo.Top;

	// Bottom과 Top을 뒤집어서 이미지에 맞춰준다.(이미지는 좌상단이 시작점이기 때문)
	OverlapInfo.Bottom = Height - OverlapInfo.Bottom;
	OverlapInfo.Top = Height - OverlapInfo.Top;

	// 충돌되었는지를 판단할 변수 생성
	bool	Collision = false;

	// Top이 0이 되었으므로 Top부터 Bottom까지 반복
	for (int y = (int)OverlapInfo.Top; y < (int)OverlapInfo.Bottom; ++y)
	{
		// Left부터 Right까지 반복
		for (int x = (int)OverlapInfo.Left; x < (int)OverlapInfo.Right; ++x)
		{
			// Pixel의 정보는 R,G,B,A 순서대로 저장되어있기때문에 Index는 4개씩 띄워가며 구한다
			// 한 줄이 Left부터 Right까지 반복했다면 다음줄의 Index는 픽셀 이미지의 너비 * 4만큼의 Index를 추가한다.
			int SrcIndex = y * (int)Src.Width * 4 + x * 4;
			int	DestIndex = y * (int)Dest.Width * 4 + x * 4;

			// ColorCollisoinType에 따라 충돌 여부를 판단한다.
			switch (Dest.PixelColorCollisionType)
			{
				// 특정 Color를 무시하기로 했다면 해당 Color와 일치한다면 충돌하지 않고, 아니라면 충돌했다고 판단
			case EPixelCollision_Type::Color_Ignore:
				if (Dest.Pixel[DestIndex] == Dest.TypeColor[0] &&
					Dest.Pixel[DestIndex + 1] == Dest.TypeColor[1] &&
					Dest.Pixel[DestIndex + 2] == Dest.TypeColor[2])
					continue;

				else
				{
					switch (Src.PixelColorCollisionType)
					{
					case EPixelCollision_Type::Color_Ignore:
						if (Src.Pixel[SrcIndex] == Src.TypeColor[0] &&
							Src.Pixel[SrcIndex + 1] == Src.TypeColor[1] &&
							Src.Pixel[SrcIndex + 2] == Src.TypeColor[2])
							continue;

						else
							Collision = true;

						break;
					case EPixelCollision_Type::Color_Confirm:
						if (Src.Pixel[SrcIndex] == Src.TypeColor[0] &&
							Src.Pixel[SrcIndex + 1] == Src.TypeColor[1] &&
							Src.Pixel[SrcIndex + 2] == Src.TypeColor[2])
							Collision = true;

						else
							continue;

						break;
					}
				}
				break;
				// 특정 Color로 충돌하기로 했다면 해당 Color와 일치한다면 충돌했다고 판단하고, 아니라면 충돌하지 않는다.
			case EPixelCollision_Type::Color_Confirm:
				if (Dest.Pixel[DestIndex] == Dest.TypeColor[0] &&
					Dest.Pixel[DestIndex + 1] == Dest.TypeColor[1] &&
					Dest.Pixel[DestIndex + 2] == Dest.TypeColor[2])
				{
					switch (Src.PixelColorCollisionType)
					{
					case EPixelCollision_Type::Color_Ignore:
						if (Src.Pixel[SrcIndex] == Src.TypeColor[0] &&
							Src.Pixel[SrcIndex + 1] == Src.TypeColor[1] &&
							Src.Pixel[SrcIndex + 2] == Src.TypeColor[2])
							continue;

						else
							Collision = true;

						break;
					case EPixelCollision_Type::Color_Confirm:
						if (Src.Pixel[SrcIndex] == Src.TypeColor[0] &&
							Src.Pixel[SrcIndex + 1] == Src.TypeColor[1] &&
							Src.Pixel[SrcIndex + 2] == Src.TypeColor[2])
							Collision = true;

						else
							continue;

						break;
					}
				}

				else
					continue;
				break;
			}

			// AlphaCollisoinType에 따라 충돌 여부를 판단한다.
			switch (Dest.PixelAlphaCollisionType)
			{
				// 특정 Alpha를 무시하기로 했다면 해당 Alpha와 일치한다면 충돌하지 않고, 아니라면 충돌했다고 판단
			case EPixelCollision_Type::Alpha_Ignore:
				if (Dest.Pixel[DestIndex + 3] == Dest.TypeColor[3])
					continue;

				else
				{
					switch (Src.PixelAlphaCollisionType)
					{
					case EPixelCollision_Type::Alpha_Ignore:
						if (Src.Pixel[SrcIndex + 3] == Dest.TypeColor[3])
							continue;

						Collision = true;
						break;
					case EPixelCollision_Type::Alpha_Confirm:
						if (Src.Pixel[SrcIndex + 3] == Dest.TypeColor[3])
							Collision = true;

						else
							continue;
						break;
					}
				}
				break;
				// 특정 Alpha로 충돌하기로 했다면 해당 Color와 일치한다면 충돌했다고 판단하고, 아니라면 충돌하지 않는다.
			case EPixelCollision_Type::Alpha_Confirm:
				if (Dest.Pixel[DestIndex + 3] == Dest.TypeColor[3])
				{
					switch (Src.PixelAlphaCollisionType)
					{
					case EPixelCollision_Type::Alpha_Ignore:
						if (Dest.Pixel[DestIndex + 3] == Dest.TypeColor[3])
							continue;

						else
							Collision = true;
						break;
					case EPixelCollision_Type::Alpha_Confirm:
						if (Dest.Pixel[DestIndex + 3] == Dest.TypeColor[3])
							Collision = true;

						else
							continue;
						break;
					}
				}

				else
					continue;
				break;
			}

			// 이미 충돌되었다면 반복문을 빠져나간다.
			if (Collision)
				break;
		}

		// 이미 충돌되었다면 반복문을 빠져나간다.
		if (Collision)
			break;
	}

	ComputeHitPoint(HitPoint, Src.Box2D, Dest.Box2D);

	return Collision;
}

bool CCollisionManager::CollisionLine2DToLine2D(Vector2& HitPoint, const Line2DInfo& Src, const Line2DInfo& Dest)
{
	// 매개 변수 u, v 를 구하기 위한 분모를 구한다.
	float Denominator = (Src.Point2.x - Src.Point1.x) * (Dest.Point2.y - Dest.Point1.y) - (Dest.Point2.x - Dest.Point1.x) * (Src.Point2.y - Src.Point1.y);

	// 각 매개 변수 u, v의 분자를 구한다.
	float u_numerator = (Dest.Point2.x - Dest.Point1.x) * (Src.Point1.y - Dest.Point1.y) - (Dest.Point2.y - Dest.Point1.y) * (Src.Point1.x - Dest.Point1.x);
	float v_numerator = (Src.Point2.x - Src.Point1.x) * (Src.Point1.y - Dest.Point1.y) - (Src.Point2.y - Src.Point1.y) * (Src.Point1.x - Dest.Point1.x);

	// 분모가 0이 되면 두 선이 평행이다.
	if (Denominator == 0)
	{
		// 평행이라면 두 선이 겹치는지 확인하여 충돌 판단을 한다.
		// 수직일 때,
		if ((Src.Point2.x - Src.Point1.x) == 0)
		{
			float SrcSmallY = Src.Point1.y < Src.Point2.y ? Src.Point1.y : Src.Point2.y;
			float SrcLargeY = Src.Point1.y > Src.Point2.y ? Src.Point1.y : Src.Point2.y;
			float DestSmallY = Dest.Point1.y < Dest.Point2.y ? Dest.Point1.y : Dest.Point2.y;
			float DestLargeY = Dest.Point1.y > Dest.Point2.y ? Dest.Point1.y : Dest.Point2.y;

			if (SrcSmallY > DestLargeY || DestSmallY > SrcLargeY)
				return false;

			else if (SrcSmallY <= DestLargeY && Src.Point1.x == Dest.Point1.x)
			{
				HitPoint.x = Src.Point1.x;
				HitPoint.y = (SrcSmallY + DestLargeY) / 2.f;

				return true;
			}

			else if (DestSmallY <= SrcLargeY && Src.Point1.x == Dest.Point1.x)
			{
				HitPoint.x = Src.Point1.x;
				HitPoint.y = (DestSmallY + SrcLargeY) / 2.f;

				return true;
			}

			else
				return false;
		}

		// 수평일 때,
		else if ((Src.Point2.y - Src.Point1.y) == 0)
		{
			float SrcSmallX = Src.Point1.x < Src.Point2.x ? Src.Point1.x : Src.Point2.x;
			float SrcLargeX = Src.Point1.x > Src.Point2.x ? Src.Point1.x : Src.Point2.x;
			float DestSmallX = Dest.Point1.x < Dest.Point2.x ? Dest.Point1.x : Dest.Point2.x;
			float DestLargeX = Dest.Point1.x > Dest.Point2.x ? Dest.Point1.x : Dest.Point2.x;

			if (SrcSmallX > DestLargeX || DestSmallX > SrcLargeX)
				return false;

			else if (SrcSmallX <= DestLargeX && Src.Point1.y == Dest.Point1.y)
			{
				HitPoint.x = (SrcSmallX + DestLargeX) / 2.f;
				HitPoint.y = Src.Point1.y;

				return true;
			}

			else if (DestSmallX <= SrcLargeX && Src.Point1.y == Dest.Point1.y)
			{
				HitPoint.x = (DestSmallX + SrcLargeX) / 2.f;
				HitPoint.y = Src.Point1.y;

				return true;
			}

			else
				return false;
		}

		// 대각선으로 평행할 때,
		else
		{
			// 일단 이건 패스하는걸로...
		}

		return false;
	}

	// 분자와 분모를 계산하여 u, v를 구한다.
	float u = u_numerator / Denominator;
	float v = v_numerator / Denominator;

	if (u < 0 || u > 1 || v < 0 || v > 1)
		return false;

	HitPoint.x = Src.Point1.x + u * (Src.Point2.x - Src.Point1.x);
	HitPoint.y = Src.Point1.y + v * (Src.Point2.y - Src.Point1.y);

	return true;
}

bool CCollisionManager::CollisionBox2DToSphere2D(Vector2& HitPoint, const Box2DInfo& Src, const Sphere2DInfo& Dest)
{
	// 원의 센터 좌표가 Box의 상하 좌우 경계 사이에 있을 경우 원의 반지름만큼 사각형을 확장하여 충돌하는지 체크
	if ((Src.Left <= Dest.Center.x && Dest.Center.x <= Src.Right) || (Src.Bottom <= Dest.Center.y && Dest.Center.y <= Src.Top))
	{
		Box2DInfo	Info = Src;
		Info.Left -= Dest.Radius;
		Info.Bottom -= Dest.Radius;
		Info.Right += Dest.Radius;
		Info.Top += Dest.Radius;

		if (Info.Left > Dest.Center.x)
			return false;

		else if (Info.Bottom > Dest.Center.y)
			return false;

		else if (Info.Right < Dest.Center.x)
			return false;

		else if (Info.Top < Dest.Center.y)
			return false;

		Box2DInfo	OverlapBox = ConvertBox2DInfo(Dest);

		ComputeHitPoint(HitPoint, Src, OverlapBox);

		return true;
	}

	// 상하 좌우 경계가 아니라면 Box의 4개 꼭지점 좌표와 비교하여 충돌하는지 체크
	Vector2	Pos[4] =
	{
		Vector2(Src.Left, Src.Top),
		Vector2(Src.Right, Src.Top),
		Vector2(Src.Left, Src.Bottom),
		Vector2(Src.Right, Src.Bottom)
	};

	for (int i = 0; i < 4; ++i)
	{
		float Dist = Dest.Center.Distance(Pos[i]);

		if (Dist <= Dest.Radius)
		{
			Box2DInfo	OverlapBox = ConvertBox2DInfo(Dest);

			ComputeHitPoint(HitPoint, Src, OverlapBox);

			return true;
		}
	}

	return false;
}

bool CCollisionManager::CollisionBox2DToOBB2D(Vector2& HitPoint, const Box2DInfo& Src, const OBB2DInfo& Dest)
{
	OBB2DInfo	SrcInfo;
	SrcInfo.Center = Vector2((Src.Left + Src.Right) / 2.f, (Src.Top + Src.Bottom) / 2.f);
	SrcInfo.Axis[AXIS2D_X] = Vector2(1.f, 0.f);
	SrcInfo.Axis[AXIS2D_Y] = Vector2(0.f, 1.f);
	SrcInfo.Length[AXIS2D_X] = (Src.Right - Src.Left) / 2.f;
	SrcInfo.Length[AXIS2D_Y] = (Src.Top - Src.Bottom) / 2.f;

	return CollisionOBB2DToOBB2D(HitPoint, SrcInfo, Dest);
}

bool CCollisionManager::CollisionBox2DToPixel(Vector2& HitPoint, const Box2DInfo& Src, const PixelInfo& Dest)
{
	// 픽셀충돌체를 구성하는 사각형과 충돌처리를 먼저 한다.
	if (!CollisionBox2DToBox2D(HitPoint, Src, Dest.Box2D))
		return false;

	// 두 사각형이 겹쳐지는 영역을 구하고 해당 영역의 픽셀정보를 확인하여 충돌이 되었는지를 판단한다.
	Box2DInfo OverlapInfo = OverlapBox2D(Src, Dest.Box2D);

	// 겹치는 영역의 좌표를 픽셀 이미지의 좌하단 좌표만큼 빼주어서 상대적인 좌표로 변환한다.
	OverlapInfo.Left -= Dest.Box2D.Left;
	OverlapInfo.Bottom -= Dest.Box2D.Bottom;
	OverlapInfo.Right -= Dest.Box2D.Left;
	OverlapInfo.Top -= Dest.Box2D.Bottom;

	float Width = (float)Dest.Width;
	float Height = (float)Dest.Height;

	// 만약 겹치는 영역의 좌표가 변환되었는데 좌하단이 0, 0보다 작거나, 우상단이 픽셀 이미지의 크기보다 크다면 교체한다.
	OverlapInfo.Left = OverlapInfo.Left < 0.f ? 0.f : OverlapInfo.Left;
	OverlapInfo.Bottom = OverlapInfo.Bottom < 0.f ? 0.f : OverlapInfo.Bottom;
	OverlapInfo.Right = OverlapInfo.Right > Width ? Width - 1.f : OverlapInfo.Right;
	OverlapInfo.Top = OverlapInfo.Top > Height ? Height - 1.f : OverlapInfo.Top;

	// Bottom과 Top을 뒤집어서 이미지에 맞춰준다.(이미지는 좌상단이 시작점이기 때문)
	OverlapInfo.Bottom = Height - OverlapInfo.Bottom;
	OverlapInfo.Top = Height - OverlapInfo.Top;

	// 충돌되었는지를 판단할 변수 생성
	bool	Collision = false;

	// Top이 0이 되었으므로 Top부터 Bottom까지 반복
	for (int y = (int)OverlapInfo.Top; y < (int)OverlapInfo.Bottom; ++y)
	{
		// Left부터 Right까지 반복
		for (int x = (int)OverlapInfo.Left; x < (int)OverlapInfo.Right; ++x)
		{
			// Pixel의 정보는 R,G,B,A 순서대로 저장되어있기때문에 Index는 4개씩 띄워가며 구한다
			// 한 줄이 Left부터 Right까지 반복했다면 다음줄의 Index는 픽셀 이미지의 너비 * 4만큼의 Index를 추가한다.
			int	Index = y * (int)Dest.Width * 4 + x * 4;

			// ColorCollisoinType에 따라 충돌 여부를 판단한다.
			switch (Dest.PixelColorCollisionType)
			{
				// 특정 Color를 무시하기로 했다면 해당 Color와 일치한다면 충돌하지 않고, 아니라면 충돌했다고 판단
			case EPixelCollision_Type::Color_Ignore:
				if (Dest.Pixel[Index] == Dest.TypeColor[0] &&
					Dest.Pixel[Index + 1] == Dest.TypeColor[1] &&
					Dest.Pixel[Index + 2] == Dest.TypeColor[2])
					continue;

				Collision = true;
				break;
				// 특정 Color로 충돌하기로 했다면 해당 Color와 일치한다면 충돌했다고 판단하고, 아니라면 충돌하지 않는다.
			case EPixelCollision_Type::Color_Confirm:
				if (Dest.Pixel[Index] == Dest.TypeColor[0] &&
					Dest.Pixel[Index + 1] == Dest.TypeColor[1] &&
					Dest.Pixel[Index + 2] == Dest.TypeColor[2])
					Collision = true;

				else
					continue;
				break;
			}

			// AlphaCollisoinType에 따라 충돌 여부를 판단한다.
			switch (Dest.PixelAlphaCollisionType)
			{
				// 특정 Alpha를 무시하기로 했다면 해당 Alpha와 일치한다면 충돌하지 않고, 아니라면 충돌했다고 판단
			case EPixelCollision_Type::Alpha_Ignore:
				if (Dest.Pixel[Index + 3] == Dest.TypeColor[3])
					continue;

				Collision = true;
				break;
				// 특정 Alpha로 충돌하기로 했다면 해당 Color와 일치한다면 충돌했다고 판단하고, 아니라면 충돌하지 않는다.
			case EPixelCollision_Type::Alpha_Confirm:
				if (Dest.Pixel[Index + 3] == Dest.TypeColor[3])
					Collision = true;

				else
					continue;
				break;
			}

			// 이미 충돌되었다면 반복문을 빠져나간다.
			if (Collision)
				break;
		}

		// 이미 충돌되었다면 반복문을 빠져나간다.
		if (Collision)
			break;
	}

	ComputeHitPoint(HitPoint, Src, Dest.Box2D);

	return Collision;
}

bool CCollisionManager::CollisionSphere2DToOBB2D(Vector2& HitPoint, const Sphere2DInfo& Src, const OBB2DInfo& Dest)
{
	Vector2	CenterLine = Src.Center - Dest.Center;

	float CenterProjDist = CenterLine.Length();

	Vector2	Axis = CenterLine;
	Axis.Normalize();

	float SrcDist, DestDist;

	SrcDist = Src.Radius;
	DestDist = abs(Axis.Dot(Dest.Axis[AXIS2D_X]) * Dest.Length[AXIS2D_X]) +	abs(Axis.Dot(Dest.Axis[AXIS2D_Y]) * Dest.Length[AXIS2D_Y]);

	if (CenterProjDist > SrcDist + DestDist)
		return false;

	Axis = Dest.Axis[AXIS2D_X];

	CenterProjDist = abs(Axis.Dot(CenterLine));

	DestDist = Dest.Length[AXIS2D_X];

	if (CenterProjDist > SrcDist + DestDist)
		return false;

	Axis = Dest.Axis[AXIS2D_Y];

	CenterProjDist = abs(Axis.Dot(CenterLine));

	DestDist = Dest.Length[AXIS2D_Y];

	if (CenterProjDist > SrcDist + DestDist)
		return false;

	Box2DInfo	SrcInfo, DestInfo;
	SrcInfo = ConvertBox2DInfo(Src);
	DestInfo = ConvertBox2DInfo(Dest);

	ComputeHitPoint(HitPoint, SrcInfo, DestInfo);

	return true;
}

bool CCollisionManager::CollisionSphere2DToPixel(Vector2& HitPoint, const Sphere2DInfo& Src, const PixelInfo& Dest)
{
	// 픽셀충돌체를 구성하는 사각형과 충돌처리를 먼저 한다.
	if (!CollisionBox2DToSphere2D(HitPoint, Dest.Box2D, Src))
		return false;

	// 두 사각형이 겹쳐지는 영역을 구하고 해당 영역의 픽셀정보를 확인하여 충돌이 되었는지를 판단한다.
	Box2DInfo OverlapInfo = OverlapBox2D(Dest.Box2D, Src);

	// 겹치는 영역의 좌표를 픽셀 이미지의 좌하단 좌표만큼 빼주어서 상대적인 좌표로 변환한다.
	OverlapInfo.Left -= Dest.Box2D.Left;
	OverlapInfo.Bottom -= Dest.Box2D.Bottom;
	OverlapInfo.Right -= Dest.Box2D.Left;
	OverlapInfo.Top -= Dest.Box2D.Bottom;

	float Width = (float)Dest.Width;
	float Height = (float)Dest.Height;

	// 만약 겹치는 영역의 좌표가 변환되었는데 좌하단이 0, 0보다 작거나, 우상단이 픽셀 이미지의 크기보다 크다면 교체한다.
	OverlapInfo.Left = OverlapInfo.Left < 0.f ? 0.f : OverlapInfo.Left;
	OverlapInfo.Bottom = OverlapInfo.Bottom < 0.f ? 0.f : OverlapInfo.Bottom;
	OverlapInfo.Right = OverlapInfo.Right > Width ? Width - 1.f : OverlapInfo.Right;
	OverlapInfo.Top = OverlapInfo.Top > Height ? Height - 1.f : OverlapInfo.Top;

	// Bottom과 Top을 뒤집어서 이미지에 맞춰준다.
	OverlapInfo.Bottom = Height - OverlapInfo.Bottom;
	OverlapInfo.Top = Height - OverlapInfo.Top;

	bool	Collision = false;

	for (int y = (int)OverlapInfo.Top; y < (int)OverlapInfo.Bottom; ++y)
	{
		for (int x = (int)OverlapInfo.Left; x < (int)OverlapInfo.Right; ++x)
		{
			int	Index = y * (int)Dest.Width * 4 + x * 4;

			// 픽셀의 인덱스를 이용하여 월드공간으로 변환해준다.
			Vector2	PixelWorldPos = Vector2(Dest.Box2D.Left, Dest.Box2D.Bottom) + Vector2((float)x, (float)Height - (float)y);

			// 해당 좌표가 원과 충돌하는지 판단한다.(원을 감싸는 사각형과 충돌했더라도 원과는 충돌하지 않았을 수도 있기 때문)
			if (!CollisionPointToSphere2D(HitPoint, PixelWorldPos, Src))
				continue;

			switch (Dest.PixelColorCollisionType)
			{
			case EPixelCollision_Type::Color_Ignore:
				if (Dest.Pixel[Index] == Dest.TypeColor[0] &&
					Dest.Pixel[Index + 1] == Dest.TypeColor[1] &&
					Dest.Pixel[Index + 2] == Dest.TypeColor[2])
					continue;

				Collision = true;
				break;
			case EPixelCollision_Type::Color_Confirm:
				if (Dest.Pixel[Index] == Dest.TypeColor[0] &&
					Dest.Pixel[Index + 1] == Dest.TypeColor[1] &&
					Dest.Pixel[Index + 2] == Dest.TypeColor[2])
					Collision = true;

				else
					continue;
				break;
			}

			switch (Dest.PixelAlphaCollisionType)
			{
			case EPixelCollision_Type::Alpha_Ignore:
				if (Dest.Pixel[Index + 3] == Dest.TypeColor[3])
					continue;

				Collision = true;
				break;
			case EPixelCollision_Type::Alpha_Confirm:
				if (Dest.Pixel[Index + 3] == Dest.TypeColor[3])
					Collision = true;

				else
					continue;
				break;
			}

			if (Collision)
				break;
		}

		if (Collision)
			break;
	}

	ComputeHitPoint(HitPoint, OverlapInfo, Dest.Box2D);

	return Collision;
}

bool CCollisionManager::CollisionOBB2DToPixel(Vector2& HitPoint, const OBB2DInfo& Src, const PixelInfo& Dest)
{
	// 픽셀충돌체를 구성하는 사각형과 충돌처리를 먼저 한다.
	if (!CollisionBox2DToOBB2D(HitPoint, Dest.Box2D, Src))
		return false;

	// 두 사각형이 겹쳐지는 영역을 구하고 해당 영역의 픽셀정보를 확인하여 충돌이 되었는지를 판단한다.
	Box2DInfo OverlapInfo = OverlapBox2D(Dest.Box2D, Src);

	OverlapInfo.Left -= Dest.Box2D.Left;
	OverlapInfo.Bottom -= Dest.Box2D.Bottom;
	OverlapInfo.Right -= Dest.Box2D.Left;
	OverlapInfo.Top -= Dest.Box2D.Bottom;

	float Width = (float)Dest.Width;
	float Height = (float)Dest.Height;

	OverlapInfo.Left = OverlapInfo.Left < 0.f ? 0.f : OverlapInfo.Left;
	OverlapInfo.Bottom = OverlapInfo.Bottom < 0.f ? 0.f : OverlapInfo.Bottom;

	OverlapInfo.Right = OverlapInfo.Right > Width ? Width - 1.f : OverlapInfo.Right;
	OverlapInfo.Top = OverlapInfo.Top > Height ? Height - 1.f : OverlapInfo.Top;

	// Bottom과 Top을 뒤집어서 이미지에 맞춰준다.
	OverlapInfo.Bottom = Height - OverlapInfo.Bottom;
	OverlapInfo.Top = Height - OverlapInfo.Top;

	bool	Collision = false;

	for (int y = (int)OverlapInfo.Top; y < (int)OverlapInfo.Bottom; ++y)
	{
		for (int x = (int)OverlapInfo.Left; x < (int)OverlapInfo.Right; ++x)
		{
			int	Index = y * (int)Dest.Width * 4 + x * 4;

			// 픽셀의 인덱스를 이용하여 월드공간으로 변환해준다.
			Vector2	PixelWorldPos = Vector2(Dest.Box2D.Left, Dest.Box2D.Bottom) + Vector2((float)x, (float)Height - (float)y);

			// 해당 좌표가 OBB과 충돌하는지 판단한다.(OBB를 감싸는 사각형과 충돌했더라도 OBB와는 충돌하지 않았을 수도 있기 때문)
			if (!CollisionPointToOBB2D(HitPoint, PixelWorldPos, Src))
				continue;

			switch (Dest.PixelColorCollisionType)
			{
			case EPixelCollision_Type::Color_Ignore:
				if (Dest.Pixel[Index] == Dest.TypeColor[0] &&
					Dest.Pixel[Index + 1] == Dest.TypeColor[1] &&
					Dest.Pixel[Index + 2] == Dest.TypeColor[2])
					continue;

				Collision = true;
				break;
			case EPixelCollision_Type::Color_Confirm:
				if (Dest.Pixel[Index] == Dest.TypeColor[0] &&
					Dest.Pixel[Index + 1] == Dest.TypeColor[1] &&
					Dest.Pixel[Index + 2] == Dest.TypeColor[2])
					Collision = true;

				else
					continue;
				break;
			}

			switch (Dest.PixelAlphaCollisionType)
			{
			case EPixelCollision_Type::Alpha_Ignore:
				if (Dest.Pixel[Index + 3] == Dest.TypeColor[3])
					continue;

				Collision = true;
				break;
			case EPixelCollision_Type::Alpha_Confirm:
				if (Dest.Pixel[Index + 3] == Dest.TypeColor[3])
					Collision = true;

				else
					continue;
				break;
			}

			if (Collision)
				break;
		}

		if (Collision)
			break;
	}

	ComputeHitPoint(HitPoint, OverlapInfo, Dest.Box2D);

	return Collision;
}

bool CCollisionManager::CollisionPointToBox2D(Vector2& HitPoint, const Vector2& Src, const Box2DInfo& Dest)
{
	if (Src.x < Dest.Left)
		return false;

	else if (Src.x > Dest.Right)
		return false;

	else if (Src.y < Dest.Bottom)
		return false;

	else if (Src.y > Dest.Top)
		return false;

	HitPoint = Src;

	return true;
}

bool CCollisionManager::CollisionPointToSphere2D(Vector2& HitPoint, const Vector2& Src, const Sphere2DInfo& Dest)
{
	bool result = Src.Distance(Dest.Center) <= Dest.Radius;

	if (result)
		HitPoint = Src;

	return result;
}

bool CCollisionManager::CollisionPointToOBB2D(Vector2& HitPoint, const Vector2& Src, const OBB2DInfo& Dest)
{
	Vector2	CenterLine = Src - Dest.Center;

	Vector2	Axis = Dest.Axis[AXIS2D_X];

	float CenterProjDist = abs(Axis.Dot(CenterLine));

	if (CenterProjDist > Dest.Length[AXIS2D_X])
		return false;

	Axis = Dest.Axis[AXIS2D_Y];

	CenterProjDist = abs(Axis.Dot(CenterLine));

	if (CenterProjDist > Dest.Length[AXIS2D_Y])
		return false;

	HitPoint = Src;

	return true;
}

bool CCollisionManager::CollisionPointToPixel(Vector2& HitPoint, const Vector2& Src, const PixelInfo& Dest)
{
	// 픽셀충돌체를 구성하는 사각형과 충돌처리를 먼저 한다.
	if (!CollisionPointToBox2D(HitPoint, Src, Dest.Box2D))
		return false;

	Vector2	ConvertSrc = Src;

	ConvertSrc.x -= Dest.Box2D.Left;
	ConvertSrc.y -= Dest.Box2D.Bottom;

	ConvertSrc.y = Dest.Height - ConvertSrc.y;

	bool	Collision = false;

	int	Index = (int)ConvertSrc.y * (int)Dest.Width * 4 + (int)ConvertSrc.x * 4;

	switch (Dest.PixelColorCollisionType)
	{
	case EPixelCollision_Type::Color_Ignore:
		if (Dest.Pixel[Index] == Dest.TypeColor[0] &&
			Dest.Pixel[Index + 1] == Dest.TypeColor[1] &&
			Dest.Pixel[Index + 2] == Dest.TypeColor[2])
			Collision = false;

		else
			Collision = true;
		break;
	case EPixelCollision_Type::Color_Confirm:
		if (Dest.Pixel[Index] == Dest.TypeColor[0] &&
			Dest.Pixel[Index + 1] == Dest.TypeColor[1] &&
			Dest.Pixel[Index + 2] == Dest.TypeColor[2])
			Collision = true;

		else
			Collision = false;
		break;
	}

	switch (Dest.PixelAlphaCollisionType)
	{
	case EPixelCollision_Type::Alpha_Ignore:
		if (Dest.Pixel[Index + 3] == Dest.TypeColor[3])
			Collision = false;

		else
			Collision = true;
		break;
	case EPixelCollision_Type::Alpha_Confirm:
		if (Dest.Pixel[Index + 3] == Dest.TypeColor[3])
			Collision = true;

		else
			Collision = false;
		break;
	}

	HitPoint = Src;

	return Collision;
}

bool CCollisionManager::CollisionPointToLine2D(Vector2& HitPoint, const Vector2& Src, const Line2DInfo& Dest)
{
	float Distance1 = Src.Distance(Dest.Point1);
	float Distance2 = Src.Distance(Dest.Point2);

	float LineLength = Dest.Point1.Distance(Dest.Point2);

	// 너무 딱 맞추니까 충돌이 일어나서 일단 여유 값으로 0.1만큼 추가했음
	if (Distance1 + Distance2 > LineLength + 0.1f)
	{
		return false;
	}

	HitPoint = Src;

	return true;
}

bool CCollisionManager::CollisionBox2DToLine2D(Vector2& HitPoint, const Box2DInfo& Src, const Line2DInfo& Dest)
{
	//// 사각형의 네 점을 이용하여 선 4개를 만든다.
	Vector2 LT = Vector2(Src.Left, Src.Top);
	Vector2 RT = Vector2(Src.Right, Src.Top);
	Vector2 LB = Vector2(Src.Left, Src.Bottom);
	Vector2 RB = Vector2(Src.Right, Src.Bottom);

	Line2DInfo TopInfo;
	TopInfo.Point1 = LT;
	TopInfo.Point2 = RT;

	Line2DInfo RightInfo;
	RightInfo.Point1 = RT;
	RightInfo.Point2 = RB;

	Line2DInfo BottomInfo;
	BottomInfo.Point1 = LB;
	BottomInfo.Point2 = RB;

	Line2DInfo LeftInfo;
	LeftInfo.Point1 = LT;
	LeftInfo.Point2 = LB;

	bool Result = false;

	if (CollisionLine2DToLine2D(HitPoint, TopInfo, Dest))
		Result = true;

	else if (!Result && CollisionLine2DToLine2D(HitPoint, RightInfo, Dest))
		Result = true;

	else if (!Result && CollisionLine2DToLine2D(HitPoint, BottomInfo, Dest))
		Result = true;

	else if (!Result && CollisionLine2DToLine2D(HitPoint, LeftInfo, Dest))
		Result = true;
	
	return Result;
}

bool CCollisionManager::CollisionSphere2DToLine2D(Vector2& HitPoint, const Sphere2DInfo& Src, const Line2DInfo& Dest)
{
	return false;
}

bool CCollisionManager::CollisionOBB2DToLine2D(Vector2& HitPoint, const OBB2DInfo& Src, const Line2DInfo& Dest)
{
	return false;
}

bool CCollisionManager::CollisionPixelToLine2D(Vector2& HitPoint, const PixelInfo& Src, const Line2DInfo& Dest)
{
	return false;
}

Box2DInfo CCollisionManager::ConvertBox2DInfo(const Sphere2DInfo& Info)
{
	Box2DInfo	result;

	result.Left = Info.Center.x - Info.Radius;
	result.Bottom = Info.Center.y - Info.Radius;
	result.Right = Info.Center.x + Info.Radius;
	result.Top = Info.Center.y + Info.Radius;

	return result;
}

Box2DInfo CCollisionManager::ConvertBox2DInfo(const OBB2DInfo& Info)
{
	Box2DInfo	result;

	Vector2	Pos[4];

	Pos[0] = Info.Center - Info.Axis[AXIS2D_X] * Info.Length[AXIS2D_X] + Info.Axis[AXIS2D_Y] * Info.Length[AXIS2D_Y];

	Pos[1] = Info.Center + Info.Axis[AXIS2D_X] * Info.Length[AXIS2D_X] + Info.Axis[AXIS2D_Y] * Info.Length[AXIS2D_Y];

	Pos[2] = Info.Center - Info.Axis[AXIS2D_X] * Info.Length[AXIS2D_X] - Info.Axis[AXIS2D_Y] * Info.Length[AXIS2D_Y];

	Pos[3] = Info.Center + Info.Axis[AXIS2D_X] * Info.Length[AXIS2D_X] - Info.Axis[AXIS2D_Y] * Info.Length[AXIS2D_Y];

	result.Left = Pos[0].x;
	result.Bottom = Pos[0].y;

	result.Right = Pos[0].x;
	result.Top = Pos[0].y;

	for (int i = 1; i < 4; ++i)
	{
		result.Left = result.Left > Pos[i].x ? Pos[i].x : result.Left;
		result.Bottom = result.Bottom > Pos[i].y ? Pos[i].y : result.Bottom;
		result.Right = result.Right < Pos[i].x ? Pos[i].x : result.Right;
		result.Top = result.Top < Pos[i].y ? Pos[i].y : result.Top;
	}

	return result;
}

Box2DInfo CCollisionManager::OverlapBox2D(const Box2DInfo& Src, const Box2DInfo& Dest)
{
	Box2DInfo	Info;

	Info.Left = Src.Left > Dest.Left ? Src.Left : Dest.Left;
	Info.Bottom = Src.Bottom > Dest.Bottom ? Src.Bottom : Dest.Bottom;
	Info.Right = Src.Right < Dest.Right ? Src.Right : Dest.Right;
	Info.Top = Src.Top < Dest.Top ? Src.Top : Dest.Top;

	return Info;
}

Box2DInfo CCollisionManager::OverlapBox2D(const Box2DInfo& Src, const Sphere2DInfo& Dest)
{
	Box2DInfo	Info, DestInfo;

	DestInfo = ConvertBox2DInfo(Dest);

	Info.Left = Src.Left > DestInfo.Left ? Src.Left : DestInfo.Left;
	Info.Bottom = Src.Bottom > DestInfo.Bottom ? Src.Bottom : DestInfo.Bottom;
	Info.Right = Src.Right < DestInfo.Right ? Src.Right : DestInfo.Right;
	Info.Top = Src.Top < DestInfo.Top ? Src.Top : DestInfo.Top;

	return Info;
}

Box2DInfo CCollisionManager::OverlapBox2D(const Box2DInfo& Src, const OBB2DInfo& Dest)
{
	Box2DInfo	Info, DestInfo;

	DestInfo = ConvertBox2DInfo(Dest);

	Info.Left = Src.Left > DestInfo.Left ? Src.Left : DestInfo.Left;
	Info.Bottom = Src.Bottom > DestInfo.Bottom ? Src.Bottom : DestInfo.Bottom;
	Info.Right = Src.Right < DestInfo.Right ? Src.Right : DestInfo.Right;
	Info.Top = Src.Top < DestInfo.Top ? Src.Top : DestInfo.Top;

	return Info;
}

void CCollisionManager::ComputeHitPoint(Vector2& HitPoint, const Box2DInfo& Src, const Box2DInfo& Dest)
{
	float Left = Src.Left > Dest.Left ? Src.Left : Dest.Left;
	float Bottom = Src.Bottom > Dest.Bottom ? Src.Bottom : Dest.Bottom;
	float Right = Src.Right < Dest.Right ? Src.Right : Dest.Right;
	float Top = Src.Top < Dest.Top ? Src.Top : Dest.Top;

	HitPoint.x = (Left + Right) / 2.f;
	HitPoint.y = (Top + Bottom) / 2.f;
}
