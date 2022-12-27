#pragma once

#include "EditorWidget.h"

class CEditorNewLine :
    public CEditorWidget
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;

	friend class CEditorGroup;

protected:
	CEditorNewLine();
	virtual ~CEditorNewLine();

public:
	virtual bool Init();
	virtual void Render();
};

