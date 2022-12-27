#pragma once

#include "ComponentWidgetList.h"

class CTargetArmWidgetList :
    public CComponentWidgetList
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CDetailWindow;

protected:
	CTargetArmWidgetList();
	virtual ~CTargetArmWidgetList();

private:
	class CEditorInput* m_TargetOffsetX;
	class CEditorInput* m_TargetOffsetY;
	class CEditorInput* m_TargetOffsetZ;

	class CEditorInput* m_TargetDistance;

public:
	virtual bool Init();
	virtual void SetComponentContents(class CSceneComponent* Component);

private:
	void TargetArmOffsetSetButtonClick();
	void TargetArmDistanceSetButtonClick();
};

