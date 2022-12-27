#pragma once

#include "Editor\EditorWindow.h"

class CDetailWindow :
	public CEditorWindow
{
	friend class CEditorGUIManager;

protected:
	CDetailWindow();
	virtual ~CDetailWindow();

protected:
	std::vector<class CComponentWidgetList*>	m_vecComponentWidgetList;
	CSharedPtr<class CSceneComponent>			m_SelectComponent;

public:
	class CSceneComponent* GetSelectComponent()	const
	{
		return m_SelectComponent;
	}

	class CComponentWidgetList* GetComponentWidgetList(ESceneComponentType Type);

public:
	void SetSelectComponent(class CSceneComponent* Component);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void CreateEditorWidgetList(ESceneComponentType Type);
	void ChangeWidget(class CSceneComponent* Component);
};

