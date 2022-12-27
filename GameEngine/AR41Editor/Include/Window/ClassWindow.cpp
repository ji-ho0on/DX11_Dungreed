#include "ClassWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorTree.h"
#include "PathManager.h"
#include "Editor/EditorGUIManager.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"

// Window
#include "ObjectWindow.h"
#include "ComponentWindow.h"

// GmaeObject
#include "../GameObject/Player2D.h"
#include "../GameObject/Bullet.h"
#include "../GameObject/Monster.h"
#include "../GameObject/Bird.h"

// Component
#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/TargetArm.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderOBB2D.h"
#include "Component/ColliderPixel.h"
#include "Component/ColliderLine2D.h"
#include "Component/TileMapComponent.h"

CClassWindow::CClassWindow()
{
}

CClassWindow::~CClassWindow()
{
}

bool CClassWindow::Init()
{
	// ===================== ObjectClass =====================
	CEditorTree<void*>* Object = CreateWidget<CEditorTree<void*>>("Object");
	Object->SetHideName(Object->GetName());
	
	Object->AddItem(nullptr, "ObjectClass");
	Object->FindItem("ObjectClass")->AddFlag(ImGuiTreeNodeFlags_DefaultOpen);

	CEditorLabel* Label = Object->CreateWidget<CEditorLabel>("ObjectClass", "Object Name");

	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(150.f, 30.f);

	CEditorSameLine* Line = Object->CreateWidget<CEditorSameLine>("ObjectClass", "Line");

	m_ObjectSelectName = Object->CreateWidget<CEditorInput>("ObjectClass", "ObjectName");

	m_ObjectSelectName->SetHideName(m_ObjectSelectName->GetName());
	m_ObjectSelectName->SetSize(150.f, 30.f);
	m_ObjectSelectName->ReadOnly(true);

	m_ObjectList = Object->CreateWidget<CEditorListBox>("ObjectClass", "ObjectListBox");

	m_ObjectList->SetHideName(m_ObjectList->GetName());
	m_ObjectList->SetSize(150.f, 300.f);
	m_ObjectList->SetPageItemCount(5);
	m_ObjectList->SetSelectCallback<CClassWindow>(this, &CClassWindow::ObjectClickCallback);

	Line = Object->CreateWidget<CEditorSameLine>("ObjectClass", "Line");

	CEditorButton* CreateObjectButton = Object->CreateWidget<CEditorButton>("ObjectClass", "Create");

	CreateObjectButton->SetColor(29, 47, 73, 255);
	CreateObjectButton->SetSize(60.f, 30.f);
	CreateObjectButton->SetClickCallback<CClassWindow>(this, &CClassWindow::ObjectCreateCallback);


	// ===================== ComponentClass =====================
	CEditorTree<void*>* Component = CreateWidget<CEditorTree<void*>>("Component");
	Component->SetHideName(Component->GetName());

	Component->AddItem(nullptr, "ComponentClass");
	Component->FindItem("ComponentClass")->AddFlag(ImGuiTreeNodeFlags_DefaultOpen);

	Label = Component->CreateWidget<CEditorLabel>("ComponentClass", "Component Name");

	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(150.f, 30.f);

	Line = Component->CreateWidget<CEditorSameLine>("ComponentClass", "Line");

	m_ComponentSelectName = Component->CreateWidget<CEditorInput>("ComponentClass", "ComponentName");

	m_ComponentSelectName->SetHideName(m_ComponentSelectName->GetName());
	m_ComponentSelectName->SetSize(150.f, 30.f);
	m_ComponentSelectName->ReadOnly(true);

	m_ComponentList = Component->CreateWidget<CEditorListBox>("ComponentClass", "ComponentListBox");

	m_ComponentList->SetHideName(m_ComponentList->GetName());
	m_ComponentList->SetSize(150.f, 300.f);
	m_ComponentList->SetPageItemCount(5);
	m_ComponentList->SetSelectCallback<CClassWindow>(this, &CClassWindow::ComponentClickCallback);

	Line = Component->CreateWidget<CEditorSameLine>("ComponentClass", "Line");

	CEditorButton* CreateComponentButton = Component->CreateWidget<CEditorButton>("ComponentClass", "Create");

	CreateComponentButton->SetColor(29, 47, 73, 255);
	CreateComponentButton->SetSize(60.f, 30.f);
	CreateComponentButton->SetClickCallback<CClassWindow>(this, &CClassWindow::ComponentCreateCallback);

	LoadGameObjectName();

	LoadComponentName();

	return true;
}

void CClassWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);
}

void CClassWindow::ObjectClickCallback(int Index, const std::string& Item)
{
	m_SelectObjectItem = Item;

	m_ObjectSelectName->SetText(Item.c_str());
}

void CClassWindow::ComponentClickCallback(int Index, const std::string& Item)
{
	m_SelectComponentItem = Item;

	m_ComponentSelectName->SetText(Item.c_str());
}

void CClassWindow::ObjectCreateCallback()
{
	CScene* Scene = CSceneManager::GetInst()->GetScene();

	CGameObject* Obj = nullptr;

	if (m_SelectObjectItem == "")
		return;

	CGameObject* ObjCDO = CGameObject::FindCDO(m_SelectObjectItem);
	Obj = ObjCDO->Clone();

	Scene->CreateObjectByCDO(m_SelectObjectItem, Obj);

	//if (m_SelectObjectItem == "Player2D")
	//	Obj = Scene->CreateObject<CPlayer2D>("Player2D");


	CObjectWindow* ObjectWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CObjectWindow>("ObjectWindow");

	if (ObjectWindow)
	{
		ObjectWindow->AddItem(Obj, m_SelectObjectItem);
	}
}

void CClassWindow::ComponentCreateCallback()
{
	CScene* Scene = CSceneManager::GetInst()->GetScene();

	CObjectWindow* ObjectWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CObjectWindow>("ObjectWindow");
	CComponentWindow* ComponentWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CComponentWindow>("ComponentWindow");

	CGameObject* SelectObject = ObjectWindow->GetSelectObject();

	if (!SelectObject)
		return;

	CSceneComponent* SelectComponent = (CSceneComponent*)ComponentWindow->GetSelectComponent();

	if (!SelectComponent)
	{
		SelectComponent = SelectObject->GetRootComponent();
	}

	std::string	Name;

	CSceneComponent* NewComponent = nullptr;	

	if (m_SelectComponentItem == "SpriteComponent")
	{
		Name = "SpriteComponent(SpriteComponent)";
		NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CSpriteComponent>("SpriteComponent");
	}

	else if (m_SelectComponentItem == "SceneComponent")
	{
		Name = "SceneComponent(SceneComponent)";
		NewComponent = SelectObject->CreateComponent<CSceneComponent>("SceneComponent");
	}

	else if (m_SelectComponentItem == "TargetArm")
	{
		Name = "TargetArm(TargetArm)";
		NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CTargetArm>("TargetArm");
	}

	else if (m_SelectComponentItem == "CameraComponent")
	{
		Name = "CameraComponent(CameraComponent)";
		NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CCameraComponent>("CameraComponent");
	}

	else if (m_SelectComponentItem == "ColliderBox2D")
	{
		Name = "ColliderBox2D(ColliderBox2D)";
		NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CColliderBox2D>("ColliderBox2D");
	}

	else if (m_SelectComponentItem == "ColliderSphere2D")
	{
		Name = "ColliderSphere2D(ColliderSphere2D)";
		NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CColliderSphere2D>("ColliderSphere2D");
	}

	else if (m_SelectComponentItem == "ColliderOBB2D")
	{
		Name = "ColliderOBB2D(ColliderOBB2D)";
		NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CColliderOBB2D>("ColliderOBB2D");
	}

	else if (m_SelectComponentItem == "ColliderPixel")
	{
		Name = "ColliderPixel(ColliderPixel)";
		NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CColliderPixel>("ColliderPixel");
	}

	else if (m_SelectComponentItem == "ColliderLine2D")
	{
		Name = "ColliderLine2D(ColliderLine2D)";
		NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CColliderLine2D>("ColliderLine2D");
	}

	else if (m_SelectComponentItem == "TileMapComponent")
	{
		Name = "TileMapComponent(TileMapComponent)";
		NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CTileMapComponent>("TileMapComponent");
	}

	if (SelectComponent)
	{
		std::string	ParentName = SelectComponent->GetName() + "(" + SelectComponent->GetComponentTypeName() + ")";

		SelectComponent->AddChild(NewComponent);

		ComponentWindow->AddItem((CComponent*)NewComponent, Name, ParentName);
	}

	else
	{
		std::string	ObjName = SelectObject->GetName() + "(" + SelectObject->GetObjectTypeName() + ")";

		ComponentWindow->AddItem((CComponent*)NewComponent, Name, ObjName);
	}
}

