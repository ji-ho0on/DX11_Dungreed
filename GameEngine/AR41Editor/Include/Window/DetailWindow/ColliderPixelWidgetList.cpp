#include "ColliderPixelWidgetList.h"
#include "Component/ColliderPixel.h"
#include "../DetailWindow.h"
#include "CollisionManager.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorImage.h"
#include "Engine.h"
#include "PathManager.h"

CColliderPixelWidgetList::CColliderPixelWidgetList()
{
}

CColliderPixelWidgetList::~CColliderPixelWidgetList()
{
}

bool CColliderPixelWidgetList::Init()
{
	CEditorTree<void*>* ColliderPixelTree = CreateWidget<CEditorTree<void*>>("ColliderPixelTree");
	ColliderPixelTree->AddItem(nullptr, "ColliderPixel");
	ColliderPixelTree->FindItem("ColliderPixel")->AddFlag(ImGuiTreeNodeFlags_DefaultOpen);

	// 이미지 세팅
	ColliderPixelTree->AddItem(nullptr, "Image", "ColliderPixel");

	m_ColliderPixelImage = ColliderPixelTree->CreateWidget<CEditorImage>("Image", "ColliderPixelImage");
	m_ColliderPixelImage->SetSize(100.f, 100.f);

	CEditorSameLine* Line = ColliderPixelTree->CreateWidget<CEditorSameLine>("Image", "Line");

	CEditorButton* LoadButton = ColliderPixelTree->CreateWidget<CEditorButton>("Image", "Load");
	LoadButton->SetSize(50.f, 30.f);
	LoadButton->SetClickCallback<CColliderPixelWidgetList>(this, &CColliderPixelWidgetList::PixelImageLoadButtonClick);

	// Pixel 충돌 Type 세팅
	ColliderPixelTree->AddItem(nullptr, "CollisionType", "ColliderPixel");

	CEditorLabel* Label = ColliderPixelTree->CreateWidget<CEditorLabel>("CollisionType", "Color", 50.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	Line = ColliderPixelTree->CreateWidget<CEditorSameLine>("CollisionType", "Line");

	m_ColorCollisionType = ColliderPixelTree->CreateWidget<CEditorComboBox>("CollisionType", "ColorCollisionType", 165.f, 30.f);
	m_ColorCollisionType->SetHideName(m_ColorCollisionType->GetName());
	m_ColorCollisionType->AddItem("None");
	m_ColorCollisionType->AddItem("Color_Ignore");
	m_ColorCollisionType->AddItem("Color_Confirm");

	Line = ColliderPixelTree->CreateWidget<CEditorSameLine>("CollisionType", "Line");

	CEditorButton* ColorSetButton = ColliderPixelTree->CreateWidget<CEditorButton>("CollisionType", "Color Set");
	ColorSetButton->SetSize(100.f, 30.f);
	ColorSetButton->SetClickCallback<CColliderPixelWidgetList>(this, &CColliderPixelWidgetList::PixelColorCollisionTypeSetButtonClick);



	Label = ColliderPixelTree->CreateWidget<CEditorLabel>("CollisionType", "Alpha", 50.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	Line = ColliderPixelTree->CreateWidget<CEditorSameLine>("CollisionType", "Line");

	m_AlphaCollisionType = ColliderPixelTree->CreateWidget<CEditorComboBox>("CollisionType", "AlphaCollisionType", 165.f, 30.f);
	m_AlphaCollisionType->SetHideName(m_AlphaCollisionType->GetName());
	m_AlphaCollisionType->AddItem("None");
	m_AlphaCollisionType->AddItem("Alpha_Ignore");
	m_AlphaCollisionType->AddItem("Alpha_Confirm");

	Line = ColliderPixelTree->CreateWidget<CEditorSameLine>("CollisionType", "Line");

	CEditorButton* AlphaSetButton = ColliderPixelTree->CreateWidget<CEditorButton>("CollisionType", "Alpha Set");
	AlphaSetButton->SetSize(100.f, 30.f);
	AlphaSetButton->SetClickCallback<CColliderPixelWidgetList>(this, &CColliderPixelWidgetList::PixelAlphaCollisionTypeSetButtonClick);


	// Pixel 충돌 TypeColor R, G, B, A 세팅
	ColliderPixelTree->AddItem(nullptr, "TypeColor", "ColliderPixel");


	Label = ColliderPixelTree->CreateWidget<CEditorLabel>("TypeColor", "R", 50.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	Line = ColliderPixelTree->CreateWidget<CEditorSameLine>("TypeColor", "Line");

	Label = ColliderPixelTree->CreateWidget<CEditorLabel>("TypeColor", "G", 50.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	Line = ColliderPixelTree->CreateWidget<CEditorSameLine>("TypeColor", "Line");

	Label = ColliderPixelTree->CreateWidget<CEditorLabel>("TypeColor", "B", 50.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	Line = ColliderPixelTree->CreateWidget<CEditorSameLine>("TypeColor", "Line");

	Label = ColliderPixelTree->CreateWidget<CEditorLabel>("TypeColor", "A", 50.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	Label->SetAlign(0.5f, 0.5f);

	m_TypeColorR = ColliderPixelTree->CreateWidget<CEditorInput>("TypeColor", "TypeColorRInput", 50.f, 30.f);
	m_TypeColorR->SetHideName(m_TypeColorR->GetName());
	m_TypeColorR->SetInputType(EImGuiInputType::Float);

	Line = ColliderPixelTree->CreateWidget<CEditorSameLine>("TypeColor", "Line");

	m_TypeColorG = ColliderPixelTree->CreateWidget<CEditorInput>("TypeColor", "TypeColorGInput", 50.f, 30.f);
	m_TypeColorG->SetHideName(m_TypeColorG->GetName());
	m_TypeColorG->SetInputType(EImGuiInputType::Float);

	Line = ColliderPixelTree->CreateWidget<CEditorSameLine>("TypeColor", "Line");

	m_TypeColorB = ColliderPixelTree->CreateWidget<CEditorInput>("TypeColor", "TypeColorBInput", 50.f, 30.f);
	m_TypeColorB->SetHideName(m_TypeColorB->GetName());
	m_TypeColorB->SetInputType(EImGuiInputType::Float);

	Line = ColliderPixelTree->CreateWidget<CEditorSameLine>("TypeColor", "Line");

	m_TypeColorA = ColliderPixelTree->CreateWidget<CEditorInput>("TypeColor", "TypeColorAInput", 50.f, 30.f);
	m_TypeColorA->SetHideName(m_TypeColorA->GetName());
	m_TypeColorA->SetInputType(EImGuiInputType::Float);

	Line = ColliderPixelTree->CreateWidget<CEditorSameLine>("TypeColor", "Line");

	CEditorButton* SetButton = ColliderPixelTree->CreateWidget<CEditorButton>("TypeColor", "Set");
	SetButton->SetSize(50.f, 30.f);
	SetButton->SetClickCallback<CColliderPixelWidgetList>(this, &CColliderPixelWidgetList::PixelTypeColorSetButtonClick);

    return true;
}

void CColliderPixelWidgetList::SetComponentContents(CSceneComponent* Component)
{
	CColliderPixel* ColliderPixel = (CColliderPixel*)Component;

	// Image
	const PixelInfo Info = ColliderPixel->GetInfo();
	
	m_ColliderPixelImage->SetTexture(Info.Name, Info.FileName, Info.PathName);

	// ColorCollisionType
	EPixelCollision_Type Type = ColliderPixel->GetPixelColorCollisionType();

	switch (Type)
	{
	case EPixelCollision_Type::None:
		m_ColorCollisionType->SetPrevViewName("None");
		break;
	case EPixelCollision_Type::Color_Ignore:
		m_ColorCollisionType->SetPrevViewName("Color_Ignore");
		break;
	case EPixelCollision_Type::Color_Confirm:
		m_ColorCollisionType->SetPrevViewName("Color_Confirm");
		break;
	}

	// AlphaCollisionType
	Type = ColliderPixel->GetPixelAlphaCollisionType();

	switch (Type)
	{
	case EPixelCollision_Type::None:
		m_AlphaCollisionType->SetPrevViewName("None");
		break;
	case EPixelCollision_Type::Alpha_Ignore:
		m_AlphaCollisionType->SetPrevViewName("Alpha_Ignore");
		break;
	case EPixelCollision_Type::Alpha_Confirm:
		m_AlphaCollisionType->SetPrevViewName("Alpha_Confirm");
		break;
	}

	// TypeColor
	unsigned char* TypeColor = nullptr;

	TypeColor = ColliderPixel->GetPixelTypeColor();

	m_TypeColorR->SetFloat((float)TypeColor[0]);
	m_TypeColorG->SetFloat((float)TypeColor[1]);
	m_TypeColorB->SetFloat((float)TypeColor[2]);
	m_TypeColorA->SetFloat((float)TypeColor[3]);
}

void CColliderPixelWidgetList::PixelImageLoadButtonClick()
{
	OPENFILENAME	ofn = {};

	TCHAR	FullPath[MAX_PATH] = {};

	TCHAR	Filter[] = TEXT("모든 파일\0*.*\0PNG\0*.png\0JPG\0*.jpg\0BMP\0*.bmp");

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	ofn.lpstrFilter = Filter;
	ofn.lpstrFile = FullPath;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->Path;

	if (GetOpenFileName(&ofn) != 0)
	{
		TCHAR	wTexName[256] = {};

		_wsplitpath_s(FullPath, 0, 0, 0, 0, wTexName, 256, 0, 0);

		char	TexName[256] = {};

		int Length = (int)WideCharToMultiByte(CP_ACP, 0, wTexName, -1, nullptr, 0, nullptr, nullptr);

		WideCharToMultiByte(CP_ACP, 0, wTexName, -1, TexName, Length, nullptr, nullptr);

		m_ColliderPixelImage->SetTextureFullPath(TexName, FullPath);

		CColliderPixel* Component = (CColliderPixel*)m_DetailWindow->GetSelectComponent();

		// 선택한 ColliderPixel의 SetInfo를 통해 이미지를 교체한다.
		if (Component)
		{
			Component->SetInfoFullPath(TexName, FullPath);
		}
	}
}

void CColliderPixelWidgetList::PixelColorCollisionTypeSetButtonClick()
{
	int SelectIndex = m_ColorCollisionType->GetSelectIndex();

	if (SelectIndex == -1)
		return;

	std::string SelectItem = m_ColorCollisionType->GetSelectItem();

	EPixelCollision_Type Type = EPixelCollision_Type::None;

	if (SelectItem == "None")
		Type = EPixelCollision_Type::None;

	else if (SelectItem == "Color_Ignore")
		Type = EPixelCollision_Type::Color_Ignore;

	else if (SelectItem == "Color_Confirm")
		Type = EPixelCollision_Type::Color_Confirm;

	CColliderPixel* Component = (CColliderPixel*)m_DetailWindow->GetSelectComponent();

	if (Component)
	{
		Component->SetPixelColorCollisionType(Type);
	}
}

void CColliderPixelWidgetList::PixelAlphaCollisionTypeSetButtonClick()
{
	int SelectIndex = m_ColorCollisionType->GetSelectIndex();

	if (SelectIndex == -1)
		return;

	std::string SelectItem = m_ColorCollisionType->GetSelectItem();

	EPixelCollision_Type Type = EPixelCollision_Type::None;

	if (SelectItem == "None")
		Type = EPixelCollision_Type::None;

	else if (SelectItem == "Alpha_Ignore")
		Type = EPixelCollision_Type::Color_Ignore;

	else if (SelectItem == "Alpha_Confirm")
		Type = EPixelCollision_Type::Color_Confirm;

	CColliderPixel* Component = (CColliderPixel*)m_DetailWindow->GetSelectComponent();

	if (Component)
	{
		Component->SetPixelAlphaCollisionType(Type);
	}
}

void CColliderPixelWidgetList::PixelTypeColorSetButtonClick()
{
	unsigned char TypeColorR = (unsigned char)m_TypeColorR->GetFloat();
	unsigned char TypeColorG = (unsigned char)m_TypeColorG->GetFloat();
	unsigned char TypeColorB = (unsigned char)m_TypeColorB->GetFloat();
	unsigned char TypeColorA = (unsigned char)m_TypeColorA->GetFloat();

	CColliderPixel* Component = (CColliderPixel*)m_DetailWindow->GetSelectComponent();

	if (Component)
	{
		Component->SetPixelColor(TypeColorR, TypeColorG, TypeColorB);
		Component->SetPixelAlpha(TypeColorA);
	}
}
