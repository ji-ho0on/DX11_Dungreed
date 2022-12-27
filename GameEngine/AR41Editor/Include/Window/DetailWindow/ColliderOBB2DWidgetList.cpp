#include "ColliderOBB2DWidgetList.h"
#include "Component/ColliderOBB2D.h"
#include "../DetailWindow.h"
#include "CollisionManager.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorInput.h"

CColliderOBB2DWidgetList::CColliderOBB2DWidgetList()
{
}

CColliderOBB2DWidgetList::~CColliderOBB2DWidgetList()
{
}

bool CColliderOBB2DWidgetList::Init()
{
	CEditorTree<void*>* ColliderOBB2DTree = CreateWidget<CEditorTree<void*>>("ColliderOBB2DTree");
	ColliderOBB2DTree->AddItem(nullptr, "ColliderOBB2D");
	ColliderOBB2DTree->FindItem("ColliderOBB2D")->AddFlag(ImGuiTreeNodeFlags_DefaultOpen);

	CEditorLabel* Label = ColliderOBB2DTree->CreateWidget<CEditorLabel>("ColliderOBB2D", "BoxSizeX", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	CEditorSameLine* Line = ColliderOBB2DTree->CreateWidget<CEditorSameLine>("ColliderOBB2D", "Line");

	Label = ColliderOBB2DTree->CreateWidget<CEditorLabel>("ColliderOBB2D", "BoxSizeY", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	m_BoxSizeX = ColliderOBB2DTree->CreateWidget<CEditorInput>("ColliderOBB2D", "BoxSizeXInput", 100.f, 30.f);
	m_BoxSizeX->SetHideName(m_BoxSizeX->GetName());
	m_BoxSizeX->SetInputType(EImGuiInputType::Float);

	Line = ColliderOBB2DTree->CreateWidget<CEditorSameLine>("ColliderOBB2D", "Line");

	m_BoxSizeY = ColliderOBB2DTree->CreateWidget<CEditorInput>("ColliderOBB2D", "BoxSizeYInput", 100.f, 30.f);
	m_BoxSizeY->SetHideName(m_BoxSizeY->GetName());
	m_BoxSizeY->SetInputType(EImGuiInputType::Float);

	Line = ColliderOBB2DTree->CreateWidget<CEditorSameLine>("ColliderOBB2D", "Line");
	Line->SetOffsetX(250.f);

	CEditorButton* Button = ColliderOBB2DTree->CreateWidget<CEditorButton>("ColliderOBB2D", "BoxSize Set", 100.f, 30.f);
	Button->SetClickCallback<CColliderOBB2DWidgetList>(this, &CColliderOBB2DWidgetList::BoxSizeSetButtonClick);

    return true;
}

void CColliderOBB2DWidgetList::SetComponentContents(CSceneComponent* Component)
{
	CColliderOBB2D* ColliderOBB2D = (CColliderOBB2D*)Component;

	Vector2 BoxSize = ColliderOBB2D->GetBoxHalfSize() * 2.f;

	m_BoxSizeX->SetFloat(BoxSize.x);
	m_BoxSizeY->SetFloat(BoxSize.y);
}

void CColliderOBB2DWidgetList::BoxSizeSetButtonClick()
{
	Vector2 BoxHalfSize = Vector2(m_BoxSizeX->GetFloat(), m_BoxSizeY->GetFloat()) / 2.f;

	CColliderOBB2D* Component = (CColliderOBB2D*)m_DetailWindow->GetSelectComponent();

	if (Component)
	{
		Component->SetBoxHalfSize(BoxHalfSize);
	}
}
