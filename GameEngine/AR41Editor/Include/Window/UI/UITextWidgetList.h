#pragma once

#include "UIWidgetList.h"

class CUITextWidgetList :
    public CUIWidgetList
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CUIWidgetEditor;

protected:
	CUITextWidgetList();
	virtual ~CUITextWidgetList();

public:
	virtual bool Init();
	virtual void SetUIWidgetContents(class CUIWidget* UIWidget);
};

