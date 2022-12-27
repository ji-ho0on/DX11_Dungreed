#pragma once

#include "ComponentWidgetList.h"

class CSceneComponentWidgetList :
    public CComponentWidgetList
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CDetailWindow;

protected:
	CSceneComponentWidgetList();
	virtual ~CSceneComponentWidgetList();

public:
	virtual bool Init();
};

