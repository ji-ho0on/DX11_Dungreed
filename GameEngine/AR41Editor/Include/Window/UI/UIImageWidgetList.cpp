#include "UIImageWidgetList.h"
#include "../UIWidgetEditor.h"
#include "UI/UIImage.h"
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

CUIImageWidgetList::CUIImageWidgetList()
{
}

CUIImageWidgetList::~CUIImageWidgetList()
{
}

bool CUIImageWidgetList::Init()
{
	CEditorGroup* ImageGroup = CreateWidget<CEditorGroup>("ImageGroup");

	CEditorText* ImageText = ImageGroup->CreateWidget<CEditorText>("ImageText");
	ImageText->SetText("UIImage");

    m_Image = ImageGroup->CreateWidget<CEditorImage>("Image");
    m_Image->SetSize(100.f, 100.f);

	ImageGroup->CreateWidget<CEditorSameLine>("Line");

    CEditorButton* ImageSetButton = ImageGroup->CreateWidget<CEditorButton>("ImageSet");
    ImageSetButton->SetSize(50.f, 30.f);
    ImageSetButton->SetClickCallback<CUIImageWidgetList>(this, &CUIImageWidgetList::ImageSetButton);

	CreateWidget<CEditorSameLine>("Line")->SetSpacing(15.f);

	CEditorGroup* ImageSettingGroup = CreateWidget<CEditorGroup>("ImageSettingGroup");

	CEditorText* ImageTintText = ImageSettingGroup->CreateWidget<CEditorText>("ImageTintText");
	ImageTintText->SetText("ImageTint");

	CEditorSameLine* Line = ImageSettingGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(80.f);

	m_ImageTint[0] = ImageSettingGroup->CreateWidget<CEditorInput>("ImageTintR", 60.f, 30.f);
	m_ImageTint[0]->SetHideName("ImageTintR");
	m_ImageTint[0]->SetInputType(EImGuiInputType::Float);
	m_ImageTint[0]->SetInputCallback<CUIImageWidgetList>(this, &CUIImageWidgetList::ImageTintRCallback);

	Line = ImageSettingGroup->CreateWidget<CEditorSameLine>("Line");

	m_ImageTint[1] = ImageSettingGroup->CreateWidget<CEditorInput>("ImageTintG", 60.f, 30.f);
	m_ImageTint[1]->SetHideName("ImageTintG");
	m_ImageTint[1]->SetInputType(EImGuiInputType::Float);
	m_ImageTint[1]->SetInputCallback<CUIImageWidgetList>(this, &CUIImageWidgetList::ImageTintGCallback);

	Line = ImageSettingGroup->CreateWidget<CEditorSameLine>("Line");

	m_ImageTint[2] = ImageSettingGroup->CreateWidget<CEditorInput>("ImageTintB", 60.f, 30.f);
	m_ImageTint[2]->SetHideName("ImageTintB");
	m_ImageTint[2]->SetInputType(EImGuiInputType::Float);
	m_ImageTint[2]->SetInputCallback<CUIImageWidgetList>(this, &CUIImageWidgetList::ImageTintBCallback);

	Line = ImageSettingGroup->CreateWidget<CEditorSameLine>("Line");

	m_ImageTint[3] = ImageSettingGroup->CreateWidget<CEditorInput>("ImageTintA", 60.f, 30.f);
	m_ImageTint[3]->SetHideName("ImageTintA");
	m_ImageTint[3]->SetInputType(EImGuiInputType::Float);
	m_ImageTint[3]->SetInputCallback<CUIImageWidgetList>(this, &CUIImageWidgetList::ImageTintACallback);


	CEditorText* PlayTimeText = ImageSettingGroup->CreateWidget<CEditorText>("PlayTimeText");
	PlayTimeText->SetText("PlayTime");

	Line = ImageSettingGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(80.f);

	m_ImagePlayTime = ImageSettingGroup->CreateWidget<CEditorInput>("ImagePlayTime", 60.f, 30.f);
	m_ImagePlayTime->SetHideName(m_ImagePlayTime->GetName());
	m_ImagePlayTime->SetInputType(EImGuiInputType::Float);
	m_ImagePlayTime->SetInputCallback<CUIImageWidgetList>(this, &CUIImageWidgetList::SetImagePlayTime);

	CEditorText* PlayScaleText = ImageSettingGroup->CreateWidget<CEditorText>("PlayScaleText");
	PlayScaleText->SetText("PlayScale");

	Line = ImageSettingGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(80.f);

	m_ImagePlayScale = ImageSettingGroup->CreateWidget<CEditorInput>("ImagePlayScale", 60.f, 30.f);
	m_ImagePlayScale->SetHideName(m_ImagePlayScale->GetName());
	m_ImagePlayScale->SetInputType(EImGuiInputType::Float);
	m_ImagePlayScale->SetInputCallback<CUIImageWidgetList>(this, &CUIImageWidgetList::SetImagePlayScale);

	CEditorText* LoopText = ImageSettingGroup->CreateWidget<CEditorText>("LoopText");
	LoopText->SetText("Loop");

	Line = ImageSettingGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(80.f);

	m_ImageLoop = ImageSettingGroup->CreateWidget<CEditorCheckBox>("ImageLoop");
	m_ImageLoop->SetHideName(m_ImageLoop->GetName());
	m_ImageLoop->SetCheckCallback<CUIImageWidgetList>(this, &CUIImageWidgetList::SetImageLoop);

	CEditorText* ReverseText = ImageSettingGroup->CreateWidget<CEditorText>("ReverseText");
	ReverseText->SetText("Reverse");

	Line = ImageSettingGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(80.f);

	m_ImageReverse = ImageSettingGroup->CreateWidget<CEditorCheckBox>("ImageReverse");
	m_ImageReverse->SetHideName(m_ImageReverse->GetName());
	m_ImageReverse->SetCheckCallback<CUIImageWidgetList>(this, &CUIImageWidgetList::SetImageReverse);

    return true;
}

