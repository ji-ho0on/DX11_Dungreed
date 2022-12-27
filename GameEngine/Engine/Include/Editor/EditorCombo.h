#pragma once

#include "EditorWidget.h"

class CEditorCombo :
    public CEditorWidget
{
	friend class CEditorWindow;

protected:
	CEditorCombo();
	virtual ~CEditorCombo();

public:
	virtual bool Init();
	virtual void Render();
};

