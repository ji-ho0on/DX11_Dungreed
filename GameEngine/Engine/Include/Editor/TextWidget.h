#pragma once

#include "EditorWidget.h"

class CTextWidget :
    public CEditorWidget
{
	friend class CEditorWindow;

protected:
	CTextWidget();
	virtual ~CTextWidget();

public:
	virtual bool Init();
	virtual void Render();
};

