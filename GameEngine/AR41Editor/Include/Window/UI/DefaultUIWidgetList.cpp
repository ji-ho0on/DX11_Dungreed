#include "DefaultUIWidgetList.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "UI/UIWindow.h"
#include "../UIWidgetEditor.h"

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

CDefaultUIWidgetList::CDefaultUIWidgetList()
{
}

CDefaultUIWidgetList::~CDefaultUIWidgetList()
{
}

bool CDefaultUIWidgetList::Init()
{
	CEditorGroup* UIWidgetListGroup = CreateWidget<CEditorGroup>("UIWidgetListGroup");

	CEditorText* UIWidgetListText = UIWidgetListGroup->CreateWidget<CEditorText>("UIWidgetListText");
	UIWidgetListText->SetText("UIWidgetList");

	m_UIWidgetListBox = UIWidgetListGroup->CreateWidget<CEditorListBox>("UIWidgetListBox", 150.f);
	m_UIWidgetListBox->SetHideName(m_UIWidgetListBox->GetName());
	m_UIWidgetListBox->SetPageItemCount(8);
	m_UIWidgetListBox->SetSelectCallback<CDefaultUIWidgetList>(this, &CDefaultUIWidgetList::UIListBoxClickCallback);

	CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");

	CEditorGroup* UIWidgetSelectGroup = CreateWidget<CEditorGroup>("UIWidgetSelectGroup");

	CEditorText* UIWidgetSelectText = UIWidgetSelectGroup->CreateWidget<CEditorText>("UIWidgetSelectText");
	UIWidgetSelectText->SetText("SelectUIWidget");

	m_SelectUIWidgetInput = UIWidgetSelectGroup->CreateWidget<CEditorInput>("SelectUIWidgetInput", 150.f, 30.f);
	m_SelectUIWidgetInput->SetHideName(m_SelectUIWidgetInput->GetName());
	m_SelectUIWidgetInput->ReadOnly(true);

	Line = CreateWidget<CEditorSameLine>("Line");

	CEditorGroup* UIWidgetEditGroup = CreateWidget<CEditorGroup>("UIWidgetEditGroup");

	CEditorText* ZOrderText = UIWidgetEditGroup->CreateWidget<CEditorText>("ZOrderText");
	ZOrderText->SetText("ZOrder");

	Line = UIWidgetEditGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(60.f);

	m_ZOrder = UIWidgetEditGroup->CreateWidget<CEditorInput>("ZOrder", 80.f, 30.f);
	m_ZOrder->SetHideName("ZOrder");
	m_ZOrder->SetInputType(EImGuiInputType::Int);
	m_ZOrder->SetInputCallback<CDefaultUIWidgetList>(this, &CDefaultUIWidgetList::ZOrderCallback);

	CEditorText* PosText = UIWidgetEditGroup->CreateWidget<CEditorText>("PosText");
	PosText->SetText("Pos");

	Line = UIWidgetEditGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(60.f);

	m_Pos[0] = UIWidgetEditGroup->CreateWidget<CEditorInput>("PosX", 80.f, 30.f);
	m_Pos[0]->SetHideName("PosX");
	m_Pos[0]->SetInputType(EImGuiInputType::Float);
	m_Pos[0]->SetInputCallback<CDefaultUIWidgetList>(this, &CDefaultUIWidgetList::PosXCallback);

	Line = UIWidgetEditGroup->CreateWidget<CEditorSameLine>("Line");

	m_Pos[1] = UIWidgetEditGroup->CreateWidget<CEditorInput>("PosY", 80.f, 30.f);
	m_Pos[1]->SetHideName("PosY");
	m_Pos[1]->SetInputType(EImGuiInputType::Float);
	m_Pos[1]->SetInputCallback<CDefaultUIWidgetList>(this, &CDefaultUIWidgetList::PosYCallback);

	CEditorText* SizeText = UIWidgetEditGroup->CreateWidget<CEditorText>("SizeText");
	SizeText->SetText("Size");

	Line = UIWidgetEditGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(60.f);

	m_Size[0] = UIWidgetEditGroup->CreateWidget<CEditorInput>("SizeX", 80.f, 30.f);
	m_Size[0]->SetHideName("SizeX");
	m_Size[0]->SetInputType(EImGuiInputType::Float);
	m_Size[0]->SetInputCallback<CDefaultUIWidgetList>(this, &CDefaultUIWidgetList::SizeXCallback);

	Line = UIWidgetEditGroup->CreateWidget<CEditorSameLine>("Line");

	m_Size[1] = UIWidgetEditGroup->CreateWidget<CEditorInput>("SizeY", 80.f, 30.f);
	m_Size[1]->SetHideName("SizeY");
	m_Size[1]->SetInputType(EImGuiInputType::Float);
	m_Size[1]->SetInputCallback<CDefaultUIWidgetList>(this, &CDefaultUIWidgetList::SizeYCallback);

	CEditorText* PivotText = UIWidgetEditGroup->CreateWidget<CEditorText>("PivotText");
	PivotText->SetText("Pivot");

	Line = UIWidgetEditGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(60.f);

	m_Pivot[0] = UIWidgetEditGroup->CreateWidget<CEditorInput>("PivotX", 80.f, 30.f);
	m_Pivot[0]->SetHideName("PivotX");
	m_Pivot[0]->SetInputType(EImGuiInputType::Float);
	m_Pivot[0]->SetInputCallback<CDefaultUIWidgetList>(this, &CDefaultUIWidgetList::PivotXCallback);

	Line = UIWidgetEditGroup->CreateWidget<CEditorSameLine>("Line");

	m_Pivot[1] = UIWidgetEditGroup->CreateWidget<CEditorInput>("PivotY", 80.f, 30.f);
	m_Pivot[1]->SetHideName("PivotY");
	m_Pivot[1]->SetInputType(EImGuiInputType::Float);
	m_Pivot[1]->SetInputCallback<CDefaultUIWidgetList>(this, &CDefaultUIWidgetList::PivotYCallback);

	CEditorText* AngleText = UIWidgetEditGroup->CreateWidget<CEditorText>("AngleText");
	AngleText->SetText("Angle");

	Line = UIWidgetEditGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(60.f);

	m_Angle = UIWidgetEditGroup->CreateWidget<CEditorInput>("Angle", 80.f, 30.f);
	m_Angle->SetHideName("Angle");
	m_Angle->SetInputType(EImGuiInputType::Float);
	m_Angle->SetInputCallback<CDefaultUIWidgetList>(this, &CDefaultUIWidgetList::AngleCallback);

	CEditorText* OpacityText = UIWidgetEditGroup->CreateWidget<CEditorText>("OpacityText");
	OpacityText->SetText("Opacity");

	Line = UIWidgetEditGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(60.f);

	m_Opacity = UIWidgetEditGroup->CreateWidget<CEditorInput>("Opacity", 80.f, 30.f);
	m_Opacity->SetHideName("Opacity");
	m_Opacity->SetInputType(EImGuiInputType::Float);
	m_Opacity->SetInputCallback<CDefaultUIWidgetList>(this, &CDefaultUIWidgetList::OpacityCallback);

	CEditorText* TintText = UIWidgetEditGroup->CreateWidget<CEditorText>("TintText");
	TintText->SetText("Tint");

	Line = UIWidgetEditGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(60.f);

	m_Tint[0] = UIWidgetEditGroup->CreateWidget<CEditorInput>("TintR", 60.f, 30.f);
	m_Tint[0]->SetHideName("TintR");
	m_Tint[0]->SetInputType(EImGuiInputType::Float);
	m_Tint[0]->SetInputCallback<CDefaultUIWidgetList>(this, &CDefaultUIWidgetList::TintRCallback);

	Line = UIWidgetEditGroup->CreateWidget<CEditorSameLine>("Line");

	m_Tint[1] = UIWidgetEditGroup->CreateWidget<CEditorInput>("TintG", 60.f, 30.f);
	m_Tint[1]->SetHideName("TintG");
	m_Tint[1]->SetInputType(EImGuiInputType::Float);
	m_Tint[1]->SetInputCallback<CDefaultUIWidgetList>(this, &CDefaultUIWidgetList::TintGCallback);

	Line = UIWidgetEditGroup->CreateWidget<CEditorSameLine>("Line");

	m_Tint[2] = UIWidgetEditGroup->CreateWidget<CEditorInput>("TintB", 60.f, 30.f);
	m_Tint[2]->SetHideName("TintB");
	m_Tint[2]->SetInputType(EImGuiInputType::Float);
	m_Tint[2]->SetInputCallback<CDefaultUIWidgetList>(this, &CDefaultUIWidgetList::TintBCallback);

	Line = UIWidgetEditGroup->CreateWidget<CEditorSameLine>("Line");

	m_Tint[3] = UIWidgetEditGroup->CreateWidget<CEditorInput>("TintA", 60.f, 30.f);
	m_Tint[3]->SetHideName("TintA");
	m_Tint[3]->SetInputType(EImGuiInputType::Float);
	m_Tint[3]->SetInputCallback<CDefaultUIWidgetList>(this, &CDefaultUIWidgetList::TintACallback);

	CreateWidget<CEditorNewLine>("NewLine");

    return true;
}

