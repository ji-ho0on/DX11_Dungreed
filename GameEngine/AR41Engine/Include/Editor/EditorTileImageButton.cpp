#include "EditorTileImageButton.h"
#include "../Resource/Texture/Texture.h"
#include "../Resource/ResourceManager.h"

CEditorTileImageButton::CEditorTileImageButton() :
	m_ImageStart{},
	m_ImageEnd{},
	m_BackgroundColor{ 0.f, 0.f, 0.f, 1.f },
	m_ImageIndexX(0),
	m_ImageIndexY(0)
{
}

CEditorTileImageButton::~CEditorTileImageButton()
{
	if (m_Texture)
		CResourceManager::GetInst()->ReleaseTexture(m_Texture->GetName());
}

void CEditorTileImageButton::SetTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName);

	m_Texture = CResourceManager::GetInst()->FindTexture(Name);

	if (!m_Texture)
		m_Texture = CResourceManager::GetInst()->FindTexture("DefaultUI");

	SetImageEnd((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
}

void CEditorTileImageButton::SetTexture(const std::string& Name, std::vector<const TCHAR*> vecFileName, const std::string& PathName)
{
	CResourceManager::GetInst()->LoadTexture(Name, vecFileName, PathName);

	m_Texture = CResourceManager::GetInst()->FindTexture(Name);

	if (!m_Texture)
		m_Texture = CResourceManager::GetInst()->FindTexture("DefaultUI");

	SetImageEnd((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
}

void CEditorTileImageButton::SetTexture(const std::string& Name)
{
	m_Texture = CResourceManager::GetInst()->FindTexture(Name);

	if (!m_Texture)
		m_Texture = CResourceManager::GetInst()->FindTexture("DefaultUI");

	SetImageEnd((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
}

void CEditorTileImageButton::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath);

	m_Texture = CResourceManager::GetInst()->FindTexture(Name);

	if (!m_Texture)
		m_Texture = CResourceManager::GetInst()->FindTexture("DefaultUI");

	SetImageEnd((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
}

void CEditorTileImageButton::SetTextureFullPath(const std::string& Name, std::vector<const TCHAR*> vecFullPath)
{
	CResourceManager::GetInst()->LoadTextureFullPath(Name, vecFullPath);

	m_Texture = CResourceManager::GetInst()->FindTexture(Name);

	if (!m_Texture)
		m_Texture = CResourceManager::GetInst()->FindTexture("DefaultUI");

	SetImageEnd((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
}

void CEditorTileImageButton::SetTexture(CTexture* Texture)
{
	m_Texture = Texture;

	if (!m_Texture)
		m_Texture = CResourceManager::GetInst()->FindTexture("DefaultUI");

	SetImageEnd((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
}

bool CEditorTileImageButton::Init()
{
	SetTexture("DefaultUI", TEXT("Example/DefaultUI.png"));

	return true;
}

void CEditorTileImageButton::Render()
{
	if (m_Texture)
	{
		// Atlas Image일 경우
		if (m_Texture->GetImageType() == EImageType::Atlas)
		{
			unsigned int Width = m_Texture->GetWidth();
			unsigned int Height = m_Texture->GetHeight();

			ImVec2 StartUV = ImVec2(m_ImageStart.x / Width, m_ImageStart.y / Height);
			ImVec2 EndUV = ImVec2(m_ImageEnd.x / Width, m_ImageEnd.y / Height);

			// Image의 SRV(ShaderResourceView)를 넣어주고 사이즈, UV, Color를 지정하여 출력한다.
			m_Click = ImGui::ImageButton(m_NameUTF8.c_str(), m_Texture->GetResource(), m_Size, StartUV, EndUV, m_BackgroundColor, m_Color);
		}

		// Array Image일 경우
		else// if (m_Texture->GetImageType() == EImageType::Frame)
		{
			unsigned int Width = m_Texture->GetWidth(m_Index);
			unsigned int Height = m_Texture->GetHeight(m_Index);

			ImVec2 StartUV = ImVec2(m_ImageStart.x / Width, m_ImageStart.y / Height);
			ImVec2 EndUV = ImVec2(m_ImageEnd.x / Width, m_ImageEnd.y / Height);

			// Image의 SRV(ShaderResourceView)를 넣어주고 사이즈, UV, Color를 지정하여 출력한다.
			m_Click = ImGui::ImageButton(m_NameUTF8.c_str(), m_Texture->GetResource(m_Index), m_Size, StartUV, EndUV, m_BackgroundColor, m_Color);
		}

		if (m_Click && m_ClickCallback)
			m_ClickCallback(m_ImageIndexX, m_ImageIndexY);
	}
}