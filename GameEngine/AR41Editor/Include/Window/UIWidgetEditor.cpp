#include "UIWidgetEditor.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "UI/UIWindow.h"
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

// UIWidgetList
#include "UI/DefaultUIWidgetList.h"
#include "UI/UIButtonWidgetList.h"
#include "UI/UIImageWidgetList.h"
#include "UI/UITextWidgetList.h"
#include "UI/UINumberWidgetList.h"
#include "UI/UIProgressBarWidgetList.h"

CUIWidgetEditor::CUIWidgetEditor()
{
}

CUIWidgetEditor::~CUIWidgetEditor()
{
	ClearWidget();

	size_t	Size = m_vecUIWidgetList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		AddWidget(m_vecUIWidgetList[i]);
	}
}

CUIWidgetList* CUIWidgetEditor::GetUIWidgetList(EUIWidgetType Type)
{
	if ((int)Type <= (int)EUIWidgetType::Max)
		return m_vecUIWidgetList[(int)Type];

	return nullptr;
}

void CUIWidgetEditor::SetSelectUIWindow(CUIWindow* UIWindow)
{
	m_SelectUIWindow = UIWindow;

	if (m_SelectUIWindow)
		((CDefaultUIWidgetList*)m_vecUIWidgetList[(int)EUIWidgetType::Default])->LoadUIWidget(m_SelectUIWindow);
}

void CUIWidgetEditor::SetSelectUIWidget(CUIWidget* UIWidget)
{
	// 처음 선택시 m_SelectUIWidget가 없으면 바로 위젯을 바꿔줌
	if (!m_SelectUIWidget)
	{
		ClearWidget();
		ChangeWidget(UIWidget);
	}

	// m_SelectUIWidget가 있고 UIWidget가 들어왔을 경우 서로 다른 UIWidget라면 위젯을 바꿔줌
	if (m_SelectUIWidget && UIWidget)
	{
		if (m_SelectUIWidget != UIWidget)
		{
			ClearWidget();

			// 타입에 맞는 GUI 추가
			ChangeWidget(UIWidget);
		}
	}

	// m_SelectUIWidget를 들어온 UIWidget로 교체
	m_SelectUIWidget = UIWidget;
}

void CUIWidgetEditor::CreateEditorWidgetList(EUIWidgetType Type)
{
	CUIWidgetList* UIWidgetList = nullptr;

	switch (Type)
	{
	case EUIWidgetType::Default:
		UIWidgetList = CreateWidgetEmpty<CDefaultUIWidgetList>("Default");
		break;
	case EUIWidgetType::Button:
		UIWidgetList = CreateWidgetEmpty<CUIButtonWidgetList>("UIButton");
		break;
	case EUIWidgetType::Image:
		UIWidgetList = CreateWidgetEmpty<CUIImageWidgetList>("UIImage");
		break;
	case EUIWidgetType::Text:
		UIWidgetList = CreateWidgetEmpty<CUITextWidgetList>("UIText");
		break;
	case EUIWidgetType::Number:
		UIWidgetList = CreateWidgetEmpty<CUINumberWidgetList>("UINumber");
		break;
	case EUIWidgetType::ProgressBar:
		UIWidgetList = CreateWidgetEmpty<CUIProgressBarWidgetList>("UIProgressBar");
		break;
	}

	if (!UIWidgetList)
		return;

	UIWidgetList->m_UIWidgetEditor = this;

	m_vecUIWidgetList[(int)Type] = UIWidgetList;
}

void CUIWidgetEditor::ChangeWidget(CUIWidget* UIWidget)
{
	if (!UIWidget)
		return;

	AddWidget(m_vecUIWidgetList[(int)EUIWidgetType::Default]);
	((CDefaultUIWidgetList*)m_vecUIWidgetList[(int)EUIWidgetType::Default])->SetUIWidgetContents(UIWidget);

	std::string UIWidgetTypeName = UIWidget->GetWidgetTypeName();

	if (UIWidgetTypeName == "UIButton")
	{
		AddWidget(m_vecUIWidgetList[(int)EUIWidgetType::Button]);
		((CUIButtonWidgetList*)m_vecUIWidgetList[(int)EUIWidgetType::Button])->SetUIWidgetContents(UIWidget);
	}

	else if (UIWidgetTypeName == "UIImage")
	{
		AddWidget(m_vecUIWidgetList[(int)EUIWidgetType::Image]);
		((CUIImageWidgetList*)m_vecUIWidgetList[(int)EUIWidgetType::Image])->SetUIWidgetContents(UIWidget);
	}

	else if (UIWidgetTypeName == "UIText")
	{
		AddWidget(m_vecUIWidgetList[(int)EUIWidgetType::Text]);
		((CUITextWidgetList*)m_vecUIWidgetList[(int)EUIWidgetType::Text])->SetUIWidgetContents(UIWidget);
	}

	else if (UIWidgetTypeName == "UINumber")
	{
		AddWidget(m_vecUIWidgetList[(int)EUIWidgetType::Number]);
		((CUINumberWidgetList*)m_vecUIWidgetList[(int)EUIWidgetType::Number])->SetUIWidgetContents(UIWidget);
	}

	else if (UIWidgetTypeName == "UIProgressBar")
	{
		AddWidget(m_vecUIWidgetList[(int)EUIWidgetType::ProgressBar]);
		((CUIProgressBarWidgetList*)m_vecUIWidgetList[(int)EUIWidgetType::ProgressBar])->SetUIWidgetContents(UIWidget);
	}
}

bool CUIWidgetEditor::Init()
{
	m_vecUIWidgetList.resize((size_t)EUIWidgetType::Max);

	for (int i = 0; i < (int)EUIWidgetType::Max; ++i)
	{
		CreateEditorWidgetList((EUIWidgetType)i);
	}

	ClearWidget();

	AddWidget(m_vecUIWidgetList[(int)EUIWidgetType::Default]);

    return true;
}

void CUIWidgetEditor::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);
}