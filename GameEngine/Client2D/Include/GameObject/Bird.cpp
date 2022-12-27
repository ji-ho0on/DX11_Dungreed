#include "Bird.h"
#include "Component/SpriteComponent.h"
#include "../Animation2D/BirdAnimation.h"
#include "Device.h"

CBird::CBird()
{
	SetTypeID<CBird>();

	m_ObjectTypeName = "Bird";
}

CBird::CBird(const CBird& Obj) :
	CGameObject(Obj)
{
	m_Bird = (CSpriteComponent*)FindComponent("Bird");
	m_MapWidth = Obj.m_MapWidth;
}

CBird::~CBird()
{
}

void CBird::Start()
{
	CGameObject::Start();
}

bool CBird::Init()
{
	CGameObject::Init();

	m_Bird = CreateComponent<CSpriteComponent>("Bird");
	m_Bird->SetWorldPosition(0.f, 300.f);
	m_Bird->SetWorldScale(45.f, 30.f);
	m_Bird->SetAnimation<CBirdAnimation>("BirdAnimation");
	m_Bird->SetRenderLayerName("Back2");

	m_MapWidth = (float)CDevice::GetInst()->GetResolution().Width;

	return true;
}

void CBird::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	AddWorldPosition(GetWorldAxis(AXIS_X) * 50.f * DeltaTime);

	if (m_Bird->GetWorldPos().x >= m_MapWidth)
		Destroy();
}

void CBird::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBird* CBird::Clone() const
{
	return new CBird(*this);
}