#include "PrimitiveComponentWidgetList.h"
#include "Component/PrimitiveComponent.h"
#include "Resource/Material/Material.h"
#include "../DetailWindow.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorInput.h"
#include "Engine.h"
#include "PathManager.h"

CPrimitiveComponentWidgetList::CPrimitiveComponentWidgetList()
{
}

CPrimitiveComponentWidgetList::~CPrimitiveComponentWidgetList()
{
}

bool CPrimitiveComponentWidgetList::Init()
{
	CEditorTree<void*>* PrimitiveComponentTree = CreateWidget<CEditorTree<void*>>("PrimitiveComponentTree");
	PrimitiveComponentTree->AddItem(nullptr, "PrimitiveComponent");
	//PrimitiveComponentTree->FindItem("PrimitiveComponent")->AddFlag(ImGuiTreeNodeFlags_DefaultOpen);

	// 이미지 세팅
	PrimitiveComponentTree->AddItem(nullptr, "Image", "PrimitiveComponent");

	m_PrimitiveImage = PrimitiveComponentTree->CreateWidget<CEditorImage>("Image", "PrimitiveImage");
	m_PrimitiveImage->SetSize(100.f, 100.f);

	PrimitiveComponentTree->CreateWidget<CEditorSameLine>("Image", "Line");

	CEditorButton* LoadButton = PrimitiveComponentTree->CreateWidget<CEditorButton>("Image", "Load");
	LoadButton->SetSize(50.f, 30.f);
	LoadButton->SetClickCallback<CPrimitiveComponentWidgetList>(this, &CPrimitiveComponentWidgetList::PrimitiveImageLoadButtonClick);


	// BaseColor 세팅
	PrimitiveComponentTree->AddItem(nullptr, "BaseColor", "PrimitiveComponent");

	m_BaseColorR = PrimitiveComponentTree->CreateWidget<CEditorInput>("BaseColor", "BaseColorR", 40.f, 30.f);
	m_BaseColorR->SetHideName(m_BaseColorR->GetName());
	m_BaseColorR->SetInputType(EImGuiInputType::Float);

	PrimitiveComponentTree->CreateWidget<CEditorSameLine>("BaseColor", "Line");

	m_BaseColorG = PrimitiveComponentTree->CreateWidget<CEditorInput>("BaseColor", "BaseColorG", 40.f, 30.f);
	m_BaseColorG->SetHideName(m_BaseColorG->GetName());
	m_BaseColorG->SetInputType(EImGuiInputType::Float);

	PrimitiveComponentTree->CreateWidget<CEditorSameLine>("BaseColor", "Line");

	m_BaseColorB = PrimitiveComponentTree->CreateWidget<CEditorInput>("BaseColor", "BaseColorB", 40.f, 30.f);
	m_BaseColorB->SetHideName(m_BaseColorB->GetName());
	m_BaseColorB->SetInputType(EImGuiInputType::Float);

	PrimitiveComponentTree->CreateWidget<CEditorSameLine>("BaseColor", "Line");


	m_BaseColorA = PrimitiveComponentTree->CreateWidget<CEditorInput>("BaseColor", "BaseColorA", 40.f, 30.f);
	m_BaseColorA->SetHideName(m_BaseColorA->GetName());
	m_BaseColorA->SetInputType(EImGuiInputType::Float);

	PrimitiveComponentTree->CreateWidget<CEditorSameLine>("BaseColor", "Line");

	CEditorButton* SetButton = PrimitiveComponentTree->CreateWidget<CEditorButton>("BaseColor", "Set", 30.f, 30.f);
	SetButton->SetClickCallback<CPrimitiveComponentWidgetList>(this, &CPrimitiveComponentWidgetList::PrimitiveBaseColorSetButtonClick);


	// AmbientColor 세팅
	PrimitiveComponentTree->AddItem(nullptr, "AmbientColor", "PrimitiveComponent");

	m_AmbientColorR = PrimitiveComponentTree->CreateWidget<CEditorInput>("AmbientColor", "AmbientColorR", 40.f, 30.f);
	m_AmbientColorR->SetHideName(m_AmbientColorR->GetName());
	m_AmbientColorR->SetInputType(EImGuiInputType::Float);

	PrimitiveComponentTree->CreateWidget<CEditorSameLine>("AmbientColor", "Line");

	m_AmbientColorG = PrimitiveComponentTree->CreateWidget<CEditorInput>("AmbientColor", "AmbientColorG", 40.f, 30.f);
	m_AmbientColorG->SetHideName(m_AmbientColorG->GetName());
	m_AmbientColorG->SetInputType(EImGuiInputType::Float);

	PrimitiveComponentTree->CreateWidget<CEditorSameLine>("AmbientColor", "Line");

	m_AmbientColorB = PrimitiveComponentTree->CreateWidget<CEditorInput>("AmbientColor", "AmbientColorB", 40.f, 30.f);
	m_AmbientColorB->SetHideName(m_AmbientColorB->GetName());
	m_AmbientColorB->SetInputType(EImGuiInputType::Float);

	PrimitiveComponentTree->CreateWidget<CEditorSameLine>("AmbientColor", "Line");


	m_AmbientColorA = PrimitiveComponentTree->CreateWidget<CEditorInput>("AmbientColor", "AmbientColorA", 40.f, 30.f);
	m_AmbientColorA->SetHideName(m_AmbientColorA->GetName());
	m_AmbientColorA->SetInputType(EImGuiInputType::Float);

	PrimitiveComponentTree->CreateWidget<CEditorSameLine>("AmbientColor", "Line");

	SetButton = PrimitiveComponentTree->CreateWidget<CEditorButton>("AmbientColor", "Set", 30.f, 30.f);
	SetButton->SetClickCallback<CPrimitiveComponentWidgetList>(this, &CPrimitiveComponentWidgetList::PrimitiveAmbientColorSetButtonClick);


	// SpecularColor 세팅
	PrimitiveComponentTree->AddItem(nullptr, "SpecularColor", "PrimitiveComponent");

	m_SpecularColorR = PrimitiveComponentTree->CreateWidget<CEditorInput>("SpecularColor", "SpecularColorR", 40.f, 30.f);
	m_SpecularColorR->SetHideName(m_SpecularColorR->GetName());
	m_SpecularColorR->SetInputType(EImGuiInputType::Float);

	PrimitiveComponentTree->CreateWidget<CEditorSameLine>("SpecularColor", "Line");

	m_SpecularColorG = PrimitiveComponentTree->CreateWidget<CEditorInput>("SpecularColor", "SpecularColorG", 40.f, 30.f);
	m_SpecularColorG->SetHideName(m_SpecularColorG->GetName());
	m_SpecularColorG->SetInputType(EImGuiInputType::Float);

	PrimitiveComponentTree->CreateWidget<CEditorSameLine>("SpecularColor", "Line");

	m_SpecularColorB = PrimitiveComponentTree->CreateWidget<CEditorInput>("SpecularColor", "SpecularColorB", 40.f, 30.f);
	m_SpecularColorB->SetHideName(m_SpecularColorB->GetName());
	m_SpecularColorB->SetInputType(EImGuiInputType::Float);

	PrimitiveComponentTree->CreateWidget<CEditorSameLine>("SpecularColor", "Line");


	m_SpecularColorA = PrimitiveComponentTree->CreateWidget<CEditorInput>("SpecularColor", "SpecularColorA", 40.f, 30.f);
	m_SpecularColorA->SetHideName(m_SpecularColorA->GetName());
	m_SpecularColorA->SetInputType(EImGuiInputType::Float);

	PrimitiveComponentTree->CreateWidget<CEditorSameLine>("SpecularColor", "Line");

	SetButton = PrimitiveComponentTree->CreateWidget<CEditorButton>("SpecularColor", "Set", 30.f, 30.f);
	SetButton->SetClickCallback<CPrimitiveComponentWidgetList>(this, &CPrimitiveComponentWidgetList::PrimitiveSpecularColorSetButtonClick);


	// EmissiveColor 세팅
	PrimitiveComponentTree->AddItem(nullptr, "EmissiveColor", "PrimitiveComponent");

	m_EmissiveColorR = PrimitiveComponentTree->CreateWidget<CEditorInput>("EmissiveColor", "EmissiveColorR", 40.f, 30.f);
	m_EmissiveColorR->SetHideName(m_EmissiveColorR->GetName());
	m_EmissiveColorR->SetInputType(EImGuiInputType::Float);

	PrimitiveComponentTree->CreateWidget<CEditorSameLine>("EmissiveColor", "Line");

	m_EmissiveColorG = PrimitiveComponentTree->CreateWidget<CEditorInput>("EmissiveColor", "EmissiveColorG", 40.f, 30.f);
	m_EmissiveColorG->SetHideName(m_EmissiveColorG->GetName());
	m_EmissiveColorG->SetInputType(EImGuiInputType::Float);

	PrimitiveComponentTree->CreateWidget<CEditorSameLine>("EmissiveColor", "Line");

	m_EmissiveColorB = PrimitiveComponentTree->CreateWidget<CEditorInput>("EmissiveColor", "EmissiveColorB", 40.f, 30.f);
	m_EmissiveColorB->SetHideName(m_EmissiveColorB->GetName());
	m_EmissiveColorB->SetInputType(EImGuiInputType::Float);

	PrimitiveComponentTree->CreateWidget<CEditorSameLine>("EmissiveColor", "Line");


	m_EmissiveColorA = PrimitiveComponentTree->CreateWidget<CEditorInput>("EmissiveColor", "EmissiveColorA", 40.f, 30.f);
	m_EmissiveColorA->SetHideName(m_EmissiveColorA->GetName());
	m_EmissiveColorA->SetInputType(EImGuiInputType::Float);

	PrimitiveComponentTree->CreateWidget<CEditorSameLine>("EmissiveColor", "Line");

	SetButton = PrimitiveComponentTree->CreateWidget<CEditorButton>("EmissiveColor", "Set", 30.f, 30.f);
	SetButton->SetClickCallback<CPrimitiveComponentWidgetList>(this, &CPrimitiveComponentWidgetList::PrimitiveEmissiveColorSetButtonClick);


	// Opacity 세팅
	PrimitiveComponentTree->AddItem(nullptr, "Opacity", "PrimitiveComponent");

	m_Opacity = PrimitiveComponentTree->CreateWidget<CEditorInput>("Opacity", "Opacity", 40.f, 30.f);
	m_Opacity->SetHideName(m_Opacity->GetName());
	m_Opacity->SetInputType(EImGuiInputType::Float);

	PrimitiveComponentTree->CreateWidget<CEditorSameLine>("Opacity", "Line");

	SetButton = PrimitiveComponentTree->CreateWidget<CEditorButton>("Opacity", "Set", 30.f, 30.f);
	SetButton->SetClickCallback<CPrimitiveComponentWidgetList>(this, &CPrimitiveComponentWidgetList::PrimitiveOpacitySetButtonClick);

    return true;
}

