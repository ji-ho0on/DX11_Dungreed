#pragma once

#include "EditorWidget.h"

class CEditorSameLine :
	public CEditorWidget
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;

	friend class CEditorGroup;

protected:
	CEditorSameLine();
	virtual ~CEditorSameLine();

private:
	float	m_OffsetX;	// Offset은 현재 라인의 가장 왼쪽으로부터 어느정도의 위치에 표현할 것인지를 나타낸다.

	float	m_Spacing;	// 왼쪽의 위젯으로부터 얼마나 떨어질지를 결정한다.

public:
	void SetOffsetX(float x)
	{
		m_OffsetX = x;
	}

	void SetSpacing(float Spacing)
	{
		m_Spacing = Spacing;
	}

public:
	virtual bool Init();
	virtual void Render();
};

