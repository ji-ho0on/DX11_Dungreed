#pragma once

#include "EditorWidget.h"

class CEditorLabel :
	public CEditorWidget
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;

	friend class CEditorGroup;

protected:
	CEditorLabel();
	virtual ~CEditorLabel();

private:
	ImVec2	m_Align;	// Align을 조절하여 Label에 표시되는 이름의 위치를 조절할 수 있음.

public:
	void SetAlign(float x, float y)
	{
		m_Align.x = x;
		m_Align.y = y;
	}

public:
	virtual bool Init();
	virtual void Render();
};

