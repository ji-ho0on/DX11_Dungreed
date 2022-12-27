#include "EditorTapItem.h"

CEditorTapItem::CEditorTapItem()
{
}

CEditorTapItem::~CEditorTapItem()
{
	size_t Size = m_vecWidget.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecWidget[i]);
	}
}

void CEditorTapItem::Render()
{
	if (ImGui::BeginTabItem(m_ItemUTF8.c_str()))
	{
		size_t	WidgetCount = m_vecWidget.size();

		for (size_t i = 0; i < WidgetCount; ++i)
		{
			m_vecWidget[i]->Render();
		}

		ImGui::EndTabItem();
	}
}