#pragma once

#include "EditorWidget.h"

class CEditorCheckBox :
    public CEditorWidget
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;

	friend class CEditorGroup;

protected:
	CEditorCheckBox();
	virtual ~CEditorCheckBox();

protected:
	bool					m_Click;
	bool					m_Check;


	std::function<void()>	m_CheckCallback;

public:
	void SetCheck(bool Check)
	{
		m_Check = Check;
	}

	bool GetCheck()	const
	{
		return m_Check;
	}

public:
	virtual bool Init();
	virtual void Render();

public:
	template <typename T>
	void SetCheckCallback(T* Obj, void(T::* Func)())
	{
		m_CheckCallback = std::bind(Func, Obj);
	}
};

