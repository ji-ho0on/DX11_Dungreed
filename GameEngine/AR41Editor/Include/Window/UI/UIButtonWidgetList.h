#pragma once

#include "UIWidgetList.h"

class CUIButtonWidgetList :
    public CUIWidgetList
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CUIWidgetEditor;

protected:
	CUIButtonWidgetList();
	virtual ~CUIButtonWidgetList();

public:
	virtual bool Init();
	virtual void SetUIWidgetContents(class CUIWidget* UIWidget);
};

