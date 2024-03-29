#pragma once

#include "EditorWidget.h"

class CEditorImage :
	public CEditorWidget
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;

	friend class CEditorGroup;

protected:
	CEditorImage();
	virtual ~CEditorImage();

private:
	CSharedPtr<class CTexture>	m_Texture;
	ImVec2						m_ImageStart;
	ImVec2						m_ImageEnd;
	ImVec4						m_BorderColor;
	int							m_ImageIndex;

public:
	CTexture* GetTexture()	const
	{
		return m_Texture;
	}

	int GetImageIndex()	const
	{
		return m_ImageIndex;
	}

public:
	void SetImageIndex(int Index)
	{
		m_ImageIndex = Index;
	}

	void SetImageStart(float x, float y)
	{
		m_ImageStart.x = x;
		m_ImageStart.y = y;
	}

	void SetImageEnd(float x, float y)
	{
		m_ImageEnd.x = x;
		m_ImageEnd.y = y;
	}

	void SetBorderColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		m_BorderColor.x = r / 255.f;
		m_BorderColor.y = g / 255.f;
		m_BorderColor.z = b / 255.f;
		m_BorderColor.w = a / 255.f;
	}

	void SetTexture(const std::string& Name);
	void SetTexture(class CTexture* Texture);
	void SetTexture(const std::string& Name, const TCHAR* FileName,	const std::string& PathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& Name, const TCHAR* FullPath);
	void SetTexture(const std::string& Name, std::vector<const TCHAR*> vecFileName, const std::string& PathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& Name, std::vector<const TCHAR*> vecFullPath);
	void SetTextureArray(const std::string& Name, std::vector<const TCHAR*> vecFileName, const std::string& PathName = TEXTURE_PATH);
	void SetTextureArrayFullPath(const std::string& Name, std::vector<const TCHAR*> vecFullPath);

public:
	virtual bool Init();
	virtual void Render();
};

