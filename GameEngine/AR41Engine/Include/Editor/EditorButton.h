#pragma once

#include "EditorWidget.h"

class CEditorButton :
	public CEditorWidget
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	
	friend class CEditorGroup;

protected:
	CEditorButton();
	virtual ~CEditorButton();

protected:
	std::function<void()>	m_ClickCallback;
	bool					m_Click;

public:
	virtual bool Init();
	virtual void Render();

public:
	template <typename T>
	void SetClickCallback(T* Obj, void(T::* Func)())
	{
		m_ClickCallback = std::bind(Func, Obj);
	}
};

