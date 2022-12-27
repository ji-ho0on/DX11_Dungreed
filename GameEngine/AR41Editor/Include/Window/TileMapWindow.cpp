#include "TileMapWindow.h"
#include "DetailWindow/TileMapComponentWidgetList.h"
#include "DetailWindow.h"
#include "Editor/EditorGUIManager.h"
#include "Resource/ResourceManager.h"
#include "Resource/Texture/Texture.h"

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
#include "Editor/EditorTileImageButton.h"

CTileMapWindow::CTileMapWindow()
{
}

CTileMapWindow::~CTileMapWindow()
{
}

void CTileMapWindow::SetTileTexture(int CountX, int CountY, const Vector2& Size, CTexture* Texture)
{
	m_TileTexture = Texture;

	if (!m_TileTexture)
		return;

	m_CountX = CountX;
	m_CountY = CountY;

	m_Size = Size;

	DeleteAllWidget();

	for (int i = 0; i < m_CountY; ++i)
	{
		for (int j = 0; j < m_CountX; ++j)
		{
			int Index = i * m_CountY + j;

			if (Index >= 200)
				break;

			char Number[64] = {};
			_itoa_s(Index, Number, 10);


			CEditorTileImageButton* TileImage = CreateWidget<CEditorTileImageButton>(Number, 50.f, 50.f);
			TileImage->SetClickCallback<CTileMapWindow>(this, &CTileMapWindow::ImageButton);
			TileImage->SetImageIndexX(j);
			TileImage->SetImageIndexY(i);
			TileImage->SetTexture(m_TileTexture);

			if (m_TileTexture->GetImageType() == EImageType::Atlas)
			{
				TileImage->SetImageStart(m_Size.x * j, m_Size.y * i);
				TileImage->SetImageEnd(m_Size.x * (j + 1), m_Size.y * (i + 1));
			}

			else
			{
				TileImage->SetIndex(Index);
			}

			if (j + 1 == m_CountX)
				break;

			CreateWidget<CEditorSameLine>("Line");
		}
	}
}

void CTileMapWindow::SetTileTexture(int CountX, int CountY, const Vector2& Size, const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	m_TileTexture = CResourceManager::GetInst()->FindTexture(Name);

	if (!m_TileTexture)
		m_TileTexture->LoadTexture(Name, FileName, PathName);

	if (!m_TileTexture)
		return;

	m_CountX = CountX;
	m_CountY = CountY;

	m_Size = Size;

	DeleteAllWidget();

	for (int i = 0; i < m_CountY; ++i)
	{
		for (int j = 0; j < m_CountX; ++j)
		{
			int Index = i * m_CountY + j;

			if (Index >= 200)
				break;

			char Number[64] = {};
			_itoa_s(Index, Number, 10);


			CEditorTileImageButton* TileImage = CreateWidget<CEditorTileImageButton>(Number, 50.f, 50.f);
			TileImage->SetClickCallback<CTileMapWindow>(this, &CTileMapWindow::ImageButton);
			TileImage->SetImageIndexX(j);
			TileImage->SetImageIndexY(i);
			TileImage->SetTexture(m_TileTexture);
			TileImage->SetImageStart(m_Size.x * j, m_Size.y * i);
			TileImage->SetImageEnd(m_Size.x * (j + 1), m_Size.y * (i + 1));

			if (j + 1 == m_CountX)
				break;

			CreateWidget<CEditorSameLine>("Line");
		}
	}
}

void CTileMapWindow::SetTileTextureFullPath(int CountX, int CountY, const Vector2& Size, const std::string& Name, const TCHAR* FullPath)
{
	m_TileTexture = CResourceManager::GetInst()->FindTexture(Name);

	if (!m_TileTexture)
		m_TileTexture->LoadTexture(Name, FullPath);

	if (!m_TileTexture)
		return;

	m_CountX = CountX;
	m_CountY = CountY;

	m_Size = Size;

	DeleteAllWidget();

	for (int i = 0; i < m_CountY; ++i)
	{
		for (int j = 0; j < m_CountX; ++j)
		{
			int Index = i * m_CountY + j;

			if (Index >= 200)
				break;

			char Number[64] = {};
			_itoa_s(Index, Number, 10);


			CEditorTileImageButton* TileImage = CreateWidget<CEditorTileImageButton>(Number, 50.f, 50.f);
			TileImage->SetClickCallback<CTileMapWindow>(this, &CTileMapWindow::ImageButton);
			TileImage->SetImageIndexX(j);
			TileImage->SetImageIndexY(i);
			TileImage->SetTexture(m_TileTexture);
			TileImage->SetImageStart(m_Size.x * i, m_Size.y * j);
			TileImage->SetImageEnd(m_Size.x * (i + 1), m_Size.y * (j + 1));

			if (j + 1 == m_CountX)
				break;

			CreateWidget<CEditorSameLine>("Line");
		}
	}
}

