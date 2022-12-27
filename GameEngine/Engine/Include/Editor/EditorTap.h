#pragma once

#include "EditorWidget.h"
#include "EditorTapItem.h"

class CEditorTap :
    public CEditorWidget
{
	friend class CEditorWindow;

	friend class CEditorTapItem;
	
	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorGroup;

protected:
	CEditorTap();
	virtual ~CEditorTap();

protected:
	ImGuiTabBarFlags				m_Flag;
	std::vector<CEditorTapItem*>	m_vecItem;

public:
	void AddFlag(ImGuiTabBarFlags Flag);

public:
	virtual bool Init();
	virtual void Render();

public:
	void AddItem(const std::string& Item);
	CEditorTapItem* FindItem(const std::string& ItemName);

public:
	template <typename WidgetType>
	WidgetType* CreateWidget(const std::string& ItemName, const std::string& Name, float Width = 100.f, float Height = 100.f)
	{
		CEditorTapItem* Item = FindItem(ItemName);

		return Item->CreateWidget<WidgetType>(Name, Width, Height);
	}

	template <typename WidgetType>
	WidgetType* FindWidget(const std::string& ItemName,	const std::string& Name)
	{
		CEditorTapItem* Item = FindItem(ItemName);

		if (!Item)
			return nullptr;

		return Item->FindWidget<WidgetType>(Name);
	}
};

