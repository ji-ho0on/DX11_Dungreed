#include "EditorUIWindow.h"
#include "PathManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"

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

CEditorUIWindow::CEditorUIWindow()
{
}

CEditorUIWindow::~CEditorUIWindow()
{
}

bool CEditorUIWindow::Init()
{
	// 처음 시작된 Scene으로 설정
	m_Scene = CSceneManager::GetInst()->GetScene();

	CEditorGroup* CurrentUIWindowGroup = CreateWidget<CEditorGroup>("CurrentUIWindowGroup");

	CEditorText* CurrentUIWindowText = CurrentUIWindowGroup->CreateWidget<CEditorText>("CurrentUIWindowText");
	CurrentUIWindowText->SetText("CurrentUIWindow");

	CEditorInput* CurrentUIWindowNameInput = CurrentUIWindowGroup->CreateWidget<CEditorInput>("CurrentUIWindowNameInput", 150.f, 30.f);
	CurrentUIWindowNameInput->SetHideName(CurrentUIWindowNameInput->GetName());
	CurrentUIWindowNameInput->ReadOnly(true);

	CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");

	CEditorGroup* UIWindowListGroup1 = CreateWidget<CEditorGroup>("UIWindowListGroup1");

	CEditorText* UIWindowListName = UIWindowListGroup1->CreateWidget<CEditorText>("UIWindowListName");
	UIWindowListName->SetText("UIWindowList");

	m_UIWindowListBox = UIWindowListGroup1->CreateWidget<CEditorListBox>("UIWindowListBox", 150.f);
	m_UIWindowListBox->SetHideName(m_UIWindowListBox->GetName());
	m_UIWindowListBox->SetPageItemCount(6);
	m_UIWindowListBox->SetSelectCallback<CEditorUIWindow>(this, &CEditorUIWindow::UIListBoxClickCallback);

	LoadUIDirectory();

	Line = CreateWidget<CEditorSameLine>("Line");


	CEditorGroup* UIWindowListGroup2 = CreateWidget<CEditorGroup>("UIWindowListGroup2");

	CEditorText* SelectSequenceName = UIWindowListGroup2->CreateWidget<CEditorText>("SelectUIWindowName");
	SelectSequenceName->SetText("SelectUIWindow");

	m_SelectUIWindowNameInput = UIWindowListGroup2->CreateWidget<CEditorInput>("SelectUIWindowNameInput", 150.f, 30.f);
	m_SelectUIWindowNameInput->SetHideName(m_SelectUIWindowNameInput->GetName());
	m_SelectUIWindowNameInput->ReadOnly(true);

	CEditorButton* UIWindowButton = UIWindowListGroup2->CreateWidget<CEditorButton>("Button", 150.f, 30.f);
	UIWindowButton->SetClickCallback<CEditorUIWindow>(this, &CEditorUIWindow::UIButton);


	return true;
}

void CEditorUIWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);
}

void CEditorUIWindow::SetScene(CScene* Scene)
{
	m_Scene = Scene;
}

void CEditorUIWindow::LoadUIDirectory()
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	Path[MAX_PATH] = {};

	strcpy_s(Path, Info->PathMultibyte);

	int	Length = (int)strlen(Path);

	// Root Path에서 Bin\을 지워준다.
	for (int i = Length - 2; i >= 0; --i)
	{
		if (Path[i] == '/' || Path[i] == '\\')
		{
			memset(&Path[i + 1], 0, sizeof(TCHAR) * (Length - i - 1));
			break;
		}
	}

	char	Directory[MAX_PATH] = {};

	strcpy_s(Directory, Path);

	// Editor의 UI폴더에 있는 파일을 읽어온다.
	strcat_s(Directory, "Include/UI/");

	for (const auto& file : std::filesystem::directory_iterator(Directory))
	{
		char	Name[64] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

		if (strcmp(Ext, ".cpp") == 0)
			continue;

		m_UIWindowListBox->AddItem(Name);
	}
}

void CEditorUIWindow::UIListBoxClickCallback(int Index, const std::string& Item)
{
	m_SelectUIWindowItem = Item;

	m_SelectUIWindowNameInput->SetText(Item.c_str());
}

void CEditorUIWindow::UIButton()
{
}
