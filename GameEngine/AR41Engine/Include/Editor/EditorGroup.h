#pragma once

#include "EditorWidget.h"

class CEditorGroup :
    public CEditorWidget
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;

protected:
	CEditorGroup();
	virtual ~CEditorGroup();

protected:
	std::vector<CEditorWidget*>	m_vecWidget;

public:
	virtual bool Init();
	virtual void Render();

public:
	template <typename WidgetType>
	WidgetType* CreateWidget(const std::string& Name, float Width = 100.f, float Height = 100.f)
	{
		WidgetType* Widget = new WidgetType;

		Widget->SetName(Name);
		Widget->SetSize(Width, Height);

		if (!Widget->Init())
		{
			SAFE_DELETE(Widget);
			return nullptr;
		}

		m_vecWidget.push_back(Widget);

		return Widget;
	}

	template <typename WidgetType>
	WidgetType* FindWidget(const std::string& Name)
	{
		size_t	Size = m_vecWidget.size();

		for (size_t i = 0; i < Size; ++i)
		{
			if (m_vecWidget[i]->GetName() == Name)
				return (WidgetType*)m_vecWidget[i];
		}

		return nullptr;
	}
};

