#include "EditorSeparator.h"

CEditorSeparator::CEditorSeparator()
{
}

CEditorSeparator::~CEditorSeparator()
{
}

bool CEditorSeparator::Init()
{
	return true;
}

void CEditorSeparator::Render()
{
	ImGui::Separator();
}
