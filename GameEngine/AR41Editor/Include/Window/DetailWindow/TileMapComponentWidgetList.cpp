#include "TileMapComponentWidgetList.h"
#include "Component/TileMapComponent.h"
#include "../DetailWindow.h"
#include "../../Editor.h"
#include "Input.h"
#include "Component/CameraComponent.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/CameraManager.h"
#include "Editor/EditorGUIManager.h"
#include "../TileMapWindow.h"
#include "PathManager.h"



// Widget
#include "Editor/EditorTree.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorNewLine.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorText.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorTileImageButton.h"
#include "Editor/EditorCheckBox.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorGUIManager.h"

CTileMapComponentWidgetList::CTileMapComponentWidgetList()
{
}

CTileMapComponentWidgetList::~CTileMapComponentWidgetList()
{
}

void CTileMapComponentWidgetList::SetTileImageIndex(int IndexX, int IndexY)
{
	EImageType Type = m_SelectTileImage->GetTexture()->GetImageType();

	if (Type == EImageType::Atlas)
	{
		m_SelectTileImage->SetImageStart(IndexX * m_TileImageSizeX->GetFloat(), IndexY * m_TileImageSizeY->GetFloat());
		m_SelectTileImage->SetImageEnd((IndexX + 1)* m_TileImageSizeX->GetFloat(), (IndexY + 1) * m_TileImageSizeY->GetFloat());
		m_SelectTileImage->SetImageIndexX(IndexX);
		m_SelectTileImage->SetImageIndexY(IndexY);
	}

	else
	{
		m_SelectTileImage->SetIndex(IndexY * m_TileImageCountY->GetInt() + IndexX);
	}
}

