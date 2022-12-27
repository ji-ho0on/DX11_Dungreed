#pragma once

#include "EditorButton.h"

class CEditorSmallButton :
    public CEditorButton
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

protected:
	CEditorSmallButton();
	virtual ~CEditorSmallButton();

public:
	virtual bool Init();
	virtual void Render();
};

