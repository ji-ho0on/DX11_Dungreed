#pragma once

#include "EditorButton.h"

class CEditorColorButton :
    public CEditorButton
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

protected:
	CEditorColorButton();
	virtual ~CEditorColorButton();

public:
	virtual bool Init();
	virtual void Render();
};