bool CTileMapComponentWidgetList::Init()
{
	CEditorTree<void*>* TileMapComponentTree = CreateWidget<CEditorTree<void*>>("TileMapComponentTree");
	TileMapComponentTree->AddItem(nullptr, "TileMapComponent");
	TileMapComponentTree->FindItem("TileMapComponent")->AddFlag(ImGuiTreeNodeFlags_DefaultOpen);

	// Tile Create
	TileMapComponentTree->AddItem(nullptr, "Tile Create", "TileMapComponent");


	CEditorGroup* CreateTileGroup = TileMapComponentTree->CreateWidget<CEditorGroup>("Tile Create", "CreateTileGroup");

	m_TileShapeCombo = CreateTileGroup->CreateWidget<CEditorComboBox>("TileShapeCombo", 120.f);
	m_TileShapeCombo->SetHideName(m_TileShapeCombo->GetName());
	m_TileShapeCombo->SetPrevViewName("TileShape");
	m_TileShapeCombo->AddItem("Rect");
	m_TileShapeCombo->AddItem("Isometric");
	m_TileShapeCombo->Sort(false);
	m_TileShapeCombo->SetSelectIndex(0);
	m_TileShapeCombo->SetPrevViewName("Rect");

	CEditorText* TileCountText = CreateTileGroup->CreateWidget<CEditorText>("TileCountText");
	TileCountText->SetText("TileCount");

	CreateTileGroup->CreateWidget<CEditorSameLine>("Line")->SetOffsetX(80.f);

	m_TileCountX = CreateTileGroup->CreateWidget<CEditorInput>("TileCountX", 100.f, 30.f);
	m_TileCountX->SetHideName(m_TileCountX->GetName());
	m_TileCountX->SetInputType(EImGuiInputType::Int);

	CreateTileGroup->CreateWidget<CEditorSameLine>("Line");

	m_TileCountY = CreateTileGroup->CreateWidget<CEditorInput>("TileCountY", 100.f, 30.f);
	m_TileCountY->SetHideName(m_TileCountY->GetName());
	m_TileCountY->SetInputType(EImGuiInputType::Int);

	CEditorText* TileSizeText = CreateTileGroup->CreateWidget<CEditorText>("TileSizeText");
	TileSizeText->SetText("TileSize");

	CreateTileGroup->CreateWidget<CEditorSameLine>("Line")->SetOffsetX(80.f);

	m_TileSizeX = CreateTileGroup->CreateWidget<CEditorInput>("TileSizeX", 100.f, 30.f);
	m_TileSizeX->SetHideName(m_TileSizeX->GetName());
	m_TileSizeX->SetInputType(EImGuiInputType::Float);

	CreateTileGroup->CreateWidget<CEditorSameLine>("Line");

	m_TileSizeY = CreateTileGroup->CreateWidget<CEditorInput>("TileSizeY", 100.f, 30.f);
	m_TileSizeY->SetHideName(m_TileSizeY->GetName());
	m_TileSizeY->SetInputType(EImGuiInputType::Float);

	TileMapComponentTree->CreateWidget<CEditorSameLine>("Tile Create", "Line");

	CEditorButton* TileCreateButton = TileMapComponentTree->CreateWidget<CEditorButton>("Tile Create", "Tile Create", 100.f, 85.f);
	TileCreateButton->SetClickCallback<CTileMapComponentWidgetList>(this, &CTileMapComponentWidgetList::CreateTileButton);



	// Tile Edit
	TileMapComponentTree->AddItem(nullptr, "Tile Edit", "TileMapComponent");

	CEditorGroup* EditTileGroup = TileMapComponentTree->CreateWidget<CEditorGroup>("Tile Edit", "EditTileGroup");

	m_TileEditModeCombo = EditTileGroup->CreateWidget<CEditorComboBox>("TileEditModeCombo", 120.f);
	m_TileEditModeCombo->SetHideName(m_TileEditModeCombo->GetName());
	m_TileEditModeCombo->SetPrevViewName("EditMode");
	m_TileEditModeCombo->AddItem("Image");
	m_TileEditModeCombo->AddItem("Option");
	m_TileEditModeCombo->Sort(false);
	m_TileEditModeCombo->SetSelectIndex(0);
	m_TileEditModeCombo->SetPrevViewName("Image");


	TileMapComponentTree->CreateWidget<CEditorNewLine>("Tile Edit", "NewLine");


	CEditorGroup* EditOptionGroup = TileMapComponentTree->CreateWidget<CEditorGroup>("Tile Edit", "EditOptionGroup");

	CEditorText* TileOptionText = EditOptionGroup->CreateWidget<CEditorText>("TileOptionText");
	TileOptionText->SetText("TileOption");

	m_TileOptionCombo = EditOptionGroup->CreateWidget<CEditorComboBox>("TileOptionCombo", 120.f);
	m_TileOptionCombo->SetHideName(m_TileOptionCombo->GetName());
	m_TileOptionCombo->SetPrevViewName("TileOption");
	m_TileOptionCombo->AddItem("None");
	m_TileOptionCombo->AddItem("Wall");
	m_TileOptionCombo->AddItem("SideWall");
	m_TileOptionCombo->AddItem("OneWay");
	m_TileOptionCombo->Sort(false);
	m_TileOptionCombo->SetSelectIndex(0);
	m_TileOptionCombo->SetPrevViewName("None");

	TileMapComponentTree->CreateWidget<CEditorSameLine>("Tile Edit", "Line")->SetSpacing(30.f);


	CEditorGroup* EditImageGroup = TileMapComponentTree->CreateWidget<CEditorGroup>("Tile Edit", "EditImageGroup");

	CEditorText* SelectTileImageText = EditImageGroup->CreateWidget<CEditorText>("SelectTileImageText");
	SelectTileImageText->SetText("SelectTileImage");

	EditImageGroup->CreateWidget<CEditorSameLine>("Line")->SetOffsetX(150.f);

	CEditorText* ChangeTileImageText = EditImageGroup->CreateWidget<CEditorText>("ChangeTileImageText");
	ChangeTileImageText->SetText("ChangeTileImage");


	m_SelectTileImage = EditImageGroup->CreateWidget<CEditorTileImageButton>("SelectTileImage", 120.f, 120.f);

	EditImageGroup->CreateWidget<CEditorSameLine>("Line")->SetOffsetX(150.f);

	CEditorButton* SetTileImageButton = EditImageGroup->CreateWidget<CEditorButton>("Open", 120.f, 50.f);
	SetTileImageButton->SetClickCallback<CTileMapComponentWidgetList>(this, &CTileMapComponentWidgetList::SetTileImageButton);



	// Tile Texture
	TileMapComponentTree->AddItem(nullptr, "Tile Texture", "TileMapComponent");

	CEditorGroup* TileImageTypeGroup = TileMapComponentTree->CreateWidget<CEditorGroup>("Tile Texture", "TileImageTypeGroup");

	CEditorText* TileImageCountText = TileImageTypeGroup->CreateWidget<CEditorText>("TileImageCountText");
	TileImageCountText->SetText("TileImageCount");

	TileImageTypeGroup->CreateWidget<CEditorSameLine>("Line")->SetOffsetX(130.f);

	m_TileImageCountX = TileImageTypeGroup->CreateWidget<CEditorInput>("TileImageCountX", 100.f, 30.f);
	m_TileImageCountX->SetHideName(m_TileImageCountX->GetName());
	m_TileImageCountX->SetInputType(EImGuiInputType::Int);

	TileImageTypeGroup->CreateWidget<CEditorSameLine>("Line");

	m_TileImageCountY = TileImageTypeGroup->CreateWidget<CEditorInput>("TileImageCountY", 100.f, 30.f);
	m_TileImageCountY->SetHideName(m_TileImageCountY->GetName());
	m_TileImageCountY->SetInputType(EImGuiInputType::Int);

	CEditorText* TileImageSizeText = TileImageTypeGroup->CreateWidget<CEditorText>("TileImageSizeText");
	TileImageSizeText->SetText("TileImageSize");

	TileImageTypeGroup->CreateWidget<CEditorSameLine>("Line")->SetOffsetX(130.f);

	m_TileImageSizeX = TileImageTypeGroup->CreateWidget<CEditorInput>("TileImageSizeX", 100.f, 30.f);
	m_TileImageSizeX->SetHideName(m_TileImageSizeX->GetName());
	m_TileImageSizeX->SetInputType(EImGuiInputType::Float);

	TileImageTypeGroup->CreateWidget<CEditorSameLine>("Line");

	m_TileImageSizeY = TileImageTypeGroup->CreateWidget<CEditorInput>("TileImageSizeY", 100.f, 30.f);
	m_TileImageSizeY->SetHideName(m_TileImageSizeY->GetName());
	m_TileImageSizeY->SetInputType(EImGuiInputType::Float);

	CEditorGroup* EditTileTextureGroup = TileMapComponentTree->CreateWidget<CEditorGroup>("Tile Texture", "EditTileTextureGroup");

	CEditorText* TileTextureText = EditTileTextureGroup->CreateWidget<CEditorText>("TileTextureText");
	TileTextureText->SetText("TileTexture");

	m_TileTexture = EditTileTextureGroup->CreateWidget<CEditorImage>("TileTexture", 120.f, 120.f);

	EditTileTextureGroup->CreateWidget<CEditorSameLine>("Line");

	CEditorButton* TileTextureLoadButton = EditTileTextureGroup->CreateWidget<CEditorButton>("TileTextureLoad", 150.f, 30.f);
	TileTextureLoadButton->SetClickCallback<CTileMapComponentWidgetList>(this, &CTileMapComponentWidgetList::LoadTileTextureButton);

	return true;
}

