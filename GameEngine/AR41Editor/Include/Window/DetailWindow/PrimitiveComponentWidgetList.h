#pragma once

#include "ComponentWidgetList.h"

class CPrimitiveComponentWidgetList :
    public CComponentWidgetList
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CDetailWindow;

protected:
	CPrimitiveComponentWidgetList();
	virtual ~CPrimitiveComponentWidgetList();

private:
	class CEditorImage* m_PrimitiveImage;

	class CEditorInput* m_BaseColorR;
	class CEditorInput* m_BaseColorG;
	class CEditorInput* m_BaseColorB;
	class CEditorInput* m_BaseColorA;

	class CEditorInput* m_AmbientColorR;
	class CEditorInput* m_AmbientColorG;
	class CEditorInput* m_AmbientColorB;
	class CEditorInput* m_AmbientColorA;

	class CEditorInput* m_SpecularColorR;
	class CEditorInput* m_SpecularColorG;
	class CEditorInput* m_SpecularColorB;
	class CEditorInput* m_SpecularColorA;

	class CEditorInput* m_EmissiveColorR;
	class CEditorInput* m_EmissiveColorG;
	class CEditorInput* m_EmissiveColorB;
	class CEditorInput* m_EmissiveColorA;

	class CEditorInput* m_Opacity;

public:
	virtual bool Init();
	virtual void SetComponentContents(class CSceneComponent* Component);

private:
	void PrimitiveImageLoadButtonClick();
	void PrimitiveBaseColorSetButtonClick();
	void PrimitiveAmbientColorSetButtonClick();
	void PrimitiveSpecularColorSetButtonClick();
	void PrimitiveEmissiveColorSetButtonClick();
	void PrimitiveOpacitySetButtonClick();
};

