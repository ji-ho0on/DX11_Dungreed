#include "EditorImageButton.h"
#include "../Resource/Texture/Texture.h"
#include "../Resource/ResourceManager.h"

CEditorImageButton::CEditorImageButton() :
	m_ImageStart{},
	m_ImageEnd{},
	m_BackgroundColor{0.f, 0.f, 0.f, 1.f},
	m_ImageIndex(0)
{
}

CEditorImageButton::~CEditorImageButton()
{
	if (m_Texture)
		CResourceManager::GetInst()->ReleaseTexture(m_Texture->GetName());
}

void CEditorImageButton::SetTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName);

	m_Texture = CResourceManager::GetInst()->FindTexture(Name);

	if (!m_Texture)
		m_Texture = CResourceManager::GetInst()->FindTexture("DefaultUI");

	SetImageEnd((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
}

void CEditorImageButton::SetTexture(const std::string& Name, std::vector<const TCHAR*> vecFileName, const std::string& PathName)
{
	CResourceManager::GetInst()->LoadTexture(Name, vecFileName, PathName);

	m_Texture = CResourceManager::GetInst()->FindTexture(Name);

	if (!m_Texture)
		m_Texture = CResourceManager::GetInst()->FindTexture("DefaultUI");

	SetImageEnd((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
}

void CEditorImageButton::SetTexture(const std::string& Name)
{
	m_Texture = CResourceManager::GetInst()->FindTexture(Name);

	if (!m_Texture)
		m_Texture = CResourceManager::GetInst()->FindTexture("DefaultUI");

	SetImageEnd((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
}

void CEditorImageButton::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath);

	m_Texture = CResourceManager::GetInst()->FindTexture(Name);

	if (!m_Texture)
		m_Texture = CResourceManager::GetInst()->FindTexture("DefaultUI");

	SetImageEnd((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
}

void CEditorImageButton::SetTextureFullPath(const std::string& Name, std::vector<const TCHAR*> vecFullPath)
{
	CResourceManager::GetInst()->LoadTextureFullPath(Name, vecFullPath);

	m_Texture = CResourceManager::GetInst()->FindTexture(Name);

	if (!m_Texture)
		m_Texture = CResourceManager::GetInst()->FindTexture("DefaultUI");

	SetImageEnd((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
}

void CEditorImageButton::SetTexture(CTexture* Texture)
{
	m_Texture = Texture;

	if (!m_Texture)
		m_Texture = CResourceManager::GetInst()->FindTexture("DefaultUI");

	SetImageEnd((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
}

bool CEditorImageButton::Init()
{
	SetTexture("DefaultUI", TEXT("Example/DefaultUI.png"));

	return true;
}

void CEditorImageButton::Render()
{
	if (m_Texture)
	{
		// Atlas Image�� ���
		if (m_Texture->GetImageType() == EImageType::Atlas)
		{
			unsigned int Width = m_Texture->GetWidth();
			unsigned int Height = m_Texture->GetHeight();

			ImVec2 StartUV = ImVec2(m_ImageStart.x / Width, m_ImageStart.y / Height);
			ImVec2 EndUV = ImVec2(m_ImageEnd.x / Width, m_ImageEnd.y / Height);

			// Image�� SRV(ShaderResourceView)�� �־��ְ� ������, UV, Color�� �����Ͽ� ����Ѵ�.
			m_Click = ImGui::ImageButton(m_NameUTF8.c_str(), m_Texture->GetResource(), m_Size, StartUV, EndUV, m_BackgroundColor, m_Color);
		}

		// Frame Image�� ���
		else if (m_Texture->GetImageType() == EImageType::Frame)
		{
			unsigned int Width = m_Texture->GetWidth(m_ImageIndex);
			unsigned int Height = m_Texture->GetHeight(m_ImageIndex);

			ImVec2 StartUV = ImVec2(m_ImageStart.x / Width, m_ImageStart.y / Height);
			ImVec2 EndUV = ImVec2(m_ImageEnd.x / Width, m_ImageEnd.y / Height);

			// Image�� SRV(ShaderResourceView)�� �־��ְ� ������, UV, Color�� �����Ͽ� ����Ѵ�.
			m_Click = ImGui::ImageButton(m_NameUTF8.c_str(), m_Texture->GetResource(m_ImageIndex), m_Size, StartUV, EndUV, m_BackgroundColor, m_Color);
		}

		// Array Image�� ���
		else
		{

		}

		if (m_Click && m_ClickCallback)
			m_ClickCallback();
	}
}