void CDefaultUIWidgetList::SetUIWidgetContents(CUIWidget* UIWidget)
{
	int ZOrder = UIWidget->GetZOrder();
	m_ZOrder->SetInt(ZOrder);

	Vector2 Pos = UIWidget->GetPos();
	m_Pos[0]->SetFloat(Pos.x);
	m_Pos[1]->SetFloat(Pos.y);

	Vector2 Size = UIWidget->GetSize();
	m_Size[0]->SetFloat(Size.x);
	m_Size[1]->SetFloat(Size.y);

	Vector2 Pivot = UIWidget->GetPivot();
	m_Pivot[0]->SetFloat(Pivot.x);
	m_Pivot[1]->SetFloat(Pivot.y);

	float Angle = UIWidget->GetAngle();
	m_ZOrder->SetFloat(Angle);

	float Opacity = UIWidget->GetOpacity();
	m_ZOrder->SetFloat(Opacity);

	Vector4 Tint = UIWidget->GetTint();
	Tint *= 255.f;
	m_Tint[0]->SetFloat(Tint.x);
	m_Tint[1]->SetFloat(Tint.y);
	m_Tint[2]->SetFloat(Tint.z);
	m_Tint[3]->SetFloat(Tint.w);
}

void CDefaultUIWidgetList::LoadUIWidget(CUIWindow* UIWindw)
{
	m_UIWidgetListBox->Clear();

	std::vector<std::string> vecWidgetName;

	UIWindw->GetWidgetNames(vecWidgetName);

	size_t Size = vecWidgetName.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_UIWidgetListBox->AddItem(vecWidgetName[i]);
	}
}

