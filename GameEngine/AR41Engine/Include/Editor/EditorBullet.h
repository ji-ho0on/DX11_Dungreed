#pragma once

#include "EditorWidget.h"

class CEditorBullet :
    public CEditorWidget
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;

	friend class CEditorGroup;

protected:
	CEditorBullet();
	virtual ~CEditorBullet();

public:
	virtual bool Init();
	virtual void Render();
};