void CTileMapComponentWidgetList::Render()
{
	CComponentWidgetList::Render();

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

		Camera->AddWorldPositionY(500.f * g_DeltaTime);
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

		Camera->AddWorldPositionY(-500.f * g_DeltaTime);
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

		Camera->AddWorldPositionX(500.f * g_DeltaTime);
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

		Camera->AddWorldPositionX(-500.f * g_DeltaTime);
	}

	// 마우스가 위치한 Tile을 MouseOnTile로 지정한다
	Vector2 Pos = CInput::GetInst()->GetMouseWorldPos();
	int	Index = m_TileMapComponent->GetTileIndex(Pos);
	m_TileMapComponent->SetEditorMouseOnTile(Index);

	// 마우스 클릭 시 EditMode가 어떤지에 따라 Tile을 편집한다.
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		switch ((ETileEditMode)m_TileEditModeCombo->GetSelectIndex())
		{
		case ETileEditMode::Image:
			if (m_SelectTileImage->GetTexture()->GetImageType() == EImageType::Atlas)
			{
				m_TileMapComponent->ChangeTileFrame(m_SelectTileImage->GetImageIndexY() * m_TileImageCountX->GetInt() + m_SelectTileImage->GetImageIndexX());
			}

			else
			{
				m_TileMapComponent->ChangeTileFrame(m_SelectTileImage->GetIndex());
			}
			break;
		case ETileEditMode::Option:
			m_TileMapComponent->ChangeTileOption((ETileOption)m_TileOptionCombo->GetSelectIndex());
			break;
		}
	}
}