void CPrimitiveComponentWidgetList::SetComponentContents(CSceneComponent* Component)
{
	CPrimitiveComponent* PrimitiveComponent = (CPrimitiveComponent*)Component;

	// Texture
	m_PrimitiveImage->SetTexture(PrimitiveComponent->GetTexture());

	// BaseColor
	Vector4 BaseColor = PrimitiveComponent->GetMaterial(0)->GetBaseColor() * 255.f;
	m_BaseColorR->SetFloat(BaseColor.x);
	m_BaseColorG->SetFloat(BaseColor.y);
	m_BaseColorB->SetFloat(BaseColor.z);
	m_BaseColorA->SetFloat(BaseColor.w);

	// AmbientColor
	Vector4 AmbientColor = PrimitiveComponent->GetMaterial(0)->GetAmbientColor() * 255.f;
	m_AmbientColorR->SetFloat(AmbientColor.x);
	m_AmbientColorG->SetFloat(AmbientColor.y);
	m_AmbientColorB->SetFloat(AmbientColor.z);
	m_AmbientColorA->SetFloat(AmbientColor.w);


	// SpecularColor
	Vector4 SpecularColor = PrimitiveComponent->GetMaterial(0)->GetSpecularColor() * 255.f;
	m_SpecularColorR->SetFloat(SpecularColor.x);
	m_SpecularColorG->SetFloat(SpecularColor.y);
	m_SpecularColorB->SetFloat(SpecularColor.z);
	m_SpecularColorA->SetFloat(SpecularColor.w);


	// EmissiveColor
	Vector4 EmissiveColor = PrimitiveComponent->GetMaterial(0)->GetEmissiveColor() * 255.f;
	m_EmissiveColorR->SetFloat(EmissiveColor.x);
	m_EmissiveColorG->SetFloat(EmissiveColor.y);
	m_EmissiveColorB->SetFloat(EmissiveColor.z);
	m_EmissiveColorA->SetFloat(EmissiveColor.w);


	// Opacity
	float Opacity = PrimitiveComponent->GetMaterial(0)->GetOpacity();
	m_Opacity->SetFloat(Opacity);
}

