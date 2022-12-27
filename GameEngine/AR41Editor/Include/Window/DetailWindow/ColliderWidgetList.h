#pragma once

#include "ComponentWidgetList.h"

class CColliderWidgetList :
    public CComponentWidgetList
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CDetailWindow;

protected:
	CColliderWidgetList();
	virtual ~CColliderWidgetList();

private:
	class CEditorComboBox* m_CollisionProfileCombo;

public:
	virtual bool Init();
	virtual void SetComponentContents(class CSceneComponent* Component);

private:
	void ProfileSetButtonClick();
};