void CClassWindow::LoadGameObjectName()
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

	// Editor의 GameObject폴더에 있는 파일을 읽어온다.
	strcat_s(Directory, "Include/GameObject/");

	for (const auto& file : std::filesystem::directory_iterator(Directory))
	{
		char	Name[64] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

		if (strcmp(Ext, ".cpp") == 0)
			continue;

		m_ObjectList->AddItem(Name);
	}

	Length = (int)strlen(Path);

	// Root Path에서 Bin\을 지워준다.
	for (int i = Length - 2; i >= 0; --i)
	{
		if (Path[i] == '/' || Path[i] == '\\')
		{
			memset(&Path[i + 1], 0, sizeof(TCHAR) * (Length - i - 1));
			break;
		}
	}

	memset(Directory, 0, MAX_PATH);
	strcpy_s(Directory, Path);

	// Editor의 GameObject폴더에 있는 파일을 읽어온다.
	strcat_s(Directory, "Engine/Include/GameObject/");

	for (const auto& file : std::filesystem::directory_iterator(Directory))
	{
		char	Name[64] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

		if (strcmp(Ext, ".cpp") == 0)
			continue;

		m_ObjectList->AddItem(Name);
	}
}

void CClassWindow::LoadComponentName()
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

	// Editor의 Component폴더에 있는 파일을 읽어온다.
	strcat_s(Directory, "Include/Component/");

	for (const auto& file : std::filesystem::directory_iterator(Directory))
	{
		char	Name[64] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

		if (strcmp(Ext, ".cpp") == 0)
			continue;

		m_ComponentList->AddItem(Name);
	}

	Length = (int)strlen(Path);

	// Root Path에서 Bin\을 지워준다.
	for (int i = Length - 2; i >= 0; --i)
	{
		if (Path[i] == '/' || Path[i] == '\\')
		{
			memset(&Path[i + 1], 0, sizeof(TCHAR) * (Length - i - 1));
			break;
		}
	}

	memset(Directory, 0, MAX_PATH);
	strcpy_s(Directory, Path);

	// Editor의 GameObject폴더에 있는 파일을 읽어온다.
	strcat_s(Directory, "Engine/Include/Component/");

	for (const auto& file : std::filesystem::directory_iterator(Directory))
	{
		char	Name[64] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

		if (strcmp(Ext, ".cpp") == 0)
			continue;

		else if (strcmp(Name, "Transform") == 0 ||
			strcmp(Name, "Transform2D") == 0 ||
			strcmp(Name, "Component") == 0 ||
			strcmp(Name, "PrimitiveComponent") == 0 ||
			strcmp(Name, "ObjectComponent") == 0 ||
			strcmp(Name, "Tile") == 0)
			continue;

		m_ComponentList->AddItem(Name);
	}
}
