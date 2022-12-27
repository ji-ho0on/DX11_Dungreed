#pragma once

#include "UIWidgetList.h"

class CUINumberWidgetList :
    public CUIWidgetList
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CUIWidgetEditor;

protected:
	CUINumberWidgetList();
	virtual ~CUINumberWidgetList();

private:
	class CEditorInput*		m_Number;
	class CEditorImage*		m_NumberImage;
	class CEditorInput*		m_NumberImageTint[4];
	class CEditorInput*		m_NumberImagePlayTime;
	class CEditorInput*		m_NumberImagePlayScale;
	class CEditorCheckBox*	m_NumberImageLoop;
	class CEditorCheckBox*	m_NumberImageReverse;

public:
	virtual bool Init();
	virtual void SetUIWidgetContents(class CUIWidget* UIWidget);

private:
	void NumberSetButton();
	void NumberImageSetButton();
	void NumberImageTintRCallback();
	void NumberImageTintGCallback();
	void NumberImageTintBCallback();
	void NumberImageTintACallback();;
	void SetNumberImagePlayTime();
	void SetNumberImagePlayScale();
	void SetNumberImageLoop();
	void SetNumberImageReverse();
};

