#pragma once

#include "ComponentWidgetList.h"

class CCollider3DWidgetList :
    public CComponentWidgetList
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CDetailWindow;

protected:
	CCollider3DWidgetList();
	virtual ~CCollider3DWidgetList();

private:

public:
	virtual bool Init();

private:

};

