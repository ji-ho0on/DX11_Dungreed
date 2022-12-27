#include "UIWindowEditor.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "UI/UIWindow.h"
#include "UIWidgetEditor.h"
#include "Editor/EditorGUIManager.h"

// Widget
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorNewLine.h"
#include "Editor/EditorCheckBox.h"
#include "Editor/EditorTap.h"
#include "Editor/EditorGroup.h"
#include "Editor/EditorSlider.h"
#include "Editor/EditorSeparator.h"

// UIWindow
#include "../UI/MainUI.h"
#include "../UI/PlaySlotUI.h"
#include "../UI/SettingUI.h"
#include "../UI/StartSceneUI.h"
#include "../UI/BossUI.h"
#include "../UI/EndingUI.h"

CUIWindowEditor::CUIWindowEditor()
{
}

CUIWindowEditor::~CUIWindowEditor()
{
}

bool CUIWindowEditor::Init()
{
	// 처음 시작된 Scene으로 설정
	m_Scene = CSceneManager::GetInst()->GetScene();

	CEditorGroup* UIWindowListGroup = CreateWidget<CEditorGroup>("UIWindowListGroup");

	CEditorText* UIWindowListText = UIWindowListGroup->CreateWidget<CEditorText>("UIWindowListText");
	UIWindowListText->SetText("UIWindowList");

	m_UIWindowListBox = UIWindowListGroup->CreateWidget<CEditorListBox>("UIWindowListBox", 150.f);
	m_UIWindowListBox->SetHideName(m_UIWindowListBox->GetName());
	m_UIWindowListBox->SetPageItemCount(6);
	m_UIWindowListBox->SetSelectCallback<CUIWindowEditor>(this, &CUIWindowEditor::UIListBoxClickCallback);

	LoadUIList();

	CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");

	CEditorGroup* UIWindowSelectGroup = CreateWidget<CEditorGroup>("UIWindowSelectGroup");

	CEditorText* UIWindowSelectText = UIWindowSelectGroup->CreateWidget<CEditorText>("UIWindowSelectText");
	UIWindowSelectText->SetText("SelectUIWindow");

	m_SelectUIWindowInput = UIWindowSelectGroup->CreateWidget<CEditorInput>("SelectUIWindowInput", 150.f, 30.f);
	m_SelectUIWindowInput->SetHideName(m_SelectUIWindowInput->GetName());
	m_SelectUIWindowInput->ReadOnly(true);

	CEditorGroup* UIWindowEditGroup = CreateWidget<CEditorGroup>("UIWindowEditGroup");

	CEditorText* ZOrderText = UIWindowEditGroup->CreateWidget<CEditorText>("ZOrderText");
	ZOrderText->SetText("ZOrder");

	Line = UIWindowEditGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(60.f);

	m_ZOrder = UIWindowEditGroup->CreateWidget<CEditorInput>("ZOrder", 80.f, 30.f);
	m_ZOrder->SetHideName("ZOrder");
	m_ZOrder->SetInputType(EImGuiInputType::Int);
	m_ZOrder->SetInputCallback<CUIWindowEditor>(this, &CUIWindowEditor::ZOrderCallback);

	CEditorText* PosText = UIWindowEditGroup->CreateWidget<CEditorText>("PosText");
	PosText->SetText("Pos");

	Line = UIWindowEditGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(60.f);

	m_Pos[0] = UIWindowEditGroup->CreateWidget<CEditorInput>("PosX", 80.f, 30.f);
	m_Pos[0]->SetHideName("PosX");
	m_Pos[0]->SetInputType(EImGuiInputType::Float);
	m_Pos[0]->SetInputCallback<CUIWindowEditor>(this, &CUIWindowEditor::PosXCallback);

	Line = UIWindowEditGroup->CreateWidget<CEditorSameLine>("Line");

	m_Pos[1] = UIWindowEditGroup->CreateWidget<CEditorInput>("PosY", 80.f, 30.f);
	m_Pos[1]->SetHideName("PosY");
	m_Pos[1]->SetInputType(EImGuiInputType::Float);
	m_Pos[1]->SetInputCallback<CUIWindowEditor>(this, &CUIWindowEditor::PosYCallback);

	CEditorText* SizeText = UIWindowEditGroup->CreateWidget<CEditorText>("SizeText");
	SizeText->SetText("Size");

	Line = UIWindowEditGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(60.f);

	m_Size[0] = UIWindowEditGroup->CreateWidget<CEditorInput>("SizeX", 80.f, 30.f);
	m_Size[0]->SetHideName("SizeX");
	m_Size[0]->SetInputType(EImGuiInputType::Float);
	m_Size[0]->SetInputCallback<CUIWindowEditor>(this, &CUIWindowEditor::SizeXCallback);

	Line = UIWindowEditGroup->CreateWidget<CEditorSameLine>("Line");

	m_Size[1] = UIWindowEditGroup->CreateWidget<CEditorInput>("SizeY", 80.f, 30.f);
	m_Size[1]->SetHideName("SizeY");
	m_Size[1]->SetInputType(EImGuiInputType::Float);
	m_Size[1]->SetInputCallback<CUIWindowEditor>(this, &CUIWindowEditor::SizeYCallback);

	return true;
}

