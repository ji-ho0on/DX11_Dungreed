#include "EditorRadioButton.h"

CEditorRadioButton::CEditorRadioButton()
{
}

CEditorRadioButton::~CEditorRadioButton()
{
}

bool CEditorRadioButton::Init()
{
	return true;
}

void CEditorRadioButton::Render()
{
	// 인자의 active 부분을 어떻게 해줘야할거 같음
	m_Click = ImGui::RadioButton(m_NameUTF8.c_str(), true);

	if (m_Click && m_ClickCallback)
		m_ClickCallback();
}
