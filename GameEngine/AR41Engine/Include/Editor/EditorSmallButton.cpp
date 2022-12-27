#include "EditorSmallButton.h"

CEditorSmallButton::CEditorSmallButton()
{
}

CEditorSmallButton::~CEditorSmallButton()
{
}

bool CEditorSmallButton::Init()
{
	return true;
}

void CEditorSmallButton::Render()
{
	ImGui::SmallButton(m_NameUTF8.c_str());

	if (m_Click && m_ClickCallback)
		m_ClickCallback();
}
