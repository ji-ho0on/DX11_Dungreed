#pragma once

#include "UIWidgetList.h"

class CUIImageWidgetList :
    public CUIWidgetList
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CUIWidgetEditor;

protected:
	CUIImageWidgetList();
	virtual ~CUIImageWidgetList();

private:
	class CEditorImage*		m_Image;
	class CEditorInput*		m_ImageTint[4];
	class CEditorInput*		m_ImagePlayTime;
	class CEditorInput*		m_ImagePlayScale;
	class CEditorCheckBox*	m_ImageLoop;
	class CEditorCheckBox*	m_ImageReverse;

public:
	virtual bool Init();
	virtual void SetUIWidgetContents(class CUIWidget* UIWidget);

private:
	void ImageSetButton();
	void ImageTintRCallback();
	void ImageTintGCallback();
	void ImageTintBCallback();
	void ImageTintACallback();;
	void SetImagePlayTime();
	void SetImagePlayScale();
	void SetImageLoop();
	void SetImageReverse();
};

