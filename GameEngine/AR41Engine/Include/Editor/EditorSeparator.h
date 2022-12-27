#pragma once

#include "EditorWidget.h"

class CEditorSeparator :
    public CEditorWidget
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;

	friend class CEditorGroup;

protected:
	CEditorSeparator();
	virtual ~CEditorSeparator();

public:
	virtual bool Init();
	virtual void Render();
};

