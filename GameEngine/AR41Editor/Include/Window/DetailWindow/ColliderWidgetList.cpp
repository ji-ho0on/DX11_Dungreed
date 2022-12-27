#include "ColliderWidgetList.h"
#include "Component/Collider.h"
#include "../DetailWindow.h"
#include "CollisionManager.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorComboBox.h"

CColliderWidgetList::CColliderWidgetList()
{
}

CColliderWidgetList::~CColliderWidgetList()
{
}

bool CColliderWidgetList::Init()
{
	CEditorTree<void*>* ColliderTree = CreateWidget<CEditorTree<void*>>("ColliderTree");
	ColliderTree->AddItem(nullptr, "Collider");
	ColliderTree->FindItem("Collider")->AddFlag(ImGuiTreeNodeFlags_DefaultOpen);

	m_CollisionProfileCombo = ColliderTree->CreateWidget<CEditorComboBox>("Collider", "CollisionProfileCombo", 150.f, 30.f);
	m_CollisionProfileCombo->SetHideName(m_CollisionProfileCombo->GetName());

	std::vector<std::string> vecProfileName;

	CCollisionManager::GetInst()->GetAllProfileName(vecProfileName);

	size_t Size = vecProfileName.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_CollisionProfileCombo->AddItem(vecProfileName[i]);
	}

	m_CollisionProfileCombo->Sort(true);

	CEditorSameLine* Line = ColliderTree->CreateWidget<CEditorSameLine>("Collider", "Line");
	Line->SetOffsetX(250.f);

	CEditorButton* ProfileSetButton = ColliderTree->CreateWidget<CEditorButton>("Collider", "Profile Set", 100.f, 30.f);
	ProfileSetButton->SetClickCallback<CColliderWidgetList>(this, &CColliderWidgetList::ProfileSetButtonClick);

    return true;
}

void CColliderWidgetList::SetComponentContents(CSceneComponent* Component)
{
	CCollider* Collider = (CCollider*)Component;

	std::string ProfileName = Collider->GetCollisionProfile()->Name;

	m_CollisionProfileCombo->SetPrevViewName(ProfileName);
}

void CColliderWidgetList::ProfileSetButtonClick()
{
	if (m_CollisionProfileCombo->GetSelectIndex() == -1)
		return;

	CCollider* Component = (CCollider*)m_DetailWindow->GetSelectComponent();

	if (Component)
	{
		Component->SetCollisionProfile(m_CollisionProfileCombo->GetSelectItem());
	}
}
