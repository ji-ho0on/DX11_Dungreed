#include "PrimitiveComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Render/RenderManager.h"
#include "../Resource/Material/Material.h"

CPrimitiveComponent::CPrimitiveComponent()
{
	SetTypeID<CPrimitiveComponent>();

	m_ComponentTypeName = "PrimitiveComponent";
}

CPrimitiveComponent::CPrimitiveComponent(const CPrimitiveComponent& component) :
	CSceneComponent(component)
{
	m_Mesh = component.m_Mesh;

	size_t	Size = component.m_vecMaterial.size();

	for (size_t i = 0; i < Size; ++i)
	{
		CMaterial* Material = component.m_vecMaterial[i]->Clone();

		m_vecMaterial.push_back(Material);
	}
}

CPrimitiveComponent::~CPrimitiveComponent()
{
}

void CPrimitiveComponent::SetMesh(const std::string& Name)
{
	if (m_Scene)
		m_Mesh = m_Scene->GetResource()->FindMesh(Name);

	else
		m_Mesh = CResourceManager::GetInst()->FindMesh(Name);

	if (m_Mesh)
		SetMeshSize(m_Mesh->GetMeshSize());

	m_vecMaterial.clear();

	int SlotCount = m_Mesh->GetSlotCount();

	for (int i = 0; i < SlotCount; ++i)
	{
		CMaterial* Material = m_Mesh->GetMaterial(i);

		m_vecMaterial.push_back(Material->Clone());
	}
}

void CPrimitiveComponent::SetMesh(CMesh* Mesh)
{
	m_Mesh = Mesh;

	if (m_Mesh)
		SetMeshSize(m_Mesh->GetMeshSize());

	int SlotCount = m_Mesh->GetSlotCount();

	for (int i = 0; i < SlotCount; ++i)
	{
		CMaterial* Material = m_Mesh->GetMaterial(i);

		m_vecMaterial.push_back(Material->Clone());
	}
}

void CPrimitiveComponent::SetMaterial(int Slot, const std::string& Name)
{
	CMaterial* Material = nullptr;

	if (m_Scene)
		Material = m_Scene->GetResource()->FindMaterial(Name);

	else
		Material = CResourceManager::GetInst()->FindMaterial(Name);

	m_vecMaterial[Slot] = Material->Clone();
}

void CPrimitiveComponent::SetMaterial(int Slot, CMaterial* Material)
{
	m_vecMaterial[Slot] = Material->Clone();
}

void CPrimitiveComponent::AddMaterial(const std::string& Name)
{
	CMaterial* Material = nullptr;

	if (m_Scene)
		Material = m_Scene->GetResource()->FindMaterial(Name);

	else
		Material = CResourceManager::GetInst()->FindMaterial(Name);

	m_vecMaterial.push_back(Material->Clone());
}

void CPrimitiveComponent::AddMaterial(CMaterial* Material)
{
	m_vecMaterial.push_back(Material->Clone());
}

void CPrimitiveComponent::ClearMaterial()
{
	m_vecMaterial.clear();
}

bool CPrimitiveComponent::SetTexture(CTexture* Texture)
{
	if (m_vecMaterial.empty())
		return false;

	m_vecMaterial[0]->SetTexture(0, 0, (int)EShaderBufferType::Pixel, Texture->GetName(), Texture);

	return true;
}

bool CPrimitiveComponent::SetTexture(const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	if (m_vecMaterial.empty())
		return false;

	m_vecMaterial[0]->SetTexture(0, 0, (int)EShaderBufferType::Pixel, Name, FileName, PathName);

	return true;
}

bool CPrimitiveComponent::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	if (m_vecMaterial.empty())
		return false;

	m_vecMaterial[0]->SetTextureFullPath(0, 0, (int)EShaderBufferType::Pixel, Name, FullPath);

	return true;
}