void CTileMapComponentWidgetList::SetComponentContents(CSceneComponent* Component)
{
	m_TileMapComponent = (CTileMapComponent*)Component;

	/*
	class CEditorComboBox*				m_TileShapeCombo;
	class CEditorInput*					m_TileCountX;
	class CEditorInput*					m_TileCountY;
	class CEditorInput*					m_TileSizeX;
	class CEditorInput*					m_TileSizeY;


	class CEditorComboBox*				m_TileEditModeCombo;
	class CEditorComboBox*				m_TileOptionCombo;

	class CEditorTileImageButton*		m_SelectTileImage;

	class CEditorInput*					m_TileImageCountX;
	class CEditorInput*					m_TileImageCountY;
	class CEditorInput*					m_TileImageSizeX;
	class CEditorInput*					m_TileImageSizeY;
	class CEditorImage*					m_TileTexture;
	*/
	CTexture* TileTexture = m_TileMapComponent->GetTileTexture();

	if(TileTexture)
		m_SelectTileImage->SetTexture(TileTexture);

	m_TileImageCountX->SetInt(10);
	m_TileImageCountY->SetInt(10);
	m_TileImageSizeX->SetFloat(64.f);
	m_TileImageSizeY->SetFloat(64.f);

	CTileMapWindow* TileMapWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CTileMapWindow>("TileMapWindow");
	TileMapWindow->SetTileTexture(m_TileImageCountX->GetInt(), m_TileImageCountY->GetInt(), Vector2(m_TileImageSizeX->GetFloat(), m_TileImageSizeY->GetFloat()), TileTexture);

}

void CTileMapComponentWidgetList::CreateTileButton()
{
	int Index = m_TileShapeCombo->GetSelectIndex();

	if (Index < 0 || Index > (int)ETileShape::Isometric)
		return;

	int TileCountX = m_TileCountX->GetInt();
	int TileCountY = m_TileCountY->GetInt();

	if (TileCountX < 0 || TileCountY < 0)
		return;

	Vector2 TileSize = Vector2(m_TileSizeX->GetFloat(), m_TileSizeY->GetFloat());

	if (TileSize.x <= 0.f || TileSize.y <= 0.f)
		return;

	m_TileMapComponent->CreateTile((ETileShape)Index, TileCountX, TileCountY, TileSize);

	m_SelectTileImage->SetSize(TileSize);
}

void CTileMapComponentWidgetList::SetTileImageButton()
{
	CEditorGUIManager::GetInst()->FindEditorWindow<CTileMapWindow>("TileMapWindow")->Open();
}

