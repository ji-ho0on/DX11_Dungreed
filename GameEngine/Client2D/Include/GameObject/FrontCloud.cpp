#include "FrontCloud.h"
#include "Component/SpriteComponent.h"

CFrontCloud::CFrontCloud()
{
	SetTypeID<CFrontCloud>();

	m_ObjectTypeName = "FrontCloud";
}

CFrontCloud::CFrontCloud(const CFrontCloud& Obj) :
	CGameObject(Obj)
{
	m_FrontCloud = (CSpriteComponent*)FindComponent("FrontCloud");
}

CFrontCloud::~CFrontCloud()
{
}

void CFrontCloud::Start()
{
	CGameObject::Start();
}

bool CFrontCloud::Init()
{
	CGameObject::Init();

	m_FrontCloud = CreateComponent<CSpriteComponent>("FrontCloud");
	m_FrontCloud->SetRenderLayerName("Back3");
	m_FrontCloud->SetTexture("FrontCloud", TEXT("MainScene/FrontCloud.png"));

	return true;
}

void CFrontCloud::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	AddWorldPosition(GetWorldAxis(AXIS_X) * -50.f * DeltaTime);

	if (GetWorldPos().x + GetWorldScale().x <= 0)
		m_FrontCloud->SetWorldPositionX(GetWorldScale().x);
}

void CFrontCloud::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CFrontCloud* CFrontCloud::Clone() const
{
	return new CFrontCloud(*this);
}