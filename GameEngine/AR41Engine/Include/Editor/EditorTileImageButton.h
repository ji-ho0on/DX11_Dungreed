#pragma once

#include "EditorWidget.h"

class CEditorTileImageButton :
    public CEditorWidget
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;

	friend class CEditorGroup;

protected:
	CEditorTileImageButton();
	virtual ~CEditorTileImageButton();

private:
	std::function<void(int, int)>	m_ClickCallback;
	bool							m_Click;
	int								m_Index;

	CSharedPtr<class CTexture>		m_Texture;
	ImVec2							m_ImageStart;
	ImVec2							m_ImageEnd;
	ImVec4							m_BackgroundColor;
	int								m_ImageIndexX;
	int								m_ImageIndexY;

public:
	int GetIndex()	const
	{
		return m_Index;
	}

	int GetImageIndexX()	const
	{
		return m_ImageIndexX;
	}

	int GetImageIndexY()	const
	{
		return m_ImageIndexY;
	}

	CTexture* GetTexture()	const
	{
		return m_Texture;
	}

public:
	void SetIndex(int Index)
	{
		m_Index = Index;
	}

	void SetImageIndexX(int IndexX)
	{
		m_ImageIndexX = IndexX;
	}

	void SetImageIndexY(int IndexY)
	{
		m_ImageIndexY = IndexY;
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

	void SetBackgroundColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		m_BackgroundColor.x = r / 255.f;
		m_BackgroundColor.y = g / 255.f;
		m_BackgroundColor.z = b / 255.f;
		m_BackgroundColor.w = a / 255.f;
	}

	void SetTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);
	void SetTexture(const std::string& Name, std::vector<const TCHAR*> vecFileName, const std::string& PathName = TEXTURE_PATH);
	void SetTexture(const std::string& Name);
	void SetTextureFullPath(const std::string& Name, const TCHAR* FullPath);
	void SetTextureFullPath(const std::string& Name, std::vector<const TCHAR*> vecFullPath);
	void SetTexture(class CTexture* Texture);

public:
	virtual bool Init();
	virtual void Render();

public:
	template <typename T>
	void SetClickCallback(T* Obj, void(T::* Func)(int, int))
	{
		m_ClickCallback = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
	}
};

