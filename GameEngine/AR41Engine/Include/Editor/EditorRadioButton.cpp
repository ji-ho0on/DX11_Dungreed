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
	// ������ active �κ��� ��� ������Ұ� ����
	m_Click = ImGui::RadioButton(m_NameUTF8.c_str(), true);

	if (m_Click && m_ClickCallback)
		m_ClickCallback();
}
