#pragma once

#include "ComponentWidgetList.h"

class CColliderSphere2DWidgetList :
    public CComponentWidgetList
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CDetailWindow;

protected:
	CColliderSphere2DWidgetList();
	virtual ~CColliderSphere2DWidgetList();

private:
	class CEditorInput* m_Radius;

public:
	virtual bool Init();
	virtual void SetComponentContents(class CSceneComponent* Component);

private:
	void RadiusSetButtonClick();
};

