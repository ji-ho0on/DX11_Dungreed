#include "ImageWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorImage.h"
#include "PathManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Editor/EditorGUIManager.h"
#include "Component/SpriteComponent.h"

// Window
#include "ComponentWindow.h"

CImageWindow::CImageWindow()
{
}

CImageWindow::~CImageWindow()
{
}

bool CImageWindow::Init()
{
	CEditorLabel* Label = CreateWidget<CEditorLabel>("Image", 150.f, 30.f);
	Label->SetColor(255, 0, 0, 255);
	Label->SetAlign(0.5f, 0.5f);

	CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(170.f);

	CEditorButton* Button = CreateWidget<CEditorButton>("이미지 세팅", 150.f, 30.f);
	Button->SetColor(29, 47, 73, 255);
	Button->SetClickCallback<CImageWindow>(this, &CImageWindow::SetImage);

	m_ImageList = CreateWidget<CEditorListBox>("ImageListBox");
	m_ImageList->SetHideName(m_ImageList->GetName());
	m_ImageList->SetSize(150.f, 300.f);
	m_ImageList->SetPageItemCount(6);

	m_ImageList->SetSelectCallback<CImageWindow>(this, &CImageWindow::ImageClickCallback);

	Line = CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(170.f);

	m_ImageSelectName = CreateWidget<CEditorInput>("ImageName");
	m_ImageSelectName->SetHideName(m_ImageSelectName->GetName());
	m_ImageSelectName->SetSize(150.f, 30.f);
	m_ImageSelectName->ReadOnly(true);

	m_SelectImage = CreateWidget<CEditorImage>("Image", 100.f, 100.f);

	LoadImageName();

    return true;
}

void CImageWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);
}

void CImageWindow::LoadImageName()
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(TEXTURE_PATH);

	char	Path[MAX_PATH] = {};

	strcpy_s(Path, Info->PathMultibyte);

	char	Directory[MAX_PATH] = {};

	strcpy_s(Directory, Path);

	for (const auto& file : std::filesystem::directory_iterator(Directory))
	{
		char	Name[64] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

		m_ImageList->AddItem(Name);
	}
}

void CImageWindow::SetImage()
{
	if (m_SelectImageItem == "")
		return;

	CComponentWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CComponentWindow>("ComponentWindow");

	if (!Window)
		return;

	CComponent* Component = Window->GetSelectComponent();

	if (Component->GetComponentTypeName() != "SpriteComponent")
		return;

	// 만약 png가 아니라면?
	std::string FileName = m_SelectImageItem + ".png";

	TCHAR	wText[256] = {};

	int Length = (int)MultiByteToWideChar(CP_ACP, 0, FileName.c_str(), -1, nullptr, 0);

	MultiByteToWideChar(CP_ACP, 0, FileName.c_str(), -1, wText, Length);

	((CSpriteComponent*)Component)->GetMaterial(0)->SetTexture(0, 0, (int)EShaderBufferType::Pixel, m_SelectImageItem, wText);
}

void CImageWindow::ImageClickCallback(int Index, const std::string& Item)
{
	m_SelectImageItem = Item;

	m_ImageSelectName->SetText(Item.c_str());

	// 만약 png가 아니라면?
	std::string FileName = Item + ".png";

	TCHAR	wText[256] = {};

	int Length = (int)MultiByteToWideChar(CP_ACP, 0, FileName.c_str(), -1, nullptr, 0);

	MultiByteToWideChar(CP_ACP, 0, FileName.c_str(), -1, wText, Length);

	m_SelectImage->SetTexture(Item, wText);
}
