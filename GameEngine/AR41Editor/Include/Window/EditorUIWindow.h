#pragma once

#include "Editor\EditorWindow.h"

class CEditorUIWindow :
    public CEditorWindow
{
	friend class CEditorGUIManager;

protected:
	CEditorUIWindow();
	virtual ~CEditorUIWindow();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

protected:
	class CScene*			m_Scene;

	class CEditorListBox*	m_UIWindowListBox;
	std::string				m_SelectUIWindowItem;

	class CEditorInput*		m_SelectUIWindowNameInput;

public:
	void SetScene(CScene* Scene);

private:
	void LoadUIDirectory();

private:
	void UIListBoxClickCallback(int Index, const std::string& Item);
	void UIButton();
};

