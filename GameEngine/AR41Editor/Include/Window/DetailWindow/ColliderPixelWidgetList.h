#pragma once

#include "ComponentWidgetList.h"

class CColliderPixelWidgetList :
    public CComponentWidgetList
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CDetailWindow;

protected:
	CColliderPixelWidgetList();
	virtual ~CColliderPixelWidgetList();

private:
	class CEditorImage*		m_ColliderPixelImage;

	class CEditorComboBox*	m_ColorCollisionType;
	class CEditorComboBox*	m_AlphaCollisionType;

	class CEditorInput*		m_TypeColorR;
	class CEditorInput*		m_TypeColorG;
	class CEditorInput*		m_TypeColorB;
	class CEditorInput*		m_TypeColorA;

public:
	virtual bool Init();
	virtual void SetComponentContents(class CSceneComponent* Component);

private:
	void PixelImageLoadButtonClick();
	void PixelColorCollisionTypeSetButtonClick();
	void PixelAlphaCollisionTypeSetButtonClick();
	void PixelTypeColorSetButtonClick();
};

