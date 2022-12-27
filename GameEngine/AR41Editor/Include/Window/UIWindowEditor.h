#pragma once

#include "Editor\EditorWindow.h"

class CUIWindowEditor :
    public CEditorWindow
{
	friend class CEditorGUIManager;

protected:
	CUIWindowEditor();
	virtual ~CUIWindowEditor();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

protected:
	class CScene*				m_Scene;

	CSharedPtr<class CUIWindow>	m_SelectUIWindow;

	class CEditorListBox*		m_UIWindowListBox;
	std::string					m_SelectUIWindowItem;

	class CEditorInput*			m_SelectUIWindowInput;

	class CEditorInput*			m_ZOrder;
	class CEditorInput*			m_Pos[2];
	class CEditorInput*			m_Size[2];

public:
	class CScene* GetScene()	const
	{
		return m_Scene;
	}

	class CUIWindow* GetSelectUIWindow()	const
	{
		return m_SelectUIWindow;
	}

public:
	void SetScene(CScene* Scene);

private:
	void SetUIWindow(class CUIWindow* UIWindow);
	void LoadUIList();

private:
	void UIListBoxClickCallback(int Index, const std::string& Item);
	void ZOrderCallback();
	void PosXCallback();
	void PosYCallback();
	void SizeXCallback();
	void SizeYCallback();
};

