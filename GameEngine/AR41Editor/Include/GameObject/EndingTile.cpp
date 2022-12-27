#include "EndingTile.h"
#include "Component/SpriteComponent.h"
#include "Device.h"

CEndingTile::CEndingTile()
{
	SetTypeID<CEndingTile>();

	m_ObjectTypeName = "EndingTile";
}

CEndingTile::CEndingTile(const CEndingTile& Obj) :
	CGameObject(Obj)
{
	m_EndingTile = (CSpriteComponent*)FindComponent("EndingTile");
}

CEndingTile::~CEndingTile()
{
}

void CEndingTile::Start()
{
	CGameObject::Start();
}

bool CEndingTile::Init()
{
	CGameObject::Init();

	Resolution RS = CDevice::GetInst()->GetResolution();

	m_EndingTile = CreateComponent<CSpriteComponent>("EndingTile");
	m_EndingTile->SetWorldScale((float)RS.Width, 256.f);
	m_EndingTile->SetTexture("EndingTile", TEXT("EndingScene/EndingTile.png"));
	m_EndingTile->SetRenderLayerName("Back2");

	return true;
}

void CEndingTile::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_EndingTile->AddWorldPositionX(40.f * DeltaTime);

	if (GetWorldPos().x >= GetWorldScale().x)
	{
		SetWorldPositionX(-GetWorldScale().x + (GetWorldPos().x - GetWorldScale().x));
	}
}

void CEndingTile::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CEndingTile* CEndingTile::Clone() const
{
	return new CEndingTile(*this);
}