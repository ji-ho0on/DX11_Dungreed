#pragma once

#include "UIWidgetList.h"

class CUIProgressBarWidgetList :
    public CUIWidgetList
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CUIWidgetEditor;

protected:
	CUIProgressBarWidgetList();
	virtual ~CUIProgressBarWidgetList();

public:
	virtual bool Init();
	virtual void SetUIWidgetContents(class CUIWidget* UIWidget);
};

