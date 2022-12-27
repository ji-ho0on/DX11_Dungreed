#include "BackCloud.h"
#include "Component/SpriteComponent.h"

CBackCloud::CBackCloud()
{
	SetTypeID<CBackCloud>();

	m_ObjectTypeName = "BackCloud";
}

CBackCloud::CBackCloud(const CBackCloud& Obj) :
	CGameObject(Obj)
{
	m_BackCloud = (CSpriteComponent*)FindComponent("BackCloud");
}

CBackCloud::~CBackCloud()
{
}

void CBackCloud::Start()
{
	CGameObject::Start();
}

bool CBackCloud::Init()
{
	CGameObject::Init();

	m_BackCloud = CreateComponent<CSpriteComponent>("BackCloud");
	m_BackCloud->SetRenderLayerName("Back");
	m_BackCloud->SetTexture("BackCloud", TEXT("MainScene/BackCloud.png"));

	return true;
}

void CBackCloud::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	AddWorldPosition(GetWorldAxis(AXIS_X) * -15.f * DeltaTime);

	if (GetWorldPos().x + GetWorldScale().x <= 0)
		m_BackCloud->SetWorldPositionX(GetWorldScale().x);
}

void CBackCloud::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBackCloud* CBackCloud::Clone() const
{
	return new CBackCloud(*this);
}