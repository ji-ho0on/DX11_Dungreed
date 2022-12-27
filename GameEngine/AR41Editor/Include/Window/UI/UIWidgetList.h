#pragma once

#include "Editor\EditorGroup.h"

class CUIWidgetList :
    public CEditorGroup
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CUIWidgetEditor;

protected:
	CUIWidgetList();
	virtual ~CUIWidgetList();

protected:
	class CUIWidgetEditor* m_UIWidgetEditor;

public:
	virtual bool Init();
	virtual void SetUIWidgetContents(class CUIWidget* UIWidget);
};

