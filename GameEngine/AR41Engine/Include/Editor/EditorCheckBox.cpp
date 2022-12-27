#include "EditorCheckBox.h"

CEditorCheckBox::CEditorCheckBox() :
	m_Check(false),
	m_Click(false)
{
}

CEditorCheckBox::~CEditorCheckBox()
{
}

bool CEditorCheckBox::Init()
{
	return true;
}

void CEditorCheckBox::Render()
{
	m_Click = ImGui::Checkbox(m_NameUTF8.c_str(), &m_Check);

	if (m_Click && m_CheckCallback)
		m_CheckCallback();
}
