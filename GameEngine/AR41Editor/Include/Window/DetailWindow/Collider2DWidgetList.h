#pragma once

#include "ComponentWidgetList.h"

class CCollider2DWidgetList :
    public CComponentWidgetList
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CDetailWindow;

protected:
	CCollider2DWidgetList();
	virtual ~CCollider2DWidgetList();

private:

public:
	virtual bool Init();

private:

};

