#include "EditorTap.h"

CEditorTap::CEditorTap() :
	m_Flag(ImGuiTabBarFlags_None)
{
}

CEditorTap::~CEditorTap()
{
	size_t Size = m_vecItem.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecItem[i]);
	}
}

void CEditorTap::AddFlag(ImGuiTabBarFlags Flag)
{
	m_Flag |= Flag;
	/*
	ImGuiTabBarFlags_None                           = 0,
	ImGuiTabBarFlags_Reorderable                    = 1 << 0,   // Allow manually dragging tabs to re-order them + New tabs are appended at the end of list
	ImGuiTabBarFlags_AutoSelectNewTabs              = 1 << 1,   // Automatically select new tabs when they appear
	ImGuiTabBarFlags_TabListPopupButton             = 1 << 2,   // Disable buttons to open the tab list popup
	ImGuiTabBarFlags_NoCloseWithMiddleMouseButton   = 1 << 3,   // Disable behavior of closing tabs (that are submitted with p_open != NULL) with middle mouse button. You can still repro this behavior on user's side with if (IsItemHovered() && IsMouseClicked(2)) *p_open = false.
	ImGuiTabBarFlags_NoTabListScrollingButtons      = 1 << 4,   // Disable scrolling buttons (apply when fitting policy is ImGuiTabBarFlags_FittingPolicyScroll)
	ImGuiTabBarFlags_NoTooltip                      = 1 << 5,   // Disable tooltips when hovering a tab
	ImGuiTabBarFlags_FittingPolicyResizeDown        = 1 << 6,   // Resize tabs when they don't fit
	ImGuiTabBarFlags_FittingPolicyScroll            = 1 << 7,   // Add scroll buttons when tabs don't fit
	ImGuiTabBarFlags_FittingPolicyMask_             = ImGuiTabBarFlags_FittingPolicyResizeDown | ImGuiTabBarFlags_FittingPolicyScroll,
	ImGuiTabBarFlags_FittingPolicyDefault_          = ImGuiTabBarFlags_FittingPolicyResizeDown,
	*/
}

bool CEditorTap::Init()
{
	return true;
}

void CEditorTap::Render()
{
	if (ImGui::BeginTabBar(m_NameUTF8.c_str(), m_Flag))
	{
		size_t Size = m_vecItem.size();

		for (size_t i = 0; i < Size; ++i)
		{
			m_vecItem[i]->Render();
		}

		ImGui::EndTabBar();
	}
}

void CEditorTap::AddItem(const std::string& Item)
{
	CEditorTapItem* TapItem = new CEditorTapItem;

	TapItem->m_Item = Item;

	TCHAR	wText[256] = {};

	int Length = (int)MultiByteToWideChar(CP_ACP, 0, Item.c_str(), -1, nullptr, 0);

	MultiByteToWideChar(CP_ACP, 0, Item.c_str(), -1, wText, Length);

	char	TextUTF8[256] = {};

	Length = WideCharToMultiByte(CP_UTF8, 0, wText, -1, nullptr, 0, nullptr, nullptr);

	WideCharToMultiByte(CP_UTF8, 0, wText, -1, TextUTF8, Length, nullptr, nullptr);

	TapItem->m_ItemUTF8 = TextUTF8;

	m_vecItem.push_back(TapItem);
}

CEditorTapItem* CEditorTap::FindItem(const std::string& ItemName)
{
	auto iter = m_vecItem.begin();
	auto iterEnd = m_vecItem.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->m_Item == ItemName)
			return *iter;
	}

	return nullptr;
}