void CDefaultUIWidgetList::UIListBoxClickCallback(int Index, const std::string& Item)
{
	m_SelectUIWidgetItem = Item;

	m_SelectUIWidgetInput->SetText(Item.c_str());

	CUIWidget* UIWidget = m_UIWidgetEditor->GetSelectUIWindow()->FindWidgetName(Item);

	if (UIWidget)
		m_UIWidgetEditor->SetSelectUIWidget(UIWidget);
}

void CDefaultUIWidgetList::ZOrderCallback()
{
	CUIWidget* UIWidget = m_UIWidgetEditor->GetSelectUIWidget();

	if (UIWidget)
		UIWidget->SetZOrder(m_ZOrder->GetInt());
}

void CDefaultUIWidgetList::PosXCallback()
{
	CUIWidget* UIWidget = m_UIWidgetEditor->GetSelectUIWidget();

	if (UIWidget)
		UIWidget->SetPos(m_Pos[0]->GetFloat(), m_Pos[1]->GetFloat());
}

void CDefaultUIWidgetList::PosYCallback()
{
	CUIWidget* UIWidget = m_UIWidgetEditor->GetSelectUIWidget();

	if (UIWidget)
		UIWidget->SetPos(m_Pos[0]->GetFloat(), m_Pos[1]->GetFloat());
}

