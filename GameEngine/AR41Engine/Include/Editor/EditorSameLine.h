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
	float	m_OffsetX;	// Offset�� ���� ������ ���� �������κ��� ��������� ��ġ�� ǥ���� �������� ��Ÿ����.

	float	m_Spacing;	// ������ �������κ��� �󸶳� ���������� �����Ѵ�.

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

