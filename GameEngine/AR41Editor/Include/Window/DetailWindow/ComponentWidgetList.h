#pragma once

#include "Editor\EditorGroup.h"

class CComponentWidgetList :
    public CEditorGroup
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CDetailWindow;

protected:
	CComponentWidgetList();
	virtual ~CComponentWidgetList();

protected:
	class CDetailWindow* m_DetailWindow;

public:
	virtual bool Init();
	virtual void Render();
	virtual void SetComponentContents(class CSceneComponent* Component);
};

