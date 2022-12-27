#pragma once

#include "EditorButton.h"

class CEditorRadioButton :
    public CEditorButton
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

protected:
	CEditorRadioButton();
	virtual ~CEditorRadioButton();

public:
	virtual bool Init();
	virtual void Render();
};

