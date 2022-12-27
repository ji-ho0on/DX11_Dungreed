#pragma once

#include "Editor\EditorWindow.h"

class CUIWidgetEditor :
    public CEditorWindow
{
	friend class CEditorGUIManager;

protected:
	CUIWidgetEditor();
	virtual ~CUIWidgetEditor();

private:
	CSharedPtr<class CUIWindow>			m_SelectUIWindow;

	std::vector<class CUIWidgetList*>	m_vecUIWidgetList;
	CSharedPtr<class CUIWidget>			m_SelectUIWidget;

public:
	class CUIWindow* GetSelectUIWindow()	const
	{
		return m_SelectUIWindow;
	}

	class CUIWidget* GetSelectUIWidget()	const
	{
		return m_SelectUIWidget;
	}

	class CUIWidgetList* GetUIWidgetList(EUIWidgetType Type);

public:
	void SetSelectUIWindow(class CUIWindow* UIWindow);
	void SetSelectUIWidget(class CUIWidget* UIWidget);

private:
	void CreateEditorWidgetList(EUIWidgetType Type);
	void ChangeWidget(class CUIWidget* UIWidget);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
};