void CPrimitiveComponentWidgetList::PrimitiveImageLoadButtonClick()
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

		m_PrimitiveImage->SetTextureFullPath(TexName, FullPath);

		// 선택한 Component의 Texture를 교체한다.
		CPrimitiveComponent* Component = (CPrimitiveComponent*)m_DetailWindow->GetSelectComponent();

		if (Component)
		{
			Component->SetTextureFullPath(TexName, FullPath);
		}
	}
}

void CPrimitiveComponentWidgetList::PrimitiveBaseColorSetButtonClick()
{
	Vector4 BaseColor = Vector4(m_BaseColorR->GetFloat() / 255.f, m_BaseColorG->GetFloat() / 255.f, m_BaseColorB->GetFloat() / 255.f, m_BaseColorA->GetFloat() / 255.f);

	CPrimitiveComponent* Component = (CPrimitiveComponent*)m_DetailWindow->GetSelectComponent();

	if (Component)
	{
		Component->GetMaterial(0)->SetBaseColor(BaseColor);
	}
}

void CPrimitiveComponentWidgetList::PrimitiveAmbientColorSetButtonClick()
{
	Vector4 AmbientColor = Vector4(m_AmbientColorR->GetFloat() / 255.f, m_AmbientColorG->GetFloat() / 255.f, m_AmbientColorB->GetFloat() / 255.f, m_AmbientColorA->GetFloat() / 255.f);

	CPrimitiveComponent* Component = (CPrimitiveComponent*)m_DetailWindow->GetSelectComponent();

	if (Component)
	{
		Component->GetMaterial(0)->SetAmbientColor(AmbientColor);
	}
}

