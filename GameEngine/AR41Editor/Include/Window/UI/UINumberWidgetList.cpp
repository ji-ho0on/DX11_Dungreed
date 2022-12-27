#include "UINumberWidgetList.h"
#include "../UIWidgetEditor.h"
#include "UI/UINumber.h"
#include "Engine.h"
#include "PathManager.h"

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

CUINumberWidgetList::CUINumberWidgetList()
{
}

CUINumberWidgetList::~CUINumberWidgetList()
{
}

bool CUINumberWidgetList::Init()
{
	CEditorGroup* NumberGroup = CreateWidget<CEditorGroup>("NumberGroup");

	CEditorText* NumberText = NumberGroup->CreateWidget<CEditorText>("NumberText");
	NumberText->SetText("Number");

	m_Number = NumberGroup->CreateWidget<CEditorInput>("Number");
	m_Number->SetHideName(m_Number->GetName());
	m_Number->SetInputType(EImGuiInputType::Int);

	NumberGroup->CreateWidget<CEditorSameLine>("Line");

	CEditorButton* NumberSetButton = NumberGroup->CreateWidget<CEditorButton>("NumberSet");
	NumberSetButton->SetSize(50.f, 30.f);
	NumberSetButton->SetClickCallback<CUINumberWidgetList>(this, &CUINumberWidgetList::NumberSetButton);


	CEditorText* NumberImageText = NumberGroup->CreateWidget<CEditorText>("NumberImageText");
	NumberImageText->SetText("NumberImage");

	m_NumberImage = NumberGroup->CreateWidget<CEditorImage>("NumberImage");
	m_NumberImage->SetSize(100.f, 100.f);

	NumberGroup->CreateWidget<CEditorSameLine>("Line");

	CEditorButton* NumberImageSetButton = NumberGroup->CreateWidget<CEditorButton>("NumberImageSet");
	NumberImageSetButton->SetSize(50.f, 30.f);
	NumberImageSetButton->SetClickCallback<CUINumberWidgetList>(this, &CUINumberWidgetList::NumberImageSetButton);

	CreateWidget<CEditorSameLine>("Line")->SetSpacing(15.f);

	CEditorGroup* NumberImageSettingGroup = CreateWidget<CEditorGroup>("NumberImageSettingGroup");

	CEditorText* NumberImageTintText = NumberImageSettingGroup->CreateWidget<CEditorText>("NumberImageTintText");
	NumberImageTintText->SetText("ImageTint");

	CEditorSameLine* Line = NumberImageSettingGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(80.f);

	m_NumberImageTint[0] = NumberImageSettingGroup->CreateWidget<CEditorInput>("NumberImageTintR", 60.f, 30.f);
	m_NumberImageTint[0]->SetHideName("NumberImageTintR");
	m_NumberImageTint[0]->SetInputType(EImGuiInputType::Float);
	m_NumberImageTint[0]->SetInputCallback<CUINumberWidgetList>(this, &CUINumberWidgetList::NumberImageTintRCallback);

	Line = NumberImageSettingGroup->CreateWidget<CEditorSameLine>("Line");

	m_NumberImageTint[1] = NumberImageSettingGroup->CreateWidget<CEditorInput>("NumberImageTintG", 60.f, 30.f);
	m_NumberImageTint[1]->SetHideName("NumberImageTintG");
	m_NumberImageTint[1]->SetInputType(EImGuiInputType::Float);
	m_NumberImageTint[1]->SetInputCallback<CUINumberWidgetList>(this, &CUINumberWidgetList::NumberImageTintGCallback);

	Line = NumberImageSettingGroup->CreateWidget<CEditorSameLine>("Line");

	m_NumberImageTint[2] = NumberImageSettingGroup->CreateWidget<CEditorInput>("NumberImageTintB", 60.f, 30.f);
	m_NumberImageTint[2]->SetHideName("NumberImageTintB");
	m_NumberImageTint[2]->SetInputType(EImGuiInputType::Float);
	m_NumberImageTint[2]->SetInputCallback<CUINumberWidgetList>(this, &CUINumberWidgetList::NumberImageTintBCallback);

	Line = NumberImageSettingGroup->CreateWidget<CEditorSameLine>("Line");

	m_NumberImageTint[3] = NumberImageSettingGroup->CreateWidget<CEditorInput>("NumberImageTintA", 60.f, 30.f);
	m_NumberImageTint[3]->SetHideName("NumberImageTintA");
	m_NumberImageTint[3]->SetInputType(EImGuiInputType::Float);
	m_NumberImageTint[3]->SetInputCallback<CUINumberWidgetList>(this, &CUINumberWidgetList::NumberImageTintACallback);


	CEditorText* NumberPlayTimeText = NumberImageSettingGroup->CreateWidget<CEditorText>("NumberPlayTimeText");
	NumberPlayTimeText->SetText("PlayTime");

	Line = NumberImageSettingGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(80.f);

	m_NumberImagePlayTime = NumberImageSettingGroup->CreateWidget<CEditorInput>("NumberImagePlayTime", 60.f, 30.f);
	m_NumberImagePlayTime->SetHideName(m_NumberImagePlayTime->GetName());
	m_NumberImagePlayTime->SetInputType(EImGuiInputType::Float);
	m_NumberImagePlayTime->SetInputCallback<CUINumberWidgetList>(this, &CUINumberWidgetList::SetNumberImagePlayTime);

	CEditorText* NumberPlayScaleText = NumberImageSettingGroup->CreateWidget<CEditorText>("NumberPlayScaleText");
	NumberPlayScaleText->SetText("PlayScale");

	Line = NumberImageSettingGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(80.f);

	m_NumberImagePlayScale = NumberImageSettingGroup->CreateWidget<CEditorInput>("NumberImagePlayScale", 60.f, 30.f);
	m_NumberImagePlayScale->SetHideName(m_NumberImagePlayScale->GetName());
	m_NumberImagePlayScale->SetInputType(EImGuiInputType::Float);
	m_NumberImagePlayScale->SetInputCallback<CUINumberWidgetList>(this, &CUINumberWidgetList::SetNumberImagePlayScale);

	CEditorText* NumberLoopText = NumberImageSettingGroup->CreateWidget<CEditorText>("NumberLoopText");
	NumberLoopText->SetText("Loop");

	Line = NumberImageSettingGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(80.f);

	m_NumberImageLoop = NumberImageSettingGroup->CreateWidget<CEditorCheckBox>("NumberImageLoop");
	m_NumberImageLoop->SetHideName(m_NumberImageLoop->GetName());
	m_NumberImageLoop->SetCheckCallback<CUINumberWidgetList>(this, &CUINumberWidgetList::SetNumberImageLoop);

	CEditorText* NumberReverseText = NumberImageSettingGroup->CreateWidget<CEditorText>("NumberReverseText");
	NumberReverseText->SetText("Reverse");

	Line = NumberImageSettingGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(80.f);

	m_NumberImageReverse = NumberImageSettingGroup->CreateWidget<CEditorCheckBox>("NumberImageReverse");
	m_NumberImageReverse->SetHideName(m_NumberImageReverse->GetName());
	m_NumberImageReverse->SetCheckCallback<CUINumberWidgetList>(this, &CUINumberWidgetList::SetNumberImageReverse);

    return true;
}

