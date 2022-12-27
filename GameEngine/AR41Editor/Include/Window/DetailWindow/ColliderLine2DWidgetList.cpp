#include "ColliderLine2DWidgetList.h"
#include "Component/ColliderLine2D.h"
#include "../DetailWindow.h"
#include "CollisionManager.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorInput.h"

CColliderLine2DWidgetList::CColliderLine2DWidgetList()
{
}

CColliderLine2DWidgetList::~CColliderLine2DWidgetList()
{
}

bool CColliderLine2DWidgetList::Init()
{
	CEditorTree<void*>* ColliderLine2DTree = CreateWidget<CEditorTree<void*>>("ColliderLine2DTree");
	ColliderLine2DTree->AddItem(nullptr, "ColliderLine2D");
	ColliderLine2DTree->FindItem("ColliderLine2D")->AddFlag(ImGuiTreeNodeFlags_DefaultOpen);

	CEditorLabel* Label = ColliderLine2DTree->CreateWidget<CEditorLabel>("ColliderLine2D", "Point1X", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	CEditorSameLine* Line = ColliderLine2DTree->CreateWidget<CEditorSameLine>("ColliderLine2D", "Line");

	Label = ColliderLine2DTree->CreateWidget<CEditorLabel>("ColliderLine2D", "Point1Y", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	m_Point1X = ColliderLine2DTree->CreateWidget<CEditorInput>("ColliderLine2D", "Point1XInput", 100.f, 30.f);
	m_Point1X->SetHideName(m_Point1X->GetName());
	m_Point1X->SetInputType(EImGuiInputType::Float);

	Line = ColliderLine2DTree->CreateWidget<CEditorSameLine>("ColliderLine2D", "Line");

	m_Point1Y = ColliderLine2DTree->CreateWidget<CEditorInput>("ColliderLine2D", "Point1YInput", 100.f, 30.f);
	m_Point1Y->SetHideName(m_Point1Y->GetName());
	m_Point1Y->SetInputType(EImGuiInputType::Float);

	Line = ColliderLine2DTree->CreateWidget<CEditorSameLine>("ColliderLine2D", "Line");
	Line->SetOffsetX(250.f);

	CEditorButton* Button = ColliderLine2DTree->CreateWidget<CEditorButton>("ColliderLine2D", "Point1 Set", 100.f, 30.f);
	Button->SetClickCallback<CColliderLine2DWidgetList>(this, &CColliderLine2DWidgetList::Point1SetButtonClick);



	Label = ColliderLine2DTree->CreateWidget<CEditorLabel>("ColliderLine2D", "Point2X", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	Line = ColliderLine2DTree->CreateWidget<CEditorSameLine>("ColliderLine2D", "Line");

	Label = ColliderLine2DTree->CreateWidget<CEditorLabel>("ColliderLine2D", "Point2Y", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	m_Point2X = ColliderLine2DTree->CreateWidget<CEditorInput>("ColliderLine2D", "Point2XInput", 100.f, 30.f);
	m_Point2X->SetHideName(m_Point2X->GetName());
	m_Point2X->SetInputType(EImGuiInputType::Float);

	Line = ColliderLine2DTree->CreateWidget<CEditorSameLine>("ColliderLine2D", "Line");

	m_Point2Y = ColliderLine2DTree->CreateWidget<CEditorInput>("ColliderLine2D", "Point2YInput", 100.f, 30.f);
	m_Point2Y->SetHideName(m_Point2Y->GetName());
	m_Point2Y->SetInputType(EImGuiInputType::Float);

	Line = ColliderLine2DTree->CreateWidget<CEditorSameLine>("ColliderLine2D", "Line");
	Line->SetOffsetX(250.f);

	Button = ColliderLine2DTree->CreateWidget<CEditorButton>("ColliderLine2D", "Point2 Set", 100.f, 30.f);
	Button->SetClickCallback<CColliderLine2DWidgetList>(this, &CColliderLine2DWidgetList::Point2SetButtonClick);

    return true;
}

void CColliderLine2DWidgetList::SetComponentContents(CSceneComponent* Component)
{
	CColliderLine2D* ColliderLine2D = (CColliderLine2D*)Component;

	Vector2 Point1 = Vector2(ColliderLine2D->GetRelativePos().x, ColliderLine2D->GetRelativePos().y);

	Vector2 Point2 = ColliderLine2D->GetRelativeDestPoint();

	m_Point1X->SetFloat(Point1.x);
	m_Point1Y->SetFloat(Point1.y);

	m_Point2X->SetFloat(Point2.x);
	m_Point2Y->SetFloat(Point2.y);
}

void CColliderLine2DWidgetList::Point1SetButtonClick()
{
	Vector2 Point1 = Vector2(m_Point1X->GetFloat(), m_Point1Y->GetFloat());

	CColliderLine2D* Component = (CColliderLine2D*)m_DetailWindow->GetSelectComponent();

	if (Component)
	{
		Component->SetRelativePosition(Point1);
	}
}

void CColliderLine2DWidgetList::Point2SetButtonClick()
{
	Vector2 Point2 = Vector2(m_Point2X->GetFloat(), m_Point2Y->GetFloat());

	CColliderLine2D* Component = (CColliderLine2D*)m_DetailWindow->GetSelectComponent();

	if (Component)
	{
		Component->SetRelativeDestPoint(Point2);
	}
}
