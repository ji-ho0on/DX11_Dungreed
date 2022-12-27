#include "EditorBullet.h"

CEditorBullet::CEditorBullet()
{
}

CEditorBullet::~CEditorBullet()
{
}

bool CEditorBullet::Init()
{
	return true;
}

void CEditorBullet::Render()
{
	ImGui::BulletText(m_NameUTF8.c_str());
}
