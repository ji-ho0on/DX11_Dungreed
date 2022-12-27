#pragma once

#include "Editor\EditorWindow.h"

class CSceneWindow :
	public CEditorWindow
{
	friend class CEditorGUIManager;

protected:
	CSceneWindow();
	virtual ~CSceneWindow();

private:
	class CEditorInput*		m_SceneSaveName;


	class CEditorListBox*	m_SceneList;
	std::string				m_SelectSceneItem;

	class CEditorInput*		m_SelectSceneName;


	class CEditorInput*		m_CurrentSceneInfoName;

	class CEditorListBox*	m_SceneInfoList;
	std::string				m_SelectSceneInfoItem;

	class CEditorInput*		m_SelectSceneInfoName;

public:
	const std::string& GetSelectSceneItem()	const
	{
		return m_SelectSceneItem;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void SceneSave();
	void SceneChange();

	void PlayButton();
	void StopButton();

	void SceneClickCallback(int Index, const std::string& Item);
	void LoadSceneDirectory();

	void CreateSection2D();
	void CreateSection3D();

	void SceneInfoClickCallback(int Index, const std::string& Item);
	void LoadSceneInfoDirectory();
	void SceneCreate();
};

