#include "ColliderLine2D.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/CameraManager.h"
#include "../Render/RenderManager.h"
#include "../Resource/Material/Material.h"
#include "../Engine.h"
#include "../Resource/ResourceManager.h"
#include "CameraComponent.h"
#include "../Resource/Shader/ColliderLine2DConstantBuffer.h"
#include "../CollisionManager.h"
#include "ColliderBox2D.h"
#include "ColliderSphere2D.h"
#include "ColliderOBB2D.h"
#include "ColliderPixel.h"

CColliderLine2D::CColliderLine2D()
{
	SetTypeID<CColliderLine2D>();

	m_ComponentTypeName = "ColliderLine2D";
	m_Collider2DType = ECollider2D_Type::Line2D;
}

CColliderLine2D::CColliderLine2D(const CColliderLine2D& component) :
	CCollider2D(component)
{
	m_RelativeDestPoint = component.m_RelativeDestPoint;
}

CColliderLine2D::~CColliderLine2D()
{
}

void CColliderLine2D::SetRelativeDestPoint(const Vector2& Point)
{
	m_RelativeDestPoint = Point;
}

void CColliderLine2D::SetRelativeDestPoint(float x, float y)
{
	m_RelativeDestPoint.x = x;
	m_RelativeDestPoint.y = y;
}

void CColliderLine2D::Start()
{
	CCollider2D::Start();
}

bool CColliderLine2D::Init()
{
	if (!CCollider2D::Init())
		return false;


	if (CEngine::GetEditorMode())
	{
		m_Mesh = CResourceManager::GetInst()->FindMesh("Line2DLineMesh");

		m_Shader = CResourceManager::GetInst()->FindShader("ColliderLine2DShader");
	}

	return true;
}

void CColliderLine2D::Update(float DeltaTime)
{
	CCollider2D::Update(DeltaTime);
}

void CColliderLine2D::PostUpdate(float DeltaTime)
{
	CCollider2D::PostUpdate(DeltaTime);

	m_Info.Point1 = Vector2(GetWorldPos().x, GetWorldPos().y);
	m_Info.Point2 = m_Info.Point1 + m_RelativeDestPoint;

	m_Min.x = m_Info.Point1.x < m_Info.Point2.x ? m_Info.Point1.x : m_Info.Point2.x;
	m_Max.x = m_Info.Point1.x > m_Info.Point2.x ? m_Info.Point1.x : m_Info.Point2.x;

	m_Min.y = m_Info.Point1.y < m_Info.Point2.y ? m_Info.Point1.y : m_Info.Point2.y;
	m_Max.y = m_Info.Point1.y > m_Info.Point2.y ? m_Info.Point1.y : m_Info.Point2.y;
}

void CColliderLine2D::Render()
{
	CCollider2D::Render();

	Matrix	matTranslate, matWorld;

	Matrix	matView = m_Scene->GetCameraManager()->GetCurrentCamera()->GetViewMatrix();
	Matrix	matProj = m_Scene->GetCameraManager()->GetCurrentCamera()->GetProjMatrix();

	matTranslate.Translation(GetWorldPos());

	matWorld = matTranslate;

	CColliderLine2DConstantBuffer* Buffer = CResourceManager::GetInst()->GetColliderLine2DCBuffer();

	Buffer->SetColor(m_Color);
	Buffer->SetWVP(matWorld * matView * matProj);

	Vector3 ConvertPoint = Vector3(m_RelativeDestPoint.x, m_RelativeDestPoint.y, 0.f);

	Buffer->SetConvertPoint(ConvertPoint);

	Buffer->UpdateBuffer();

	m_Shader->SetShader();

	m_Mesh->Render();
}

CColliderLine2D* CColliderLine2D::Clone() const
{
	return new CColliderLine2D(*this);
}

void CColliderLine2D::Save(FILE* File)
{
	CCollider2D::Save(File);

	fwrite(&m_RelativeDestPoint, sizeof(Vector2), 1, File);
}

void CColliderLine2D::Load(FILE* File)
{
	CCollider2D::Load(File);

	fread(&m_RelativeDestPoint, sizeof(Vector2), 1, File);

	if (CEngine::GetEditorMode())
	{
		m_Mesh = CResourceManager::GetInst()->FindMesh("Line2DLineMesh");

		m_Shader = CResourceManager::GetInst()->FindShader("ColliderLine2DShader");
	}
}

bool CColliderLine2D::Collision(CCollider* Dest)
{
	Vector2	HitPoint;
	bool	Result = false;

	switch (((CCollider2D*)Dest)->GetCollider2DType())
	{
	case ECollider2D_Type::Box2D:
		Result = CCollisionManager::GetInst()->CollisionBox2DToLine2D(HitPoint, (CColliderBox2D*)Dest, this);
		break;
	case ECollider2D_Type::OBB2D:
		Result = CCollisionManager::GetInst()->CollisionOBB2DToLine2D(HitPoint, (CColliderOBB2D*)Dest, this);
		break;
	case ECollider2D_Type::Sphere2D:
		Result = CCollisionManager::GetInst()->CollisionSphere2DToLine2D(HitPoint, (CColliderSphere2D*)Dest, this);
		break;
	case ECollider2D_Type::Pixel:
		Result = CCollisionManager::GetInst()->CollisionPixelToLine2D(HitPoint, (CColliderPixel*)Dest, this);
		break;
	case ECollider2D_Type::Line2D:
		Result = CCollisionManager::GetInst()->CollisionLine2DToLine2D(HitPoint, (CColliderLine2D*)Dest, this);
		break;
	}

	m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);

	return Result;
}

bool CColliderLine2D::CollisionMouse(const Vector2& MouseWorldPos)
{
	Vector2	HitPoint;

	m_MouseCollision = CCollisionManager::GetInst()->CollisionPointToLine2D(HitPoint, MouseWorldPos, m_Info);

	m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);

	return m_MouseCollision;
}