void CDefaultUIWidgetList::SizeXCallback()
{
	CUIWidget* UIWidget = m_UIWidgetEditor->GetSelectUIWidget();

	if (UIWidget)
		UIWidget->SetSize(m_Size[0]->GetFloat(), m_Size[1]->GetFloat());
}

void CDefaultUIWidgetList::SizeYCallback()
{
	CUIWidget* UIWidget = m_UIWidgetEditor->GetSelectUIWidget();

	if (UIWidget)
		UIWidget->SetSize(m_Size[0]->GetFloat(), m_Size[1]->GetFloat());
}

void CDefaultUIWidgetList::PivotXCallback()
{
	CUIWidget* UIWidget = m_UIWidgetEditor->GetSelectUIWidget();

	if (UIWidget)
		UIWidget->SetPivot(m_Pivot[0]->GetFloat(), m_Pivot[1]->GetFloat());
}

void CDefaultUIWidgetList::PivotYCallback()
{
	CUIWidget* UIWidget = m_UIWidgetEditor->GetSelectUIWidget();

	if (UIWidget)
		UIWidget->SetPivot(m_Pivot[0]->GetFloat(), m_Pivot[1]->GetFloat());
}

void CDefaultUIWidgetList::AngleCallback()
{
	CUIWidget* UIWidget = m_UIWidgetEditor->GetSelectUIWidget();

	if (UIWidget)
		UIWidget->SetAngle(m_Angle->GetFloat());
}

void CDefaultUIWidgetList::OpacityCallback()
{
	CUIWidget* UIWidget = m_UIWidgetEditor->GetSelectUIWidget();

	if (UIWidget)
		UIWidget->SetOpacity(m_Opacity->GetFloat());
}

void CDefaultUIWidgetList::TintRCallback()
{
	CUIWidget* UIWidget = m_UIWidgetEditor->GetSelectUIWidget();

	if (UIWidget)
		UIWidget->SetTint((unsigned char)m_Tint[0]->GetFloat(), (unsigned char)m_Tint[1]->GetFloat(), (unsigned char)m_Tint[2]->GetFloat(), (unsigned char)m_Tint[3]->GetFloat());
}

void CDefaultUIWidgetList::TintGCallback()
{
	CUIWidget* UIWidget = m_UIWidgetEditor->GetSelectUIWidget();

	if (UIWidget)
		UIWidget->SetTint((unsigned char)m_Tint[0]->GetFloat(), (unsigned char)m_Tint[1]->GetFloat(), (unsigned char)m_Tint[2]->GetFloat(), (unsigned char)m_Tint[3]->GetFloat());
}

void CDefaultUIWidgetList::TintBCallback()
{
	CUIWidget* UIWidget = m_UIWidgetEditor->GetSelectUIWidget();

	if (UIWidget)
		UIWidget->SetTint((unsigned char)m_Tint[0]->GetFloat(), (unsigned char)m_Tint[1]->GetFloat(), (unsigned char)m_Tint[2]->GetFloat(), (unsigned char)m_Tint[3]->GetFloat());
}

void CDefaultUIWidgetList::TintACallback()
{
	CUIWidget* UIWidget = m_UIWidgetEditor->GetSelectUIWidget();

	if (UIWidget)
		UIWidget->SetTint((unsigned char)m_Tint[0]->GetFloat(), (unsigned char)m_Tint[1]->GetFloat(), (unsigned char)m_Tint[2]->GetFloat(), (unsigned char)m_Tint[3]->GetFloat());
}
