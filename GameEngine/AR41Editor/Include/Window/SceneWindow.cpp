#include "SceneWindow.h"
#include "PathManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneCollision.h"
#include "Editor/EditorGUIManager.h"
#include "Engine.h"

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

// EditorWindow
#include "ObjectWindow.h"
#include "UIWindowEditor.h"
//#include "EditorUIWindow.h"

// SceneInfo
#include "../Scene/EditorDefaultScene.h"
#include "../Scene/TestSceneInfo.h"
#include "../Scene/MainScene.h"
#include "../Scene/LoadingScene.h"
#include "../Scene/TownScene.h"
#include "../Scene/BossScene.h"
#include "../Scene/BossEntranceScene.h"
#include "../Scene/NormalScene.h"
#include "../Scene/NormalScene1.h"
#include "../Scene/NormalScene2.h"
#include "../Scene/NormalScene3.h"
#include "../Scene/NormalScene4.h"
#include "../Scene/NormalScene5.h"
#include "../Scene/NormalScene6.h"
#include "../Scene/EndingScene.h"

CSceneWindow::CSceneWindow()
{
}

CSceneWindow::~CSceneWindow()
{
}

bool CSceneWindow::Init()
{
	CEditorTap* SceneTap = CreateWidget<CEditorTap>("SceneTap");

	// ========== Scene ==========
	SceneTap->AddItem("Scene");


	// ========== Scene Save ==========
	CEditorGroup* SceneSaveGroup = SceneTap->CreateWidget<CEditorGroup>("Scene", "SceneSaveGroup");

	CEditorText* SceneSaveText = SceneSaveGroup->CreateWidget<CEditorText>("SceneSaveText");
	SceneSaveText->SetText("SceneSave");

	m_SceneSaveName = SceneSaveGroup->CreateWidget<CEditorInput>("SceneSaveName");
	m_SceneSaveName->SetHideName(m_SceneSaveName->GetName());
	m_SceneSaveName->SetHintText("SaveName");
	m_SceneSaveName->SetSize(150.f, 30.f);


	CEditorButton* SceneSaveButton = SceneSaveGroup->CreateWidget<CEditorButton>("Scene Save", 150.f, 30.f);
	SceneSaveButton->SetColor(29, 47, 73, 255);
	SceneSaveButton->SetClickCallback<CSceneWindow>(this, &CSceneWindow::SceneSave);


	// ========== Scene Change ==========
	CEditorSameLine* Line = SceneTap->CreateWidget<CEditorSameLine>("Scene", "Line");
	Line->SetSpacing(30.f);

	CEditorGroup* SceneChangeGroup1 = SceneTap->CreateWidget<CEditorGroup>("Scene", "SceneChangeGroup1");


	CEditorText* SceneChangeText = SceneChangeGroup1->CreateWidget<CEditorText>("SceneChangeText");
	SceneChangeText->SetText("SceneChange");


	m_SceneList = SceneChangeGroup1->CreateWidget<CEditorListBox>("SceneListBox");
	m_SceneList->SetHideName(m_SceneList->GetName());
	m_SceneList->SetSize(150.f, 300.f);
	m_SceneList->SetPageItemCount(5);
	m_SceneList->SetSelectCallback<CSceneWindow>(this, &CSceneWindow::SceneClickCallback);

	LoadSceneDirectory();	// SceneListBox에 Scene 읽어와서 넣어주기


	Line = SceneTap->CreateWidget<CEditorSameLine>("Scene", "Line");

	CEditorGroup* SceneChangeGroup2 = SceneTap->CreateWidget<CEditorGroup>("Scene", "SceneChangeGroup2");


	CEditorText* SelectSceneText = SceneChangeGroup2->CreateWidget<CEditorText>("SelectSceneText");
	SelectSceneText->SetText("SelectScene");


	m_SelectSceneName = SceneChangeGroup2->CreateWidget<CEditorInput>("SelectSceneName");
	m_SelectSceneName->SetHideName(m_SelectSceneName->GetName());
	m_SelectSceneName->SetSize(150.f, 30.f);
	m_SelectSceneName->ReadOnly(true);


	CEditorButton* SceneChangeButton = SceneChangeGroup2->CreateWidget<CEditorButton>("Scene Change", 150.f, 30.f);
	SceneChangeButton->SetColor(29, 47, 73, 255);
	SceneChangeButton->SetClickCallback<CSceneWindow>(this, &CSceneWindow::SceneChange);

	SceneTap->CreateWidget<CEditorNewLine>("Scene", "NewLine");

	CEditorButton* PlayButton = SceneTap->CreateWidget<CEditorButton>("Scene", "Play", 80.f, 30.f);
	PlayButton->SetColor(29, 47, 73, 255);
	PlayButton->SetClickCallback<CSceneWindow>(this, &CSceneWindow::PlayButton);

	SceneTap->CreateWidget<CEditorSameLine>("Scene", "Line");

	CEditorButton* StopButton = SceneTap->CreateWidget<CEditorButton>("Scene", "Stop", 80.f, 30.f);
	StopButton->SetColor(29, 47, 73, 255);
	StopButton->SetClickCallback<CSceneWindow>(this, &CSceneWindow::StopButton);


	// ========== SceneInfo ==========
	SceneTap->AddItem("SceneInfo");


	// ========== SceneInfo Change ==========
	CEditorGroup* CurrentSceneInfoGroup = SceneTap->CreateWidget<CEditorGroup>("SceneInfo", "CurrentSceneInfoGroup");

	CEditorText* CurrentSceneInfoText = CurrentSceneInfoGroup->CreateWidget<CEditorText>("CurrentSceneInfoText");
	CurrentSceneInfoText->SetText("Current SceneInfo");

	m_CurrentSceneInfoName = CurrentSceneInfoGroup->CreateWidget<CEditorInput>("CurrentSceneInfoName");
	m_CurrentSceneInfoName->SetHideName(m_CurrentSceneInfoName->GetName());
	m_CurrentSceneInfoName->SetSize(150.f, 30.f);
	m_CurrentSceneInfoName->ReadOnly(true);


	Line = SceneTap->CreateWidget<CEditorSameLine>("SceneInfo", "Line");


	CEditorGroup* SceneInfoChangeGroup1 = SceneTap->CreateWidget<CEditorGroup>("SceneInfo", "SceneInfoChangeGroup1");

	CEditorText* SceneInfoChangeText = SceneInfoChangeGroup1->CreateWidget<CEditorText>("SceneInfoChangeText");
	SceneInfoChangeText->SetText("SceneInfo");


	m_SceneInfoList = SceneInfoChangeGroup1->CreateWidget<CEditorListBox>("SceneInfoListBox");
	m_SceneInfoList->SetHideName(m_SceneList->GetName());
	m_SceneInfoList->SetSize(150.f, 300.f);
	m_SceneInfoList->SetPageItemCount(5);
	m_SceneInfoList->SetSelectCallback<CSceneWindow>(this, &CSceneWindow::SceneInfoClickCallback);

	LoadSceneInfoDirectory();	// SceneInfoListBox에 저장된 SceneInfo들 읽어와서 넣어주기


	Line = SceneTap->CreateWidget<CEditorSameLine>("SceneInfo", "Line");

	CEditorGroup* SceneInfoChangeGroup2 = SceneTap->CreateWidget<CEditorGroup>("SceneInfo", "SceneInfoChangeGroup2");


	CEditorText* SelectSceneInfoText = SceneInfoChangeGroup2->CreateWidget<CEditorText>("SelectSceneInfoText");
	SelectSceneInfoText->SetText("SelectSceneInfo");


	m_SelectSceneInfoName = SceneInfoChangeGroup2->CreateWidget<CEditorInput>("SelectSceneInfoName");
	m_SelectSceneInfoName->SetHideName(m_SelectSceneInfoName->GetName());
	m_SelectSceneInfoName->SetSize(150.f, 30.f);
	m_SelectSceneInfoName->ReadOnly(true);


	CEditorButton* SceneCreateButton = SceneInfoChangeGroup2->CreateWidget<CEditorButton>("Scene Create", 150.f, 30.f);
	SceneCreateButton->SetColor(29, 47, 73, 255);
	SceneCreateButton->SetClickCallback<CSceneWindow>(this, &CSceneWindow::SceneCreate);






	// ========== Section2D ==========
	SceneTap->AddItem("Section2D");


	/* CountX, CountY, WorldStartX, WorldStartY, SectionSizeX, SectionSizeY 총 6개 Data가 필요 */
	CEditorLabel* Label = SceneTap->CreateWidget<CEditorLabel>("Section2D", "Section2D", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	Line = SceneTap->CreateWidget<CEditorSameLine>("Section2D", "Line");

	Label = SceneTap->CreateWidget<CEditorLabel>("Section2D", "X", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	Line = SceneTap->CreateWidget<CEditorSameLine>("Section2D", "Line");

	Label = SceneTap->CreateWidget<CEditorLabel>("Section2D", "Y", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);


	Label = SceneTap->CreateWidget<CEditorLabel>("Section2D", "Count", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	Line = SceneTap->CreateWidget<CEditorSameLine>("Section2D", "Line");

	CEditorInput* Section2DCountXInput = SceneTap->CreateWidget<CEditorInput>("Section2D", "Section2DCountXInput", 100.f, 30.f);
	Section2DCountXInput->SetHideName(Section2DCountXInput->GetName());
	Section2DCountXInput->SetInputType(EImGuiInputType::Int);

	Line = SceneTap->CreateWidget<CEditorSameLine>("Section2D", "Line");

	CEditorInput* Section2DCountYInput = SceneTap->CreateWidget<CEditorInput>("Section2D", "Section2DCountYInput", 100.f, 30.f);
	Section2DCountYInput->SetHideName(Section2DCountYInput->GetName());
	Section2DCountYInput->SetInputType(EImGuiInputType::Int);


	Label = SceneTap->CreateWidget<CEditorLabel>("Section2D", "WorldStart", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	Line = SceneTap->CreateWidget<CEditorSameLine>("Section2D", "Line");

	CEditorInput* Section2DWorldStartXInput = SceneTap->CreateWidget<CEditorInput>("Section2D", "Section2DWorldStartXInput", 100.f, 30.f);
	Section2DWorldStartXInput->SetHideName(Section2DWorldStartXInput->GetName());
	Section2DWorldStartXInput->SetInputType(EImGuiInputType::Float);

	Line = SceneTap->CreateWidget<CEditorSameLine>("Section2D", "Line");

	CEditorInput* Section2DWorldStartYInput = SceneTap->CreateWidget<CEditorInput>("Section2D", "Section2DWorldStartYInput", 100.f, 30.f);
	Section2DWorldStartYInput->SetHideName(Section2DWorldStartYInput->GetName());
	Section2DWorldStartYInput->SetInputType(EImGuiInputType::Float);


	Label = SceneTap->CreateWidget<CEditorLabel>("Section2D", "SectionSize", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	Line = SceneTap->CreateWidget<CEditorSameLine>("Section2D", "Line");

	CEditorInput* Section2DSizeXInput = SceneTap->CreateWidget<CEditorInput>("Section2D", "Section2DSizeXInput", 100.f, 30.f);
	Section2DSizeXInput->SetHideName(Section2DSizeXInput->GetName());
	Section2DSizeXInput->SetInputType(EImGuiInputType::Float);

	Line = SceneTap->CreateWidget<CEditorSameLine>("Section2D", "Line");

	CEditorInput* Section2DSizeYInput = SceneTap->CreateWidget<CEditorInput>("Section2D", "Section2DSizeYInput", 100.f, 30.f);
	Section2DSizeYInput->SetHideName(Section2DSizeYInput->GetName());
	Section2DSizeYInput->SetInputType(EImGuiInputType::Float);

	CEditorButton* Section2DCreateButton = SceneTap->CreateWidget<CEditorButton>("Section2D", "CreateSection2D", 315.f, 30.f);
	Section2DCreateButton->SetColor(29, 47, 73, 255);
	Section2DCreateButton->SetClickCallback<CSceneWindow>(this, &CSceneWindow::CreateSection2D);


	// ========== Section3D ==========
	SceneTap->AddItem("Section3D");

	Label = SceneTap->CreateWidget<CEditorLabel>("Section3D", "Section3D", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	Line = SceneTap->CreateWidget<CEditorSameLine>("Section3D", "Line");

	Label = SceneTap->CreateWidget<CEditorLabel>("Section3D", "X", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	Line = SceneTap->CreateWidget<CEditorSameLine>("Section3D", "Line");

	Label = SceneTap->CreateWidget<CEditorLabel>("Section3D", "Y", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	Line = SceneTap->CreateWidget<CEditorSameLine>("Section3D", "Line");

	Label = SceneTap->CreateWidget<CEditorLabel>("Section3D", "Z", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);


	Label = SceneTap->CreateWidget<CEditorLabel>("Section3D", "Count", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	Line = SceneTap->CreateWidget<CEditorSameLine>("Section3D", "Line");

	CEditorInput* Section3DCountXInput = SceneTap->CreateWidget<CEditorInput>("Section3D", "Section3DCountXInput", 100.f, 30.f);
	Section3DCountXInput->SetHideName(Section3DCountXInput->GetName());
	Section3DCountXInput->SetInputType(EImGuiInputType::Int);

	Line = SceneTap->CreateWidget<CEditorSameLine>("Section3D", "Line");

	CEditorInput* Section3DCountYInput = SceneTap->CreateWidget<CEditorInput>("Section3D", "Section3DCountYInput", 100.f, 30.f);
	Section3DCountYInput->SetHideName(Section3DCountYInput->GetName());
	Section3DCountYInput->SetInputType(EImGuiInputType::Int);

	Line = SceneTap->CreateWidget<CEditorSameLine>("Section3D", "Line");

	CEditorInput* Section3DCountZInput = SceneTap->CreateWidget<CEditorInput>("Section3D", "Section3DCountZInput", 100.f, 30.f);
	Section3DCountZInput->SetHideName(Section3DCountZInput->GetName());
	Section3DCountZInput->SetInputType(EImGuiInputType::Int);


	Label = SceneTap->CreateWidget<CEditorLabel>("Section3D", "WorldStart", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	Line = SceneTap->CreateWidget<CEditorSameLine>("Section3D", "Line");

	CEditorInput* Section3DWorldStartXInput = SceneTap->CreateWidget<CEditorInput>("Section3D", "Section3DWorldStartXInput", 100.f, 30.f);
	Section3DWorldStartXInput->SetHideName(Section3DWorldStartXInput->GetName());
	Section3DWorldStartXInput->SetInputType(EImGuiInputType::Float);

	Line = SceneTap->CreateWidget<CEditorSameLine>("Section3D", "Line");

	CEditorInput* Section3DWorldStartYInput = SceneTap->CreateWidget<CEditorInput>("Section3D", "Section3DWorldStartYInput", 100.f, 30.f);
	Section3DWorldStartYInput->SetHideName(Section3DWorldStartYInput->GetName());
	Section3DWorldStartYInput->SetInputType(EImGuiInputType::Float);

	Line = SceneTap->CreateWidget<CEditorSameLine>("Section3D", "Line");

	CEditorInput* Section3DWorldStartZInput = SceneTap->CreateWidget<CEditorInput>("Section3D", "Section3DWorldStartZInput", 100.f, 30.f);
	Section3DWorldStartZInput->SetHideName(Section3DWorldStartZInput->GetName());
	Section3DWorldStartZInput->SetInputType(EImGuiInputType::Float);


	Label = SceneTap->CreateWidget<CEditorLabel>("Section3D", "SectionSize", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	Line = SceneTap->CreateWidget<CEditorSameLine>("Section3D", "Line");

	CEditorInput* Section3DSizeXInput = SceneTap->CreateWidget<CEditorInput>("Section3D", "Section3DSizeXInput", 100.f, 30.f);
	Section3DSizeXInput->SetHideName(Section3DSizeXInput->GetName());
	Section3DSizeXInput->SetInputType(EImGuiInputType::Float);

	Line = SceneTap->CreateWidget<CEditorSameLine>("Section3D", "Line");

	CEditorInput* Section3DSizeYInput = SceneTap->CreateWidget<CEditorInput>("Section3D", "Section3DSizeYInput", 100.f, 30.f);
	Section3DSizeYInput->SetHideName(Section3DSizeYInput->GetName());
	Section3DSizeYInput->SetInputType(EImGuiInputType::Float);

	Line = SceneTap->CreateWidget<CEditorSameLine>("Section3D", "Line");

	CEditorInput* Section3DSizeZInput = SceneTap->CreateWidget<CEditorInput>("Section3D", "Section3DSizeZInput", 100.f, 30.f);
	Section3DSizeZInput->SetHideName(Section3DSizeZInput->GetName());
	Section3DSizeZInput->SetInputType(EImGuiInputType::Float);


	CEditorButton* Section3DCreateButton = SceneTap->CreateWidget<CEditorButton>("Section3D", "CreateSection3D", 425.f, 30.f);
	Section3DCreateButton->SetColor(29, 47, 73, 255);
	Section3DCreateButton->SetClickCallback<CSceneWindow>(this, &CSceneWindow::CreateSection3D);

	return true;
}

void CSceneWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);
}

void CSceneWindow::SceneSave()
{
	std::string Name = m_SceneSaveName->GetText();

	if (Name.empty())
		return;

	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	FullPath[MAX_PATH] = {};

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, "Scene/");
	strcat_s(FullPath, Name.c_str());
	strcat_s(FullPath, ".scn");

	CScene* Scene = CSceneManager::GetInst()->GetScene();

	Scene->SetName(Name);

	Scene->Save(FullPath);

	if (!m_SceneList->CheckItem(Name))
		m_SceneList->AddItem(Name);
}

void CSceneWindow::SceneChange()
{
	CScene* Scene = CSceneManager::GetInst()->GetScene();

	if (Scene->GetName() == m_SelectSceneItem && !m_SelectSceneItem.empty())
		return;

	CSceneManager::GetInst()->CreateNextScene();
	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();

	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	FullPath[MAX_PATH] = {};

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, "Scene/");
	strcat_s(FullPath, m_SelectSceneItem.c_str());
	strcat_s(FullPath, ".scn");

	NextScene->Load(FullPath);

	// 완료된 GameObject 목록을 ObjectWindow에 추가한다.
	CObjectWindow* ObjectWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CObjectWindow>("ObjectWindow");
	
	// 추가하기 전에 원래 있던 GameObject 목록을 날려준다.
	ObjectWindow->ClearItem();

	std::vector<HierarchyObjectName> vecName;

	NextScene->GetAllGameObjectHierarchyName(vecName);

	size_t	Size = vecName.size();

	for (size_t i = 0; i < Size; ++i)
	{
		ObjectWindow->AddItem(vecName[i].Obj, vecName[i].Name);
	}

	// SceneInfo 이름을 넣어준다.
	m_CurrentSceneInfoName->SetText(NextScene->GetSceneInfo()->GetClassTypeName().c_str());

	// EditorUItWindow에 변경된 Scene을 적용한다.
	CUIWindowEditor* UIWindowEditor = CEditorGUIManager::GetInst()->FindEditorWindow<CUIWindowEditor>("UIWindowEditor");
	UIWindowEditor->SetScene(NextScene);
}

void CSceneWindow::PlayButton()
{
	CEngine::GetInst()->SetDeltaTimeScale(1.f);
}

void CSceneWindow::StopButton()
{
	CEngine::GetInst()->SetDeltaTimeScale(0.f);
}

void CSceneWindow::SceneClickCallback(int Index, const std::string& Item)
{
	m_SelectSceneItem = Item;

	m_SelectSceneName->SetText(Item.c_str());
}

void CSceneWindow::LoadSceneDirectory()
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	Path[MAX_PATH] = {};

	strcpy_s(Path, Info->PathMultibyte);
	strcat_s(Path, "Scene/");

	for (const auto& file : std::filesystem::directory_iterator(Path))
	{
		char	Name[64] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

		m_SceneList->AddItem(Name);
	}
}

void CSceneWindow::CreateSection2D()
{
	CScene* Scene = CSceneManager::GetInst()->GetScene();

	CEditorTap* SceneTap = (CEditorTap*)FindWidget("SceneTap");

	int CountX = SceneTap->FindWidget<CEditorInput>("Section2D", "##Section2DCountXInput")->GetInt();
	int CountY = SceneTap->FindWidget<CEditorInput>("Section2D", "##Section2DCountYInput")->GetInt();

	Vector2 WorldStart = Vector2(SceneTap->FindWidget<CEditorInput>("Section2D", "##Section2DWorldStartXInput")->GetFloat(), SceneTap->FindWidget<CEditorInput>("Section2D", "##Section2DWorldStartYInput")->GetFloat());
	Vector2 SectionSize = Vector2(SceneTap->FindWidget<CEditorInput>("Section2D", "##Section2DSizeXInput")->GetFloat(), SceneTap->FindWidget<CEditorInput>("Section2D", "##Section2DSizeYInput")->GetFloat());
	
	if (CountX < 0)
		return;

	else if (CountY < 0)
		return;

	else if (WorldStart.x < 0.f)
		return;

	else if (WorldStart.y < 0.f)
		return;

	else if (SectionSize.x < 0.f)
		return;

	else if (SectionSize.y < 0.f)
		return;

	Scene->GetCollisionManager()->CreateSection2D(CountX, CountY, WorldStart, SectionSize);
}

void CSceneWindow::CreateSection3D()
{
	CScene* Scene = CSceneManager::GetInst()->GetScene();

	CEditorTap* SceneTap = (CEditorTap*)FindWidget("SceneTap");

	int CountX = SceneTap->FindWidget<CEditorInput>("Section3D", "##Section3DCountXInput")->GetInt();
	int CountY = SceneTap->FindWidget<CEditorInput>("Section3D", "##Section3DCountYInput")->GetInt();
	int CountZ = SceneTap->FindWidget<CEditorInput>("Section3D", "##Section3DCountZInput")->GetInt();

	Vector3 WorldStart = Vector3(SceneTap->FindWidget<CEditorInput>("Section3D", "##Section3DWorldStartXInput")->GetFloat(), SceneTap->FindWidget<CEditorInput>("Section3D", "##Section3DWorldStartYInput")->GetFloat(), SceneTap->FindWidget<CEditorInput>("Section3D", "##Section3DWorldStartZInput")->GetFloat());
	Vector3 SectionSize = Vector3(SceneTap->FindWidget<CEditorInput>("Section3D", "##Section3DSizeXInput")->GetFloat(), SceneTap->FindWidget<CEditorInput>("Section3D", "##Section3DSizeYInput")->GetFloat(), SceneTap->FindWidget<CEditorInput>("Section3D", "##Section3DSizeZInput")->GetFloat());

	if (CountX < 0)
		return;

	else if (CountY < 0)
		return;

	else if (CountZ < 0)
		return;

	else if (WorldStart.x < 0.f)
		return;

	else if (WorldStart.y < 0.f)
		return;

	else if (WorldStart.z < 0.f)
		return;

	else if (SectionSize.x < 0.f)
		return;

	else if (SectionSize.y < 0.f)
		return;

	else if (SectionSize.x < 0.f)
		return;

	else if (SectionSize.z < 0.f)
		return;

	Scene->GetCollisionManager()->CreateSection3D(CountX, CountY, CountZ, WorldStart, SectionSize);
}

void CSceneWindow::SceneInfoClickCallback(int Index, const std::string& Item)
{
	m_SelectSceneInfoItem = Item;

	m_SelectSceneInfoName->SetText(Item.c_str());
}

void CSceneWindow::LoadSceneInfoDirectory()
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

	// Editor의 Scene폴더에 있는 파일을 읽어온다.
	strcat_s(Directory, "Include/Scene/");

	for (const auto& file : std::filesystem::directory_iterator(Directory))
	{
		char	Name[64] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

		// cpp 파일은 넘어가고 헤더 파일만 읽어서 중복을 방지한다.
		if (strcmp(Ext, ".cpp") == 0)
			continue;

		m_SceneInfoList->AddItem(Name);
	}
}

void CSceneWindow::SceneCreate()
{
	if (m_SelectSceneInfoName->Empty())
		return;

	CSceneManager::GetInst()->CreateNextScene();

	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();

	std::string SceneInfoName = m_SelectSceneInfoName->GetText();

	//CSceneInfo* SceneInfoCDO = CScene::FindSceneInfoCDO(SceneInfoName);
	//CSceneInfo* SceneInfo = SceneInfoCDO->Clone();

	//NextScene->SetSceneInfoByCDO(SceneInfo);

	if (SceneInfoName == "EditorDefaultScene")
		NextScene->CreateSceneInfo<CEditorDefaultScene>();

	else if(SceneInfoName == "TestSceneInfo")
		NextScene->CreateSceneInfo<CTestSceneInfo>();

	else if (SceneInfoName == "MainScene")
		NextScene->CreateSceneInfo<CMainScene>();

	else if (SceneInfoName == "LoadingScene")
		NextScene->CreateSceneInfo<CLoadingScene>();

	else if (SceneInfoName == "TownScene")
		NextScene->CreateSceneInfo<CTownScene>();

	else if (SceneInfoName == "BossScene")
		NextScene->CreateSceneInfo<CBossScene>();

	else if (SceneInfoName == "BossEntranceScene")
		NextScene->CreateSceneInfo<CBossEntranceScene>();

	else if (SceneInfoName == "NormalScene")
		NextScene->CreateSceneInfo<CNormalScene>();

	else if (SceneInfoName == "NormalScene1")
		NextScene->CreateSceneInfo<CNormalScene1>();

	else if (SceneInfoName == "NormalScene2")
		NextScene->CreateSceneInfo<CNormalScene2>();

	else if (SceneInfoName == "NormalScene3")
		NextScene->CreateSceneInfo<CNormalScene3>();

	else if (SceneInfoName == "NormalScene4")
		NextScene->CreateSceneInfo<CNormalScene4>();

	else if (SceneInfoName == "NormalScene5")
		NextScene->CreateSceneInfo<CNormalScene5>();

	else if (SceneInfoName == "NormalScene6")
		NextScene->CreateSceneInfo<CNormalScene6>();

	else if (SceneInfoName == "EndingScene")
		NextScene->CreateSceneInfo<CEndingScene>();

	m_CurrentSceneInfoName->SetText(m_SelectSceneInfoName->GetText());

	// ObjectWindow에 바뀐 Scene의 Object들을 전달한다.
	CObjectWindow* ObjectWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CObjectWindow>("ObjectWindow");

	// 추가하기 전에 원래 있던 GameObject 목록을 날려준다.
	ObjectWindow->ClearItem();

	std::vector<HierarchyObjectName> vecName;

	NextScene->GetAllGameObjectHierarchyName(vecName);

	size_t	Size = vecName.size();

	for (size_t i = 0; i < Size; ++i)
	{
		ObjectWindow->AddItem(vecName[i].Obj, vecName[i].Name);
	}

	// EditorUItWindow에 변경된 Scene을 적용한다.
	CUIWindowEditor* UIWindowEditor = CEditorGUIManager::GetInst()->FindEditorWindow<CUIWindowEditor>("UIWindowEditor");
	UIWindowEditor->SetScene(NextScene);
}
