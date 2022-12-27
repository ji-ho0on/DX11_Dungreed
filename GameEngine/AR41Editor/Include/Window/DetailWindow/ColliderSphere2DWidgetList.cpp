#include "ColliderSphere2DWidgetList.h"
#include "Component/ColliderSphere2D.h"
#include "../DetailWindow.h"
#include "CollisionManager.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorInput.h"

CColliderSphere2DWidgetList::CColliderSphere2DWidgetList()
{
}

CColliderSphere2DWidgetList::~CColliderSphere2DWidgetList()
{
}

bool CColliderSphere2DWidgetList::Init()
{
	CEditorTree<void*>* ColliderSphere2DTree = CreateWidget<CEditorTree<void*>>("ColliderSphere2DTree");
	ColliderSphere2DTree->AddItem(nullptr, "ColliderSphere2D");
	ColliderSphere2DTree->FindItem("ColliderSphere2D")->AddFlag(ImGuiTreeNodeFlags_DefaultOpen);

	CEditorLabel* Label = ColliderSphere2DTree->CreateWidget<CEditorLabel>("ColliderSphere2D", "Radius", 60.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	CEditorSameLine* Line = ColliderSphere2DTree->CreateWidget<CEditorSameLine>("ColliderSphere2D", "Line");

	m_Radius = ColliderSphere2DTree->CreateWidget<CEditorInput>("ColliderSphere2D", "RadiusInput", 60.f, 30.f);
	m_Radius->SetHideName(m_Radius->GetName());
	m_Radius->SetInputType(EImGuiInputType::Float);

	Line = ColliderSphere2DTree->CreateWidget<CEditorSameLine>("ColliderSphere2D", "Line");
	Line->SetOffsetX(200.f);

	CEditorButton* Button = ColliderSphere2DTree->CreateWidget<CEditorButton>("ColliderSphere2D", "Radius Set", 100.f, 30.f);
	Button->SetClickCallback<CColliderSphere2DWidgetList>(this, &CColliderSphere2DWidgetList::RadiusSetButtonClick);

    return true;
}

void CColliderSphere2DWidgetList::SetComponentContents(CSceneComponent* Component)
{
	CColliderSphere2D* ColliderSphere2D = (CColliderSphere2D*)Component;

	float Radius = ColliderSphere2D->GetRadius();

	m_Radius->SetFloat(Radius);
}

void CColliderSphere2DWidgetList::RadiusSetButtonClick()
{
	float Radius = m_Radius->GetFloat();

	CColliderSphere2D* Component = (CColliderSphere2D*)m_DetailWindow->GetSelectComponent();

	if (Component)
	{
		Component->SetRadius(Radius);
	}
}
