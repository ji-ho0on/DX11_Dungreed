#pragma once

#include "ComponentWidgetList.h"

class CColliderLine2DWidgetList :
    public CComponentWidgetList
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CDetailWindow;

protected:
	CColliderLine2DWidgetList();
	virtual ~CColliderLine2DWidgetList();

private:
	class CEditorInput* m_Point1X;
	class CEditorInput* m_Point1Y;
	class CEditorInput* m_Point2X;
	class CEditorInput* m_Point2Y;

public:
	virtual bool Init();
	virtual void SetComponentContents(class CSceneComponent* Component);

private:
	void Point1SetButtonClick();
	void Point2SetButtonClick();
};

