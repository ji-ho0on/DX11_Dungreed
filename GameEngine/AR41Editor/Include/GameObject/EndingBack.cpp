#include "EndingBack.h"
#include "Component/SpriteComponent.h"
#include "Device.h"

CEndingBack::CEndingBack()
{
	SetTypeID<CEndingBack>();

	m_ObjectTypeName = "EndingBack";
}

CEndingBack::CEndingBack(const CEndingBack& Obj) :
	CGameObject(Obj)
{
	m_Back = (CSpriteComponent*)FindComponent("Back");
}

CEndingBack::~CEndingBack()
{
}

void CEndingBack::Start()
{
	CGameObject::Start();
}

bool CEndingBack::Init()
{
	CGameObject::Init();

	Resolution RS = CDevice::GetInst()->GetResolution();

	m_Back = CreateComponent<CSpriteComponent>("Back");
	m_Back->SetWorldScale((float)RS.Width, (float)RS.Height);
	m_Back->SetTexture("Sky_Night", TEXT("EndingScene/Sky_Night.png"));
	m_Back->SetPivot(0.f, 1.f);
	m_Back->SetWorldPositionY((float)RS.Height);
	m_Back->SetRenderLayerName("Back");

	return true;
}

void CEndingBack::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CEndingBack::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CEndingBack* CEndingBack::Clone() const
{
	return new CEndingBack(*this);
}