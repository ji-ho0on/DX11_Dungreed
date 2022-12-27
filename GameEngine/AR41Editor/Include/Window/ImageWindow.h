#pragma once

#include "Editor\EditorWindow.h"

class CImageWindow :
    public CEditorWindow
{
	friend class CEditorGUIManager;

protected:
	CImageWindow();
	virtual ~CImageWindow();

private:
	class CEditorListBox*	m_ImageList;
	std::string				m_SelectImageItem;

	class CEditorInput*		m_ImageSelectName;

	class CEditorImage*		m_SelectImage;

public:
	const std::string& GetSelectImageItem()	const
	{
		return m_SelectImageItem;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void LoadImageName();

private:
	void SetImage();
	void ImageClickCallback(int Index, const std::string& Item);
};

