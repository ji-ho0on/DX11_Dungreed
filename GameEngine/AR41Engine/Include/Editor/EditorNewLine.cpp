#include "EditorNewLine.h"

CEditorNewLine::CEditorNewLine()
{
}

CEditorNewLine::~CEditorNewLine()
{
}

bool CEditorNewLine::Init()
{
	return true;
}

void CEditorNewLine::Render()
{
	ImGui::NewLine();
}
