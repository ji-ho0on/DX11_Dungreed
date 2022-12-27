#pragma once

#include "ComponentWidgetList.h"

class CTileMapComponentWidgetList :
    public CComponentWidgetList
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CDetailWindow;

protected:
	CTileMapComponentWidgetList();
	virtual ~CTileMapComponentWidgetList();

private:
	CSharedPtr<class CTileMapComponent>	m_TileMapComponent;

	class CEditorComboBox*				m_TileShapeCombo;
	class CEditorInput*					m_TileCountX;
	class CEditorInput*					m_TileCountY;
	class CEditorInput*					m_TileSizeX;
	class CEditorInput*					m_TileSizeY;


	class CEditorComboBox*				m_TileEditModeCombo;
	class CEditorComboBox*				m_TileOptionCombo;

	class CEditorTileImageButton*		m_SelectTileImage;

	class CEditorInput*					m_TileImageCountX;
	class CEditorInput*					m_TileImageCountY;
	class CEditorInput*					m_TileImageSizeX;
	class CEditorInput*					m_TileImageSizeY;
	class CEditorImage*					m_TileTexture;

public:
	void SetTileImageIndex(int IndexX, int IndexY);

public:
	virtual bool Init();
	virtual void Render();
	virtual void SetComponentContents(class CSceneComponent* Component);

private:
	void CreateTileButton();
	void SetTileImageButton();
	void LoadTileTextureButton();
};

