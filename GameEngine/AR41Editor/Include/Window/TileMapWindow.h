#pragma once

#include "Editor\EditorWindow.h"

class CTileMapWindow :
    public CEditorWindow
{
	friend class CEditorGUIManager;

protected:
	CTileMapWindow();
	virtual ~CTileMapWindow();

private:
	CSharedPtr<class CTexture>		m_TileTexture;
	int								m_CountX;
	int								m_CountY;
	Vector2							m_Size;

public:
	void SetAtlasImageCount(int CountX, int CountY)
	{
		m_CountX = CountX;
		m_CountY = CountY;
	}

	void SetAtlasImageSize(const Vector2& Size)
	{
		m_Size = Size;
	}

public:
	void SetTileTexture(int CountX, int CountY, const Vector2& Size, class CTexture* Texture);
	void SetTileTexture(int CountX, int CountY, const Vector2& Size, const std::string& Name, const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);
	void SetTileTextureFullPath(int CountX, int CountY, const Vector2& Size, const std::string& Name, const TCHAR* FullPath);
	void SetTileTexture(int CountX, int CountY, const std::string& Name, std::vector<const TCHAR*> vecFileName, const std::string& PathName = TEXTURE_PATH);
	void SetTileTextureFullPath(int CountX, int CountY, const std::string& Name, std::vector<const TCHAR*> vecFullPath);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void ImageButton(int IndexX, int IndexY);
};

