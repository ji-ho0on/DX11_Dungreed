#include "EditorColorButton.h"

CEditorColorButton::CEditorColorButton()
{
}

CEditorColorButton::~CEditorColorButton()
{
}

bool CEditorColorButton::Init()
{
	return true;
}

void CEditorColorButton::Render()
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(m_Color.x * 0.7f, m_Color.y * 0.7f, m_Color.z * 0.7f, m_Color.w));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(m_Color.x * 0.8f, m_Color.y * 0.8f, m_Color.z * 0.8f, m_Color.w));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_Color);

	m_Click = ImGui::Button(m_NameUTF8.c_str(), m_Size);

	ImGui::PopStyleColor(3);

	if (m_Click && m_ClickCallback)
		m_ClickCallback();
}
