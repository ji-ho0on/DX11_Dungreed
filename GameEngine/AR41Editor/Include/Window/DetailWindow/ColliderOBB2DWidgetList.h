#pragma once

#include "ComponentWidgetList.h"

class CColliderOBB2DWidgetList :
    public CComponentWidgetList
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CDetailWindow;

protected:
	CColliderOBB2DWidgetList();
	virtual ~CColliderOBB2DWidgetList();

private:
	class CEditorInput* m_BoxSizeX;
	class CEditorInput* m_BoxSizeY;

public:
	virtual bool Init();
	virtual void SetComponentContents(class CSceneComponent* Component);

private:
	void BoxSizeSetButtonClick();
};

