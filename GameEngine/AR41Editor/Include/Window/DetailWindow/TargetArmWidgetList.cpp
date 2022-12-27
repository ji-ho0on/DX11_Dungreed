#include "TargetArmWidgetList.h"
#include "Component/TargetArm.h"
#include "../DetailWindow.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorLabel.h"

CTargetArmWidgetList::CTargetArmWidgetList()
{
}

CTargetArmWidgetList::~CTargetArmWidgetList()
{
}

bool CTargetArmWidgetList::Init()
{
	CEditorTree<void*>* TargetArmTree = CreateWidget<CEditorTree<void*>>("TargetArmTree");
	TargetArmTree->AddItem(nullptr, "TargetArm");
	TargetArmTree->FindItem("TargetArm")->AddFlag(ImGuiTreeNodeFlags_DefaultOpen);

	// TargetOffset
	TargetArmTree->AddItem(nullptr, "TargetOffset", "TargetArm");

	CEditorLabel* Label = TargetArmTree->CreateWidget<CEditorLabel>("TargetOffset", "OffsetX", 60.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	CEditorSameLine* Line = TargetArmTree->CreateWidget<CEditorSameLine>("TargetOffset", "Line");

	Label = TargetArmTree->CreateWidget<CEditorLabel>("TargetOffset", "OffsetY", 60.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	Line = TargetArmTree->CreateWidget<CEditorSameLine>("TargetOffset", "Line");

	Label = TargetArmTree->CreateWidget<CEditorLabel>("TargetOffset", "OffsetZ", 60.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	m_TargetOffsetX = TargetArmTree->CreateWidget<CEditorInput>("TargetOffset", "TargetOffsetXInput", 60.f, 30.f);
	m_TargetOffsetX->SetHideName(m_TargetOffsetX->GetName());
	m_TargetOffsetX->SetInputType(EImGuiInputType::Float);

	Line = TargetArmTree->CreateWidget<CEditorSameLine>("TargetOffset", "Line");

	m_TargetOffsetY = TargetArmTree->CreateWidget<CEditorInput>("TargetOffset", "TargetOffsetYInput", 60.f, 30.f);
	m_TargetOffsetY->SetHideName(m_TargetOffsetY->GetName());
	m_TargetOffsetY->SetInputType(EImGuiInputType::Float);

	Line = TargetArmTree->CreateWidget<CEditorSameLine>("TargetOffset", "Line");

	m_TargetOffsetZ = TargetArmTree->CreateWidget<CEditorInput>("TargetOffset", "TargetOffsetZInput", 60.f, 30.f);
	m_TargetOffsetZ->SetHideName(m_TargetOffsetZ->GetName());
	m_TargetOffsetZ->SetInputType(EImGuiInputType::Float);

	Line = TargetArmTree->CreateWidget<CEditorSameLine>("TargetOffset", "Line");

	CEditorButton* SetButton = TargetArmTree->CreateWidget<CEditorButton>("TargetOffset", "Set", 30.f, 30.f);
	SetButton->SetClickCallback<CTargetArmWidgetList>(this, &CTargetArmWidgetList::TargetArmOffsetSetButtonClick);


	// TargetDistance
	TargetArmTree->AddItem(nullptr, "TargetDistance", "TargetArm");

	m_TargetDistance = TargetArmTree->CreateWidget<CEditorInput>("TargetDistance", "TargetDistanceInput", 60.f, 30.f);
	m_TargetDistance->SetHideName(m_TargetDistance->GetName());
	m_TargetDistance->SetInputType(EImGuiInputType::Float);

	Line = TargetArmTree->CreateWidget<CEditorSameLine>("TargetDistance", "Line");

	SetButton = TargetArmTree->CreateWidget<CEditorButton>("TargetDistance", "Set", 30.f, 30.f);
	SetButton->SetClickCallback<CTargetArmWidgetList>(this, &CTargetArmWidgetList::TargetArmDistanceSetButtonClick);

    return true;
}

void CTargetArmWidgetList::SetComponentContents(CSceneComponent* Component)
{
	CTargetArm* TargetArm = (CTargetArm*)Component;

	// TargetOffset
	Vector3 TargetOffset = TargetArm->GetTargetOffset();

	m_TargetOffsetX->SetFloat(TargetOffset.x);
	m_TargetOffsetY->SetFloat(TargetOffset.y);
	m_TargetOffsetZ->SetFloat(TargetOffset.z);

	// TargetDistance
	float TargetDistance = TargetArm->GetTargetDistance();

	m_TargetDistance->SetFloat(TargetDistance);
}

void CTargetArmWidgetList::TargetArmOffsetSetButtonClick()
{
	Vector3 TargetOffset = Vector3(m_TargetOffsetX->GetFloat(), m_TargetOffsetY->GetFloat(), m_TargetOffsetZ->GetFloat());

	CTargetArm* Component = (CTargetArm*)m_DetailWindow->GetSelectComponent();

	if (Component)
	{
		Component->SetTargetOffset(TargetOffset);
	}
}

void CTargetArmWidgetList::TargetArmDistanceSetButtonClick()
{
	float TargetDistance = m_TargetDistance->GetFloat();

	CTargetArm* Component = (CTargetArm*)m_DetailWindow->GetSelectComponent();

	if (Component)
	{
		Component->SetTargetDistance(TargetDistance);
	}
}
