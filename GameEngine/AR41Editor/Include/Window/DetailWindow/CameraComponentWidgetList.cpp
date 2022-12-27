#include "CameraComponentWidgetList.h"
#include "Component/CameraComponent.h"
#include "../DetailWindow.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorInput.h"

CCameraComponentWidgetList::CCameraComponentWidgetList()
{
}

CCameraComponentWidgetList::~CCameraComponentWidgetList()
{
}

bool CCameraComponentWidgetList::Init()
{
	CEditorTree<void*>* CameraComponentTree = CreateWidget<CEditorTree<void*>>("CameraComponentTree");
	CameraComponentTree->AddItem(nullptr, "CameraComponent");
	CameraComponentTree->FindItem("CameraComponent")->AddFlag(ImGuiTreeNodeFlags_DefaultOpen);

	// CameraType
	CameraComponentTree->AddItem(nullptr, "CameraType", "CameraComponent");

	m_CameraType = CameraComponentTree->CreateWidget<CEditorComboBox>("CameraType", "CameraType", 130.f, 30.f);
	m_CameraType->SetHideName(m_CameraType->GetName());
	m_CameraType->AddItem("Camera2D");
	m_CameraType->AddItem("Camera3D");
	m_CameraType->AddItem("CameraUI");

	CEditorSameLine* Line = CameraComponentTree->CreateWidget<CEditorSameLine>("CameraType", "Line");

	CEditorButton* SetButton = CameraComponentTree->CreateWidget<CEditorButton>("CameraType", "Set", 30.f, 30.f);
	SetButton->SetClickCallback<CCameraComponentWidgetList>(this, &CCameraComponentWidgetList::CameraTypeSetButtonClick);


	// CameraViewDistance
	CameraComponentTree->AddItem(nullptr, "CameraViewDistance", "CameraComponent");

	m_CameraViewDistance = CameraComponentTree->CreateWidget<CEditorInput>("CameraViewDistance", "CameraViewDistance", 60.f, 30.f);
	m_CameraViewDistance->SetHideName(m_CameraViewDistance->GetName());
	m_CameraViewDistance->SetInputType(EImGuiInputType::Float);

	Line = CameraComponentTree->CreateWidget<CEditorSameLine>("CameraViewDistance", "Line");

	SetButton = CameraComponentTree->CreateWidget<CEditorButton>("CameraViewDistance", "Set", 30.f, 30.f);
	SetButton->SetClickCallback<CCameraComponentWidgetList>(this, &CCameraComponentWidgetList::CameraViewDistanceSetButtonClick);

	return true;
}

void CCameraComponentWidgetList::SetComponentContents(CSceneComponent* Component)
{
	CCameraComponent* CameraComponent = (CCameraComponent*)Component;

	// CameraType
	ECameraType Type = CameraComponent->GetCameraType();

	// 카메라 타입별로 ComboBox에 넣어주기
	switch (Type)
	{
	case ECameraType::Camera2D:
		m_CameraType->SetPrevViewName("Camera2D");
		break;
	case ECameraType::Camera3D:
		m_CameraType->SetPrevViewName("Camera3D");
		break;
	case ECameraType::CameraUI:
		m_CameraType->SetPrevViewName("CameraUI");
		break;
	}

	// CameraViewDistance
	float CameraViewDistance = CameraComponent->GetCameraViewDistance();

	m_CameraViewDistance->SetFloat(CameraViewDistance);
}

void CCameraComponentWidgetList::CameraTypeSetButtonClick()
{
	int SelectIndex = m_CameraType->GetSelectIndex();

	if (SelectIndex == -1)
		return;

	std::string SelectItem = m_CameraType->GetSelectItem();

	ECameraType Type = ECameraType::Camera2D;

	if (SelectItem == "Camera2D")
		Type = ECameraType::Camera2D;

	else if (SelectItem == "Camera3D")
		Type = ECameraType::Camera3D;

	else if (SelectItem == "CameraUI")
		Type = ECameraType::CameraUI;

	CCameraComponent* Component = (CCameraComponent*)m_DetailWindow->GetSelectComponent();

	if (Component)
	{
		Component->SetCameraType(Type);
	}
}

void CCameraComponentWidgetList::CameraViewDistanceSetButtonClick()
{
	float CameraViewDistance = m_CameraViewDistance->GetFloat();

	CCameraComponent* Component = (CCameraComponent*)m_DetailWindow->GetSelectComponent();

	if (Component)
	{
		Component->SetCameraViewDistance(CameraViewDistance);
	}
}