void CUIImageWidgetList::SetUIWidgetContents(CUIWidget* UIWidget)
{
    CUIImage* UIImage = (CUIImage*)UIWidget;

    UIWidgetImageInfo TextureInfo = UIImage->GetTextureInfo();

    if (TextureInfo.Texture)
        m_Image->SetTexture(TextureInfo.Texture);

	Vector4 Tint = TextureInfo.Tint;
	Tint *= 255.f;
	m_ImageTint[0]->SetFloat(Tint.x);
	m_ImageTint[1]->SetFloat(Tint.y);
	m_ImageTint[2]->SetFloat(Tint.z);
	m_ImageTint[3]->SetFloat(Tint.w);

	float PlayTime = TextureInfo.PlayTime;
	m_ImagePlayTime->SetFloat(PlayTime);

	float PlayScale = TextureInfo.PlayScale;
	m_ImagePlayScale->SetFloat(PlayScale);

	bool ImageLoop = TextureInfo.Loop;
	m_ImageLoop->SetCheck(ImageLoop);

	bool ImageReverse = TextureInfo.Reverse;
	m_ImageReverse->SetCheck(ImageReverse);
}

void CUIImageWidgetList::ImageSetButton()
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

		m_Image->SetTextureFullPath(TexName, FullPath);

		// 선택한 Component의 Texture를 교체한다.
		CUIImage* UIImage = (CUIImage*)m_UIWidgetEditor->GetSelectUIWidget();

		if (UIImage)
		{
			UIImage->SetTextureFullPath(TexName, FullPath);
		}
	}
}

void CUIImageWidgetList::ImageTintRCallback()
{
	CUIImage* UIImage = (CUIImage*)m_UIWidgetEditor->GetSelectUIWidget();

	if (UIImage)
		UIImage->SetImageTint((unsigned char)m_ImageTint[0]->GetFloat(), (unsigned char)m_ImageTint[1]->GetFloat(), (unsigned char)m_ImageTint[2]->GetFloat(), (unsigned char)m_ImageTint[3]->GetFloat());
}

void CUIImageWidgetList::ImageTintGCallback()
{
	CUIImage* UIImage = (CUIImage*)m_UIWidgetEditor->GetSelectUIWidget();

	if (UIImage)
		UIImage->SetImageTint((unsigned char)m_ImageTint[0]->GetFloat(), (unsigned char)m_ImageTint[1]->GetFloat(), (unsigned char)m_ImageTint[2]->GetFloat(), (unsigned char)m_ImageTint[3]->GetFloat());
}

void CUIImageWidgetList::ImageTintBCallback()
{
	CUIImage* UIImage = (CUIImage*)m_UIWidgetEditor->GetSelectUIWidget();

	if (UIImage)
		UIImage->SetImageTint((unsigned char)m_ImageTint[0]->GetFloat(), (unsigned char)m_ImageTint[1]->GetFloat(), (unsigned char)m_ImageTint[2]->GetFloat(), (unsigned char)m_ImageTint[3]->GetFloat());
}

void CUIImageWidgetList::ImageTintACallback()
{
	CUIImage* UIImage = (CUIImage*)m_UIWidgetEditor->GetSelectUIWidget();

	if (UIImage)
		UIImage->SetImageTint((unsigned char)m_ImageTint[0]->GetFloat(), (unsigned char)m_ImageTint[1]->GetFloat(), (unsigned char)m_ImageTint[2]->GetFloat(), (unsigned char)m_ImageTint[3]->GetFloat());
}

void CUIImageWidgetList::SetImagePlayTime()
{
	CUIImage* UIImage = (CUIImage*)m_UIWidgetEditor->GetSelectUIWidget();

	if (UIImage)
		UIImage->SetPlayTime(m_ImagePlayTime->GetFloat());
}

void CUIImageWidgetList::SetImagePlayScale()
{
	CUIImage* UIImage = (CUIImage*)m_UIWidgetEditor->GetSelectUIWidget();

	if (UIImage)
		UIImage->SetPlayScale(m_ImagePlayScale->GetFloat());
}

void CUIImageWidgetList::SetImageLoop()
{
	CUIImage* UIImage = (CUIImage*)m_UIWidgetEditor->GetSelectUIWidget();

	if (UIImage)
		UIImage->SetLoop(m_ImageLoop->GetCheck());
}

void CUIImageWidgetList::SetImageReverse()
{
	CUIImage* UIImage = (CUIImage*)m_UIWidgetEditor->GetSelectUIWidget();

	if (UIImage)
		UIImage->SetReverse(m_ImageReverse->GetCheck());
}