void CTileMapWindow::SetTileTexture(int CountX, int CountY, const std::string& Name, std::vector<const TCHAR*> vecFileName, const std::string& PathName)
{
	m_TileTexture = CResourceManager::GetInst()->FindTexture(Name);

	if (!m_TileTexture)
		m_TileTexture->LoadTexture(Name, vecFileName, PathName);

	if (!m_TileTexture)
		return;

	m_CountX = CountX;
	m_CountY = CountY;

	DeleteAllWidget();

	for (int i = 0; i < m_CountY; ++i)
	{
		for (int j = 0; j < m_CountX; ++j)
		{
			int Index = i * m_CountY + j;

			if (Index >= 200 || Index >= m_TileTexture->GetImageCount())
				break;

			char Number[64] = {};
			_itoa_s(Index, Number, 10);


			CEditorTileImageButton* TileImage = CreateWidget<CEditorTileImageButton>(Number, 50.f, 50.f);
			TileImage->SetClickCallback<CTileMapWindow>(this, &CTileMapWindow::ImageButton);
			TileImage->SetImageIndexX(j);
			TileImage->SetImageIndexY(i);
			TileImage->SetIndex(Index);
			TileImage->SetTexture(m_TileTexture);
			//TileImage->SetImageStart(m_Size.x * i, m_Size.y * j);
			//TileImage->SetImageEnd(m_Size.x * (i + 1), m_Size.y * (j + 1));

			if (j + 1 == m_CountX)
				break;

			CreateWidget<CEditorSameLine>("Line");
		}
	}
}

void CTileMapWindow::SetTileTextureFullPath(int CountX, int CountY, const std::string& Name, std::vector<const TCHAR*> vecFullPath)
{
	m_TileTexture = CResourceManager::GetInst()->FindTexture(Name);

	if (!m_TileTexture)
		m_TileTexture->LoadTexture(Name, vecFullPath);

	if (!m_TileTexture)
		return;

	m_CountX = CountX;
	m_CountY = CountY;

	DeleteAllWidget();

	for (int i = 0; i < m_CountY; ++i)
	{
		for (int j = 0; j < m_CountX; ++j)
		{
			int Index = i * m_CountY + j;

			if (Index >= 200)
				break;

			char Number[64] = {};
			_itoa_s(Index, Number, 10);


			CEditorTileImageButton* TileImage = CreateWidget<CEditorTileImageButton>(Number, 50.f, 50.f);
			TileImage->SetClickCallback<CTileMapWindow>(this, &CTileMapWindow::ImageButton);
			TileImage->SetImageIndexX(j);
			TileImage->SetImageIndexY(i);
			TileImage->SetIndex(Index);
			TileImage->SetTexture(m_TileTexture);
			//TileImage->SetImageStart(m_Size.x * i, m_Size.y * j);
			//TileImage->SetImageEnd(m_Size.x * (i + 1), m_Size.y * (j + 1));

			if (j + 1 == m_CountX)
				break;

			CreateWidget<CEditorSameLine>("Line");
		}
	}
}

bool CTileMapWindow::Init()
{
	//int NewLine = 0;

	//for (int i = 0; i < 10; ++i)
	//{
	//	for (int j = 0; j < 20; ++j)
	//	{
	//		char Number[64] = {};
	//		_itoa_s(i * 20 + j, Number, 10);

	//		CEditorTileImageButton* TileImage = CreateWidget<CEditorTileImageButton>(Number, 30.f, 30.f);
	//		TileImage->SetClickCallback<CTileMapWindow>(this, &CTileMapWindow::ImageButton);
	//		TileImage->SetIndex(i * 20 + j);

	//		++NewLine;

	//		if (j == 19)
	//			break;

	//		CreateWidget<CEditorSameLine>("Line");
	//	}
	//}

	//CEditorTileImageButton* ImageButton = (CEditorTileImageButton*)FindWidget("12");
	//ImageButton->SetTexture("TestImage", TEXT("Example/MainImage.png"));

	return true;
}

void CTileMapWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);
}

void CTileMapWindow::ImageButton(int IndexX, int IndexY)
{
	int Index = IndexY * m_CountX + IndexX;

	if (m_TileTexture->GetImageType() == EImageType::Array)
	{
		if (Index >= m_TileTexture->GetImageCount())
			return;
	}

	CDetailWindow* DetailWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CDetailWindow>("DetailWindow");

	CTileMapComponentWidgetList* TileMapComponentWidgetList = (CTileMapComponentWidgetList*)DetailWindow->GetComponentWidgetList(ESceneComponentType::TileMap);
	TileMapComponentWidgetList->SetTileImageIndex(IndexX, IndexY);
}
