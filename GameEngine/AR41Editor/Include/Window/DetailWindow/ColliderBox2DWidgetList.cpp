#include "ColliderBox2DWidgetList.h"
#include "Component/ColliderBox2D.h"
#include "../DetailWindow.h"
#include "CollisionManager.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorInput.h"

CColliderBox2DWidgetList::CColliderBox2DWidgetList()
{
}

CColliderBox2DWidgetList::~CColliderBox2DWidgetList()
{
}

bool CColliderBox2DWidgetList::Init()
{
	CEditorTree<void*>* ColliderBox2DTree = CreateWidget<CEditorTree<void*>>("ColliderBox2DTree");
	ColliderBox2DTree->AddItem(nullptr, "ColliderBox2D");
	ColliderBox2DTree->FindItem("ColliderBox2D")->AddFlag(ImGuiTreeNodeFlags_DefaultOpen);

	CEditorLabel* Label = ColliderBox2DTree->CreateWidget<CEditorLabel>("ColliderBox2D", "BoxSizeX", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	CEditorSameLine* Line = ColliderBox2DTree->CreateWidget<CEditorSameLine>("ColliderBox2D", "Line");

	Label = ColliderBox2DTree->CreateWidget<CEditorLabel>("ColliderBox2D", "BoxSizeY", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	m_BoxSizeX = ColliderBox2DTree->CreateWidget<CEditorInput>("ColliderBox2D", "BoxSizeXInput", 100.f, 30.f);
	m_BoxSizeX->SetHideName(m_BoxSizeX->GetName());
	m_BoxSizeX->SetInputType(EImGuiInputType::Float);

	Line = ColliderBox2DTree->CreateWidget<CEditorSameLine>("ColliderBox2D", "Line");

	m_BoxSizeY = ColliderBox2DTree->CreateWidget<CEditorInput>("ColliderBox2D", "BoxSizeYInput", 100.f, 30.f);
	m_BoxSizeY->SetHideName(m_BoxSizeY->GetName());
	m_BoxSizeY->SetInputType(EImGuiInputType::Float);

	Line = ColliderBox2DTree->CreateWidget<CEditorSameLine>("ColliderBox2D", "Line");
	Line->SetOffsetX(250.f);

	CEditorButton* Button = ColliderBox2DTree->CreateWidget<CEditorButton>("ColliderBox2D", "BoxSize Set", 100.f, 30.f);
	Button->SetClickCallback<CColliderBox2DWidgetList>(this, &CColliderBox2DWidgetList::BoxSizeSetButtonClick);

    return true;
}

void CColliderBox2DWidgetList::SetComponentContents(CSceneComponent* Component)
{
	CColliderBox2D* ColliderBox2D = (CColliderBox2D*)Component;

	Vector2 BoxSize = ColliderBox2D->GetBoxSize();

	m_BoxSizeX->SetFloat(BoxSize.x);
	m_BoxSizeY->SetFloat(BoxSize.y);
}

void CColliderBox2DWidgetList::BoxSizeSetButtonClick()
{
	Vector2 BoxSize = Vector2(m_BoxSizeX->GetFloat(), m_BoxSizeY->GetFloat());

	CColliderBox2D* Component = (CColliderBox2D*)m_DetailWindow->GetSelectComponent();

	if (Component)
	{
		Component->SetBoxSize(BoxSize);
	}
}