bool CPrimitiveComponent::SetTexture(const std::string& Name, const std::vector<const TCHAR*>& vecFileName, const std::string& PathName)
{
	if (m_vecMaterial.empty())
		return false;

	m_vecMaterial[0]->SetTexture(0, 0, (int)EShaderBufferType::Pixel, Name, vecFileName, PathName);

	return true;
}

bool CPrimitiveComponent::SetTextureFullPath(const std::string& Name, const std::vector<const TCHAR*>& vecFullPath)
{
	if (m_vecMaterial.empty())
		return false;

	m_vecMaterial[0]->SetTextureFullPath(0, 0, (int)EShaderBufferType::Pixel, Name, vecFullPath);

	return true;
}

bool CPrimitiveComponent::SetTextureArray(const std::string& Name, const std::vector<const TCHAR*>& vecFileName, const std::string& PathName)
{
	if (m_vecMaterial.empty())
		return false;

	m_vecMaterial[0]->SetTextureArray(0, 10, (int)EShaderBufferType::Pixel, Name, vecFileName, PathName);

	return true;
}

bool CPrimitiveComponent::SetTextureArrayFullPath(const std::string& Name, const std::vector<const TCHAR*>& vecFullPath)
{
	if (m_vecMaterial.empty())
		return false;

	m_vecMaterial[0]->SetTextureArrayFullPath(0, 10, (int)EShaderBufferType::Pixel, Name, vecFullPath);

	return true;
}

void CPrimitiveComponent::SetTextureFrameIndex(int Index)
{
	m_vecMaterial[0]->SetTextureFrameIndex(0, Index);
}

CTexture* CPrimitiveComponent::GetTexture(int Index) const
{
	if (m_vecMaterial.empty())
		return nullptr;

	return m_vecMaterial[0]->GetTexture(Index);
}

void CPrimitiveComponent::Start()
{
	CSceneComponent::Start();

	// Scene�� ��ġ�� �ǰ� Start�� ȣ��Ǹ� ��� ������� �����Ѵ�.
	CRenderManager::GetInst()->AddRenderList(this);
}

bool CPrimitiveComponent::Init()
{
	if (!CSceneComponent::Init())
		return false;

	return true;
}

void CPrimitiveComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);
}

void CPrimitiveComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
}

void CPrimitiveComponent::Render()
{
	CSceneComponent::Render();

	int	Size = (int)m_vecMaterial.size();

	for (int i = 0; i < Size; ++i)
	{
		m_vecMaterial[i]->SetMaterial();

		m_Mesh->Render(i);

		m_vecMaterial[i]->ResetMaterial();
	}
}

CPrimitiveComponent* CPrimitiveComponent::Clone() const
{
	return new CPrimitiveComponent(*this);
}

void CPrimitiveComponent::Save(FILE* File)
{
	CSceneComponent::Save(File);

	int	Length = (int)m_Mesh->GetName().length();

	fwrite(&Length, 4, 1, File);
	fwrite(m_Mesh->GetName().c_str(), 1, Length, File);

	int	MaterialCount = (int)m_vecMaterial.size();

	fwrite(&MaterialCount, 4, 1, File);

	for (int i = 0; i < MaterialCount; ++i)
	{
		m_vecMaterial[i]->Save(File);
	}
}

void CPrimitiveComponent::Load(FILE* File)
{
	CSceneComponent::Load(File);

	int	Length = 0;
	char	MeshName[256] = {};

	fread(&Length, 4, 1, File);
	fread(MeshName, 1, Length, File);

	SetMesh(MeshName);

	int	MaterialCount = 0;

	fread(&MaterialCount, 4, 1, File);

	m_vecMaterial.clear();

	for (int i = 0; i < MaterialCount; ++i)
	{
		CMaterial* Material = m_Mesh->GetMaterial(i);

		Material = Material->Clone();

		Material->SetScene(m_Scene);

		Material->Load(File);

		m_vecMaterial.push_back(Material);
	}
}