void CTileMapComponentWidgetList::LoadTileTextureButton()
{
	OPENFILENAME	ofn = {};

	TCHAR	FullPath[2048] = {};

	TCHAR	Filter[] = TEXT("모든 파일\0*.*\0PNG\0*.png\0JPG\0*.jpg\0BMP\0*.bmp");

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	ofn.lpstrFilter = Filter;
	ofn.lpstrFile = FullPath;
	ofn.nMaxFile = 2048;
	ofn.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->Path;
	ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;

	if (GetOpenFileName(&ofn) != 0)
	{
		// Image를 한장 선택했는지 or 여러장 선택했는지 나눈다.
		TCHAR Path[2048] = {};

		lstrcpy(Path, FullPath);

		size_t Size = lstrlen(FullPath);

		// 한 장 선택했을 때 (Atlas)
		if (FullPath[Size + 1] == 0)
		{
			TCHAR	wTexName[256] = {};

			_wsplitpath_s(FullPath, 0, 0, 0, 0, wTexName, 256, 0, 0);

			char	TexName[256] = {};

			int Length = (int)WideCharToMultiByte(CP_ACP, 0, wTexName, -1, nullptr, 0, nullptr, nullptr);

			WideCharToMultiByte(CP_ACP, 0, wTexName, -1, TexName, Length, nullptr, nullptr);

			m_TileTexture->SetTextureFullPath(TexName, FullPath);

			m_SelectTileImage->SetTextureFullPath(TexName, FullPath);

			m_TileMapComponent->SetTileTextureFullPath(m_TileImageCountX->GetInt(), m_TileImageCountY->GetInt(), Vector2(m_TileImageSizeX->GetFloat(), m_TileImageSizeY->GetFloat()), TexName, FullPath);


			CTileMapWindow* TileMapWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CTileMapWindow>("TileMapWindow");
			TileMapWindow->SetTileTexture(m_TileImageCountX->GetInt(), m_TileImageCountY->GetInt(), Vector2(m_TileImageSizeX->GetFloat(), m_TileImageSizeY->GetFloat()), TexName, FullPath);
		}

		// 여러 장 선택했을 때 (Frame)
		else
		{
			lstrcat(Path, L"/");

			std::vector<const TCHAR*> vecFileName;

			for (size_t i = lstrlen(FullPath) + 1; FullPath[i] != 0; i += (lstrlen(FullPath + i) + 1))
			{
				TCHAR* FileName = new TCHAR[256];

				lstrcpy(FileName, Path);

				lstrcat(FileName, FullPath + i);

				vecFileName.push_back(FileName);
			}

			// TexName을 구해야함.
			//보통 TexName_00.png or TexName-00.png 형태로 들어오니까 vecFileName에서 첫번째꺼를
			TCHAR	wTexName[256] = {};

			_wsplitpath_s(vecFileName[0], 0, 0, 0, 0, wTexName, 256, 0, 0);

			char	TexName[256] = {};

			int Length = (int)WideCharToMultiByte(CP_ACP, 0, wTexName, -1, nullptr, 0, nullptr, nullptr);

			WideCharToMultiByte(CP_ACP, 0, wTexName, -1, TexName, Length, nullptr, nullptr);

			// 여기서 뒤에 _ 이나 - 까지를 떼줘야함.
			// 이부분은 추출한 Resource에 따라 변경
			for (int i = Length - 2; i > 0; --i)
			{
				if ((TexName[i] == '-') || (TexName[i] == '_'))
				{
					TexName[i] = 0;
					break;
				}

				TexName[i] = 0;
			}


			m_TileTexture->SetTextureArrayFullPath(TexName, vecFileName);

			m_SelectTileImage->SetTextureFullPath(TexName, vecFileName);

			m_TileMapComponent->SetTileTextureArrayFullPath(TexName, vecFileName);


			CTileMapWindow* TileMapWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CTileMapWindow>("TileMapWindow");
			TileMapWindow->SetTileTexture(m_TileImageCountX->GetInt(), m_TileImageCountY->GetInt(), TexName, vecFileName);

			size_t vecSize = vecFileName.size();

			for (size_t i = 0; i < vecSize; ++i)
			{
				SAFE_DELETE_ARRAY(vecFileName[i]);
			}
		}
	}
}