void CUIWindowEditor::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);
}

void CUIWindowEditor::SetScene(CScene* Scene)
{
	m_Scene = Scene;

	LoadUIList();
}

void CUIWindowEditor::SetUIWindow(CUIWindow* UIWindow)
{
	Vector2 Pos = UIWindow->GetPos();
	m_Pos[0]->SetFloat(Pos.x);
	m_Pos[1]->SetFloat(Pos.y);

	Vector2 Size = UIWindow->GetSize();
	m_Size[0]->SetFloat(Size.x);
	m_Size[1]->SetFloat(Size.y);

	int ZOrder = UIWindow->GetZOrder();
	m_ZOrder->SetInt(ZOrder);
}

void CUIWindowEditor::LoadUIList()
{
	m_UIWindowListBox->Clear();

	std::vector<std::string> vecWindowName;

	m_Scene->GetViewport()->GetWindowNames(vecWindowName);

	size_t Size = vecWindowName.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_UIWindowListBox->AddItem(vecWindowName[i]);
	}
}

void CUIWindowEditor::UIListBoxClickCallback(int Index, const std::string& Item)
{
	m_SelectUIWindowItem = Item;

	m_SelectUIWindowInput->SetText(Item.c_str());

	if (Item == "MainUI")
		m_SelectUIWindow = m_Scene->GetViewport()->FindUIWindow<CMainUI>("MainUI");

	else if (Item == "PlaySlotUI")
		m_SelectUIWindow = m_Scene->GetViewport()->FindUIWindow<CPlaySlotUI>("PlaySlotUI");

	else if (Item == "SettingUI")
		m_SelectUIWindow = m_Scene->GetViewport()->FindUIWindow<CSettingUI>("SettingUI");

	else if (Item == "StartSceneUI")
		m_SelectUIWindow = m_Scene->GetViewport()->FindUIWindow<CStartSceneUI>("StartSceneUI");

	else if (Item == "BossUI")
		m_SelectUIWindow = m_Scene->GetViewport()->FindUIWindow<CBossUI>("BossUI");

	else if (Item == "EndingUI")
		m_SelectUIWindow = m_Scene->GetViewport()->FindUIWindow<CEndingUI>("EndingUI");

	if (m_SelectUIWindow)
		SetUIWindow(m_SelectUIWindow);

	CUIWidgetEditor* UIWidgetEditor = CEditorGUIManager::GetInst()->FindEditorWindow<CUIWidgetEditor>("UIWidgetEditor");
	UIWidgetEditor->SetSelectUIWindow(m_SelectUIWindow);
}

void CUIWindowEditor::ZOrderCallback()
{
	if (m_SelectUIWindow)
	{
		m_SelectUIWindow->SetZOrder(m_ZOrder->GetInt());
	}
}

void CUIWindowEditor::PosXCallback()
{
	if (m_SelectUIWindow)
	{
		m_SelectUIWindow->SetPosX(m_Pos[0]->GetFloat());
	}
}

void CUIWindowEditor::PosYCallback()
{
	if (m_SelectUIWindow)
	{
		m_SelectUIWindow->SetPosY(m_Pos[1]->GetFloat());
	}
}

void CUIWindowEditor::SizeXCallback()
{
	if (m_SelectUIWindow)
	{
		m_SelectUIWindow->SetSizeX(m_Size[0]->GetFloat());
	}
}

void CUIWindowEditor::SizeYCallback()
{
	if (m_SelectUIWindow)
	{
		m_SelectUIWindow->SetSizeY(m_Size[1]->GetFloat());
	}
}
