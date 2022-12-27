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
	// �� �ȼ��浹ü�� �����ϴ� �簢���� �浹ó���� ���� �Ѵ�.
	if (!CollisionBox2DToBox2D(HitPoint, Src.Box2D, Dest.Box2D))
		return false;

	// �� �簢���� �������� ������ ���ϰ� �ش� ������ �ȼ������� Ȯ���Ͽ� �浹�� �Ǿ������� �Ǵ��Ѵ�.
	Box2DInfo OverlapInfo = OverlapBox2D(Src.Box2D, Dest.Box2D);

	// ��ġ�� ������ ��ǥ�� �ȼ� �̹����� ���ϴ� ��ǥ��ŭ ���־ ������� ��ǥ�� ��ȯ�Ѵ�.
	OverlapInfo.Left -= Dest.Box2D.Left;
	OverlapInfo.Bottom -= Dest.Box2D.Bottom;
	OverlapInfo.Right -= Dest.Box2D.Left;
	OverlapInfo.Top -= Dest.Box2D.Bottom;

	float Width = (float)Dest.Width;
	float Height = (float)Dest.Height;

	// ���� ��ġ�� ������ ��ǥ�� ��ȯ�Ǿ��µ� ���ϴ��� 0, 0���� �۰ų�, ������ �ȼ� �̹����� ũ�⺸�� ũ�ٸ� ��ü�Ѵ�.
	OverlapInfo.Left = OverlapInfo.Left < 0.f ? 0.f : OverlapInfo.Left;
	OverlapInfo.Bottom = OverlapInfo.Bottom < 0.f ? 0.f : OverlapInfo.Bottom;
	OverlapInfo.Right = OverlapInfo.Right > Width ? Width - 1.f : OverlapInfo.Right;
	OverlapInfo.Top = OverlapInfo.Top > Height ? Height - 1.f : OverlapInfo.Top;

	// Bottom�� Top�� ����� �̹����� �����ش�.(�̹����� �»���� �������̱� ����)
	OverlapInfo.Bottom = Height - OverlapInfo.Bottom;
	OverlapInfo.Top = Height - OverlapInfo.Top;

	// �浹�Ǿ������� �Ǵ��� ���� ����
	bool	Collision = false;

	// Top�� 0�� �Ǿ����Ƿ� Top���� Bottom���� �ݺ�
	for (int y = (int)OverlapInfo.Top; y < (int)OverlapInfo.Bottom; ++y)
	{
		// Left���� Right���� �ݺ�
		for (int x = (int)OverlapInfo.Left; x < (int)OverlapInfo.Right; ++x)
		{
			// Pixel�� ������ R,G,B,A ������� ����Ǿ��ֱ⶧���� Index�� 4���� ������� ���Ѵ�
			// �� ���� Left���� Right���� �ݺ��ߴٸ� �������� Index�� �ȼ� �̹����� �ʺ� * 4��ŭ�� Index�� �߰��Ѵ�.
			int SrcIndex = y * (int)Src.Width * 4 + x * 4;
			int	DestIndex = y * (int)Dest.Width * 4 + x * 4;

			// ColorCollisoinType�� ���� �浹 ���θ� �Ǵ��Ѵ�.
			switch (Dest.PixelColorCollisionType)
			{
				// Ư�� Color�� �����ϱ�� �ߴٸ� �ش� Color�� ��ġ�Ѵٸ� �浹���� �ʰ�, �ƴ϶�� �浹�ߴٰ� �Ǵ�
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
				// Ư�� Color�� �浹�ϱ�� �ߴٸ� �ش� Color�� ��ġ�Ѵٸ� �浹�ߴٰ� �Ǵ��ϰ�, �ƴ϶�� �浹���� �ʴ´�.
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

			// AlphaCollisoinType�� ���� �浹 ���θ� �Ǵ��Ѵ�.
			switch (Dest.PixelAlphaCollisionType)
			{
				// Ư�� Alpha�� �����ϱ�� �ߴٸ� �ش� Alpha�� ��ġ�Ѵٸ� �浹���� �ʰ�, �ƴ϶�� �浹�ߴٰ� �Ǵ�
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
				// Ư�� Alpha�� �浹�ϱ�� �ߴٸ� �ش� Color�� ��ġ�Ѵٸ� �浹�ߴٰ� �Ǵ��ϰ�, �ƴ϶�� �浹���� �ʴ´�.
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

			// �̹� �浹�Ǿ��ٸ� �ݺ����� ����������.
			if (Collision)
				break;
		}

		// �̹� �浹�Ǿ��ٸ� �ݺ����� ����������.
		if (Collision)
			break;
	}

	ComputeHitPoint(HitPoint, Src.Box2D, Dest.Box2D);

	return Collision;
}

bool CCollisionManager::CollisionLine2DToLine2D(Vector2& HitPoint, const Line2DInfo& Src, const Line2DInfo& Dest)
{
	// �Ű� ���� u, v �� ���ϱ� ���� �и� ���Ѵ�.
	float Denominator = (Src.Point2.x - Src.Point1.x) * (Dest.Point2.y - Dest.Point1.y) - (Dest.Point2.x - Dest.Point1.x) * (Src.Point2.y - Src.Point1.y);

	// �� �Ű� ���� u, v�� ���ڸ� ���Ѵ�.
	float u_numerator = (Dest.Point2.x - Dest.Point1.x) * (Src.Point1.y - Dest.Point1.y) - (Dest.Point2.y - Dest.Point1.y) * (Src.Point1.x - Dest.Point1.x);
	float v_numerator = (Src.Point2.x - Src.Point1.x) * (Src.Point1.y - Dest.Point1.y) - (Src.Point2.y - Src.Point1.y) * (Src.Point1.x - Dest.Point1.x);

	// �и� 0�� �Ǹ� �� ���� �����̴�.
	if (Denominator == 0)
	{
		// �����̶�� �� ���� ��ġ���� Ȯ���Ͽ� �浹 �Ǵ��� �Ѵ�.
		// ������ ��,
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

		// ������ ��,
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

		// �밢������ ������ ��,
		else
		{
			// �ϴ� �̰� �н��ϴ°ɷ�...
		}

		return false;
	}

	// ���ڿ� �и� ����Ͽ� u, v�� ���Ѵ�.
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
	// ���� ���� ��ǥ�� Box�� ���� �¿� ��� ���̿� ���� ��� ���� ��������ŭ �簢���� Ȯ���Ͽ� �浹�ϴ��� üũ
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

	// ���� �¿� ��谡 �ƴ϶�� Box�� 4�� ������ ��ǥ�� ���Ͽ� �浹�ϴ��� üũ
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
	// �ȼ��浹ü�� �����ϴ� �簢���� �浹ó���� ���� �Ѵ�.
	if (!CollisionBox2DToBox2D(HitPoint, Src, Dest.Box2D))
		return false;

	// �� �簢���� �������� ������ ���ϰ� �ش� ������ �ȼ������� Ȯ���Ͽ� �浹�� �Ǿ������� �Ǵ��Ѵ�.
	Box2DInfo OverlapInfo = OverlapBox2D(Src, Dest.Box2D);

	// ��ġ�� ������ ��ǥ�� �ȼ� �̹����� ���ϴ� ��ǥ��ŭ ���־ ������� ��ǥ�� ��ȯ�Ѵ�.
	OverlapInfo.Left -= Dest.Box2D.Left;
	OverlapInfo.Bottom -= Dest.Box2D.Bottom;
	OverlapInfo.Right -= Dest.Box2D.Left;
	OverlapInfo.Top -= Dest.Box2D.Bottom;

	float Width = (float)Dest.Width;
	float Height = (float)Dest.Height;

	// ���� ��ġ�� ������ ��ǥ�� ��ȯ�Ǿ��µ� ���ϴ��� 0, 0���� �۰ų�, ������ �ȼ� �̹����� ũ�⺸�� ũ�ٸ� ��ü�Ѵ�.
	OverlapInfo.Left = OverlapInfo.Left < 0.f ? 0.f : OverlapInfo.Left;
	OverlapInfo.Bottom = OverlapInfo.Bottom < 0.f ? 0.f : OverlapInfo.Bottom;
	OverlapInfo.Right = OverlapInfo.Right > Width ? Width - 1.f : OverlapInfo.Right;
	OverlapInfo.Top = OverlapInfo.Top > Height ? Height - 1.f : OverlapInfo.Top;

	// Bottom�� Top�� ����� �̹����� �����ش�.(�̹����� �»���� �������̱� ����)
	OverlapInfo.Bottom = Height - OverlapInfo.Bottom;
	OverlapInfo.Top = Height - OverlapInfo.Top;

	// �浹�Ǿ������� �Ǵ��� ���� ����
	bool	Collision = false;

	// Top�� 0�� �Ǿ����Ƿ� Top���� Bottom���� �ݺ�
	for (int y = (int)OverlapInfo.Top; y < (int)OverlapInfo.Bottom; ++y)
	{
		// Left���� Right���� �ݺ�
		for (int x = (int)OverlapInfo.Left; x < (int)OverlapInfo.Right; ++x)
		{
			// Pixel�� ������ R,G,B,A ������� ����Ǿ��ֱ⶧���� Index�� 4���� ������� ���Ѵ�
			// �� ���� Left���� Right���� �ݺ��ߴٸ� �������� Index�� �ȼ� �̹����� �ʺ� * 4��ŭ�� Index�� �߰��Ѵ�.
			int	Index = y * (int)Dest.Width * 4 + x * 4;

			// ColorCollisoinType�� ���� �浹 ���θ� �Ǵ��Ѵ�.
			switch (Dest.PixelColorCollisionType)
			{
				// Ư�� Color�� �����ϱ�� �ߴٸ� �ش� Color�� ��ġ�Ѵٸ� �浹���� �ʰ�, �ƴ϶�� �浹�ߴٰ� �Ǵ�
			case EPixelCollision_Type::Color_Ignore:
				if (Dest.Pixel[Index] == Dest.TypeColor[0] &&
					Dest.Pixel[Index + 1] == Dest.TypeColor[1] &&
					Dest.Pixel[Index + 2] == Dest.TypeColor[2])
					continue;

				Collision = true;
				break;
				// Ư�� Color�� �浹�ϱ�� �ߴٸ� �ش� Color�� ��ġ�Ѵٸ� �浹�ߴٰ� �Ǵ��ϰ�, �ƴ϶�� �浹���� �ʴ´�.
			case EPixelCollision_Type::Color_Confirm:
				if (Dest.Pixel[Index] == Dest.TypeColor[0] &&
					Dest.Pixel[Index + 1] == Dest.TypeColor[1] &&
					Dest.Pixel[Index + 2] == Dest.TypeColor[2])
					Collision = true;

				else
					continue;
				break;
			}

			// AlphaCollisoinType�� ���� �浹 ���θ� �Ǵ��Ѵ�.
			switch (Dest.PixelAlphaCollisionType)
			{
				// Ư�� Alpha�� �����ϱ�� �ߴٸ� �ش� Alpha�� ��ġ�Ѵٸ� �浹���� �ʰ�, �ƴ϶�� �浹�ߴٰ� �Ǵ�
			case EPixelCollision_Type::Alpha_Ignore:
				if (Dest.Pixel[Index + 3] == Dest.TypeColor[3])
					continue;

				Collision = true;
				break;
				// Ư�� Alpha�� �浹�ϱ�� �ߴٸ� �ش� Color�� ��ġ�Ѵٸ� �浹�ߴٰ� �Ǵ��ϰ�, �ƴ϶�� �浹���� �ʴ´�.
			case EPixelCollision_Type::Alpha_Confirm:
				if (Dest.Pixel[Index + 3] == Dest.TypeColor[3])
					Collision = true;

				else
					continue;
				break;
			}

			// �̹� �浹�Ǿ��ٸ� �ݺ����� ����������.
			if (Collision)
				break;
		}

		// �̹� �浹�Ǿ��ٸ� �ݺ����� ����������.
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
	// �ȼ��浹ü�� �����ϴ� �簢���� �浹ó���� ���� �Ѵ�.
	if (!CollisionBox2DToSphere2D(HitPoint, Dest.Box2D, Src))
		return false;

	// �� �簢���� �������� ������ ���ϰ� �ش� ������ �ȼ������� Ȯ���Ͽ� �浹�� �Ǿ������� �Ǵ��Ѵ�.
	Box2DInfo OverlapInfo = OverlapBox2D(Dest.Box2D, Src);

	// ��ġ�� ������ ��ǥ�� �ȼ� �̹����� ���ϴ� ��ǥ��ŭ ���־ ������� ��ǥ�� ��ȯ�Ѵ�.
	OverlapInfo.Left -= Dest.Box2D.Left;
	OverlapInfo.Bottom -= Dest.Box2D.Bottom;
	OverlapInfo.Right -= Dest.Box2D.Left;
	OverlapInfo.Top -= Dest.Box2D.Bottom;

	float Width = (float)Dest.Width;
	float Height = (float)Dest.Height;

	// ���� ��ġ�� ������ ��ǥ�� ��ȯ�Ǿ��µ� ���ϴ��� 0, 0���� �۰ų�, ������ �ȼ� �̹����� ũ�⺸�� ũ�ٸ� ��ü�Ѵ�.
	OverlapInfo.Left = OverlapInfo.Left < 0.f ? 0.f : OverlapInfo.Left;
	OverlapInfo.Bottom = OverlapInfo.Bottom < 0.f ? 0.f : OverlapInfo.Bottom;
	OverlapInfo.Right = OverlapInfo.Right > Width ? Width - 1.f : OverlapInfo.Right;
	OverlapInfo.Top = OverlapInfo.Top > Height ? Height - 1.f : OverlapInfo.Top;

	// Bottom�� Top�� ����� �̹����� �����ش�.
	OverlapInfo.Bottom = Height - OverlapInfo.Bottom;
	OverlapInfo.Top = Height - OverlapInfo.Top;

	bool	Collision = false;

	for (int y = (int)OverlapInfo.Top; y < (int)OverlapInfo.Bottom; ++y)
	{
		for (int x = (int)OverlapInfo.Left; x < (int)OverlapInfo.Right; ++x)
		{
			int	Index = y * (int)Dest.Width * 4 + x * 4;

			// �ȼ��� �ε����� �̿��Ͽ� ����������� ��ȯ���ش�.
			Vector2	PixelWorldPos = Vector2(Dest.Box2D.Left, Dest.Box2D.Bottom) + Vector2((float)x, (float)Height - (float)y);

			// �ش� ��ǥ�� ���� �浹�ϴ��� �Ǵ��Ѵ�.(���� ���δ� �簢���� �浹�ߴ��� ������ �浹���� �ʾ��� ���� �ֱ� ����)
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
	// �ȼ��浹ü�� �����ϴ� �簢���� �浹ó���� ���� �Ѵ�.
	if (!CollisionBox2DToOBB2D(HitPoint, Dest.Box2D, Src))
		return false;

	// �� �簢���� �������� ������ ���ϰ� �ش� ������ �ȼ������� Ȯ���Ͽ� �浹�� �Ǿ������� �Ǵ��Ѵ�.
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

	// Bottom�� Top�� ����� �̹����� �����ش�.
	OverlapInfo.Bottom = Height - OverlapInfo.Bottom;
	OverlapInfo.Top = Height - OverlapInfo.Top;

	bool	Collision = false;

	for (int y = (int)OverlapInfo.Top; y < (int)OverlapInfo.Bottom; ++y)
	{
		for (int x = (int)OverlapInfo.Left; x < (int)OverlapInfo.Right; ++x)
		{
			int	Index = y * (int)Dest.Width * 4 + x * 4;

			// �ȼ��� �ε����� �̿��Ͽ� ����������� ��ȯ���ش�.
			Vector2	PixelWorldPos = Vector2(Dest.Box2D.Left, Dest.Box2D.Bottom) + Vector2((float)x, (float)Height - (float)y);

			// �ش� ��ǥ�� OBB�� �浹�ϴ��� �Ǵ��Ѵ�.(OBB�� ���δ� �簢���� �浹�ߴ��� OBB�ʹ� �浹���� �ʾ��� ���� �ֱ� ����)
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
	// �ȼ��浹ü�� �����ϴ� �簢���� �浹ó���� ���� �Ѵ�.
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

	// �ʹ� �� ���ߴϱ� �浹�� �Ͼ�� �ϴ� ���� ������ 0.1��ŭ �߰�����
	if (Distance1 + Distance2 > LineLength + 0.1f)
	{
		return false;
	}

	HitPoint = Src;

	return true;
}

bool CCollisionManager::CollisionBox2DToLine2D(Vector2& HitPoint, const Box2DInfo& Src, const Line2DInfo& Dest)
{
	//// �簢���� �� ���� �̿��Ͽ� �� 4���� �����.
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