void CUINumberWidgetList::SetUIWidgetContents(CUIWidget* UIWidget)
{
	CUINumber* UINumber = (CUINumber*)UIWidget;

	unsigned int Number = UINumber->GetNumber();
	m_Number->SetInt((int)Number);

	UIWidgetImageInfo TextureInfo = UINumber->GetTextureInfo();

	if (TextureInfo.Texture)
		m_NumberImage->SetTexture(TextureInfo.Texture);

	Vector4 Tint = TextureInfo.Tint;
	Tint *= 255.f;
	m_NumberImageTint[0]->SetFloat(Tint.x);
	m_NumberImageTint[1]->SetFloat(Tint.y);
	m_NumberImageTint[2]->SetFloat(Tint.z);
	m_NumberImageTint[3]->SetFloat(Tint.w);

	float PlayTime = TextureInfo.PlayTime;
	m_NumberImagePlayTime->SetFloat(PlayTime);

	float PlayScale = TextureInfo.PlayScale;
	m_NumberImagePlayScale->SetFloat(PlayScale);

	bool ImageLoop = TextureInfo.Loop;
	m_NumberImageLoop->SetCheck(ImageLoop);

	bool ImageReverse = TextureInfo.Reverse;
	m_NumberImageReverse->SetCheck(ImageReverse);
}

