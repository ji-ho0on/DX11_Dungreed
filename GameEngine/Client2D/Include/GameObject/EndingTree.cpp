#include "EndingTree.h"
#include "Component/SpriteComponent.h"
#include "Device.h"

CEndingTree::CEndingTree()
{
	SetTypeID<CEndingTree>();

	m_ObjectTypeName = "EndingTree";
}

CEndingTree::CEndingTree(const CEndingTree& Obj) :
	CGameObject(Obj)
{
	m_Tree = (CSpriteComponent*)FindComponent("Tree");
}

CEndingTree::~CEndingTree()
{
}

void CEndingTree::Start()
{
	CGameObject::Start();
}

bool CEndingTree::Init()
{
	CGameObject::Init();

	Resolution RS = CDevice::GetInst()->GetResolution();

	m_Tree = CreateComponent<CSpriteComponent>("Tree");
	m_Tree->SetWorldScale((float)RS.Width, (float)RS.Height - 160.f);
	m_Tree->SetTexture("TownBG_Night", TEXT("EndingScene/TownBG_Night.png"));
	m_Tree->SetPivot(0.f, 1.f);
	m_Tree->SetWorldPositionY((float)RS.Height - 160.f);
	m_Tree->SetRenderLayerName("Back1");
	m_Tree->Set2DZOffset(100.f);

	return true;
}

void CEndingTree::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Tree->AddWorldPositionX(20.f * DeltaTime);

	if (GetWorldPos().x >= GetWorldScale().x)
	{
		SetWorldPositionX(-GetWorldScale().x + (GetWorldPos().x - GetWorldScale().x));
	}
}

void CEndingTree::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CEndingTree* CEndingTree::Clone() const
{
	return new CEndingTree(*this);
}