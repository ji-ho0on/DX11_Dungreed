#pragma once

#include "ComponentWidgetList.h"

class CCameraComponentWidgetList :
    public CComponentWidgetList
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CDetailWindow;

protected:
	CCameraComponentWidgetList();
	virtual ~CCameraComponentWidgetList();

private:
	class CEditorComboBox*	m_CameraType;
	class CEditorInput*		m_CameraViewDistance;

public:
	virtual bool Init();
	virtual void SetComponentContents(class CSceneComponent* Component);

private:
	void CameraTypeSetButtonClick();
	void CameraViewDistanceSetButtonClick();
};

