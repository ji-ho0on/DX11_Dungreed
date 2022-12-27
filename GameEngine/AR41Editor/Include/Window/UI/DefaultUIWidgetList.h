#pragma once

#include "UIWidgetList.h"

class CDefaultUIWidgetList :
    public CUIWidgetList
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CUIWidgetEditor;

protected:
	CDefaultUIWidgetList();
	virtual ~CDefaultUIWidgetList();

private:
	class CEditorListBox*	m_UIWidgetListBox;
	std::string				m_SelectUIWidgetItem;

	class CEditorInput*		m_SelectUIWidgetInput;

	class CEditorInput*		m_ZOrder;
	class CEditorInput*		m_Pos[2];
	class CEditorInput*		m_Size[2];
	class CEditorInput*		m_Pivot[2];
	class CEditorInput*		m_Angle;
	class CEditorInput*		m_Opacity;
	class CEditorInput*		m_Tint[4];

public:
	virtual bool Init();
	virtual void SetUIWidgetContents(class CUIWidget* UIWidget);

private:
	void LoadUIWidget(class CUIWindow* UIWindw);
	void UIListBoxClickCallback(int Index, const std::string& Item);
	void ZOrderCallback();
	void PosXCallback();
	void PosYCallback();
	void SizeXCallback();
	void SizeYCallback();
	void PivotXCallback();
	void PivotYCallback();
	void AngleCallback();
	void OpacityCallback();
	void TintRCallback();
	void TintGCallback();
	void TintBCallback();
	void TintACallback();
};

