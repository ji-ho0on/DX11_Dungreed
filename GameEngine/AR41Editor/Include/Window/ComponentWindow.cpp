
#include "ComponentWindow.h"
#include "Editor/EditorGUIManager.h"
#include "GameObject/GameObject.h"

// Widget
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorComboBox.h"

// Window
#include "TransformWindow.h"
#include "DetailWindow.h"
#include "Animation2DWindow.h"

#include "Component/Component.h"
#include "Component/SceneComponent.h"
#include "Component/SpriteComponent.h"

CComponentWindow::CComponentWindow()
{
}

CComponentWindow::~CComponentWindow()
{
}

bool CComponentWindow::AddItem(CComponent* Component, const std::string& Name, const std::string& ParentName)
{
	return m_Tree->AddItem(Component, Name, ParentName);
}

void CComponentWindow::Clear()
{
	m_Tree->Clear();
}

void CComponentWindow::ClearSelect()
{
	m_SelectComponent = nullptr;
}

bool CComponentWindow::Init()
{
	CEditorText* SelectComponentText = CreateWidget<CEditorText>("SelectComponentText");
	SelectComponentText->SetText("SelectComponent");

	CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");

	m_SelectComponentInput = CreateWidget<CEditorInput>("SelectComponentInput");
	m_SelectComponentInput->SetHideName(m_SelectComponentInput->GetName());
	m_SelectComponentInput->SetSize(200.f, 30.f);
	m_SelectComponentInput->ReadOnly(true);


	CEditorButton* DeleteCompoentButton = CreateWidget<CEditorButton>("Delete Component", 150.f, 30.f);
	DeleteCompoentButton->SetClickCallback<CComponentWindow>(this, &CComponentWindow::DeleteComponentButton);

	m_Tree = CreateWidget<CEditorTree<CComponent*>>("ComponentTree");

	m_Tree->SetSelectCallback<CComponentWindow>(this, &CComponentWindow::TreeCallback);

	m_Tree->SetSize(400.f, 300.f);

	return true;
}

void CComponentWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);

	if (m_SelectComponent)
	{
		if (!m_SelectComponent->GetActive())
			m_SelectComponent = nullptr;
	}
}

void CComponentWindow::TreeCallback(CEditorTreeItem<class CComponent*>* Node, const std::string& Item)
{
	m_SelectComponent = Node->GetCustomData();

	CEditorInput* SelectedComponentInput = (CEditorInput*)FindWidget(m_SelectComponentInput->GetName());
	SelectedComponentInput->SetText(Item.c_str());

	CTransformWindow* TransformWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CTransformWindow>("TransformWindow");
	CDetailWindow* DetailWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CDetailWindow>("DetailWindow");
	CAnimation2DWindow* Animation2DWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CAnimation2DWindow>("Animation2DWindow");

	DetailWindow->SetSelectComponent((CSceneComponent*)m_SelectComponent.Get());
	Animation2DWindow->SetSelectComponent((CSpriteComponent*)m_SelectComponent.Get());


	if (m_SelectComponent)
	{
		CSceneComponent* Component = (CSceneComponent*)m_SelectComponent.Get();

		TransformWindow->SetSelectComponent(Component);
	}
}

void CComponentWindow::DeleteComponentButton()
{
	if (!m_SelectComponent)
		return;

	// 선택한 Component를 GameObject의 SceneComponentList에서 지워야함.
	// Parnet가 있다면 Parent의 DeleteChild를 통해 제거, Parent가 없다면 RootComponent이므로 모두 제거
	CSceneComponent* ParentComponent = ((CSceneComponent*)m_SelectComponent.Get())->GetParent();

	if (ParentComponent)
	{
		ParentComponent->DeleteChild(m_SelectComponent->GetName());
	}

	else
	{
		CGameObject* Owner = m_SelectComponent->GetOwner();
		Owner->DeleteSceneComponent((CSceneComponent*)m_SelectComponent.Get());
	}

	// GameObject의 SerialNumber를 재조정해야함.


	// 지우고 m_Tree에서도 지워야함.
	std::string DeleteItem = m_SelectComponent->GetName() + "(" + m_SelectComponent->GetComponentTypeName() + ")";

	m_Tree->DeleteItem(DeleteItem);

	m_SelectComponent = nullptr;

	m_SelectComponentInput->SetText("");
}