void CPrimitiveComponentWidgetList::PrimitiveSpecularColorSetButtonClick()
{
	Vector4 SpecularColor = Vector4(m_SpecularColorR->GetFloat() / 255.f, m_SpecularColorG->GetFloat() / 255.f, m_SpecularColorB->GetFloat() / 255.f, m_SpecularColorA->GetFloat() / 255.f);

	CPrimitiveComponent* Component = (CPrimitiveComponent*)m_DetailWindow->GetSelectComponent();

	if (Component)
	{
		Component->GetMaterial(0)->SetSpecularColor(SpecularColor);
	}
}

void CPrimitiveComponentWidgetList::PrimitiveEmissiveColorSetButtonClick()
{
	Vector4 EmissiveColor = Vector4(m_EmissiveColorR->GetFloat() / 255.f, m_EmissiveColorG->GetFloat() / 255.f, m_EmissiveColorB->GetFloat() / 255.f, m_EmissiveColorA->GetFloat() / 255.f);

	CPrimitiveComponent* Component = (CPrimitiveComponent*)m_DetailWindow->GetSelectComponent();

	if (Component)
	{
		Component->GetMaterial(0)->SetEmissiveColor(EmissiveColor);
	}
}

void CPrimitiveComponentWidgetList::PrimitiveOpacitySetButtonClick()
{
	float Opacity = m_Opacity->GetFloat();

	CPrimitiveComponent* Component = (CPrimitiveComponent*)m_DetailWindow->GetSelectComponent();

	if (Component)
	{
		Component->GetMaterial(0)->SetOpacity(Opacity);
	}
}