void CUINumberWidgetList::NumberSetButton()
{
	int Number = m_Number->GetInt();

	if (Number < 0)
		return;

	CUINumber* UINumber = (CUINumber*)m_UIWidgetEditor->GetSelectUIWidget();

	if (UINumber)
		UINumber->SetNumber((unsigned int)Number);
}

void CUINumberWidgetList::NumberImageSetButton()
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

		m_NumberImage->SetTextureFullPath(TexName, FullPath);

		// 선택한 Component의 Texture를 교체한다.
		CUINumber* UINumber = (CUINumber*)m_UIWidgetEditor->GetSelectUIWidget();

		if (UINumber)
		{
			UINumber->SetTextureFullPath(TexName, FullPath);
		}
	}
}

void CUINumberWidgetList::NumberImageTintRCallback()
{
	CUINumber* UINumber = (CUINumber*)m_UIWidgetEditor->GetSelectUIWidget();

	if (UINumber)
		UINumber->SetImageTint((unsigned char)m_NumberImageTint[0]->GetFloat(), (unsigned char)m_NumberImageTint[1]->GetFloat(), (unsigned char)m_NumberImageTint[2]->GetFloat(), (unsigned char)m_NumberImageTint[3]->GetFloat());
}

void CUINumberWidgetList::NumberImageTintGCallback()
{
	CUINumber* UINumber = (CUINumber*)m_UIWidgetEditor->GetSelectUIWidget();

	if (UINumber)
		UINumber->SetImageTint((unsigned char)m_NumberImageTint[0]->GetFloat(), (unsigned char)m_NumberImageTint[1]->GetFloat(), (unsigned char)m_NumberImageTint[2]->GetFloat(), (unsigned char)m_NumberImageTint[3]->GetFloat());
}

void CUINumberWidgetList::NumberImageTintBCallback()
{
	CUINumber* UINumber = (CUINumber*)m_UIWidgetEditor->GetSelectUIWidget();

	if (UINumber)
		UINumber->SetImageTint((unsigned char)m_NumberImageTint[0]->GetFloat(), (unsigned char)m_NumberImageTint[1]->GetFloat(), (unsigned char)m_NumberImageTint[2]->GetFloat(), (unsigned char)m_NumberImageTint[3]->GetFloat());
}

void CUINumberWidgetList::NumberImageTintACallback()
{
	CUINumber* UINumber = (CUINumber*)m_UIWidgetEditor->GetSelectUIWidget();

	if (UINumber)
		UINumber->SetImageTint((unsigned char)m_NumberImageTint[0]->GetFloat(), (unsigned char)m_NumberImageTint[1]->GetFloat(), (unsigned char)m_NumberImageTint[2]->GetFloat(), (unsigned char)m_NumberImageTint[3]->GetFloat());
}

void CUINumberWidgetList::SetNumberImagePlayTime()
{
	CUINumber* UINumber = (CUINumber*)m_UIWidgetEditor->GetSelectUIWidget();

	if (UINumber)
		UINumber->SetPlayTime(m_NumberImagePlayTime->GetFloat());
}

void CUINumberWidgetList::SetNumberImagePlayScale()
{
	CUINumber* UINumber = (CUINumber*)m_UIWidgetEditor->GetSelectUIWidget();

	if (UINumber)
		UINumber->SetPlayScale(m_NumberImagePlayScale->GetFloat());
}

void CUINumberWidgetList::SetNumberImageLoop()
{
	CUINumber* UINumber = (CUINumber*)m_UIWidgetEditor->GetSelectUIWidget();

	if (UINumber)
		UINumber->SetLoop(m_NumberImageLoop->GetCheck());
}

void CUINumberWidgetList::SetNumberImageReverse()
{
	CUINumber* UINumber = (CUINumber*)m_UIWidgetEditor->GetSelectUIWidget();

	if (UINumber)
		UINumber->SetReverse(m_NumberImageReverse->GetCheck());
}
