#include "CameraManager.h"
#include "../Component/CameraComponent.h"

CCameraManager::CCameraManager()
{
}

CCameraManager::~CCameraManager()
{
}

void CCameraManager::SetCurrentCamera(CCameraComponent* Camera)
{
	m_CurrentCamera = Camera;
}

void CCameraManager::SetUICamera(CCameraComponent* Camera)
{
	m_UICamera = Camera;
}

void CCameraManager::Start()
{
}

bool CCameraManager::Init()
{
	// 기본 카메라를 하나 생성한다.
	m_CurrentCamera = new CCameraComponent;

	m_CurrentCamera->Init();

	m_CurrentCamera->SetCameraType(ECameraType::Camera2D);

	// 기본 UI카메라를 하나 생성한다.
	m_UICamera = new CCameraComponent;

	m_UICamera->Init();

	m_UICamera->SetCameraType(ECameraType::CameraUI);

	return true;
}

void CCameraManager::Update(float DeltaTime)
{
	if (!m_CurrentCamera->GetOwner())
	{
		m_CurrentCamera->Update(DeltaTime);
	}
}

void CCameraManager::PostUpdate(float DeltaTime)
{
	if (!m_CurrentCamera->GetOwner())
	{
		m_CurrentCamera->PostUpdate(DeltaTime);
	}
}

void CCameraManager::Save(FILE* File)
{
}

void CCameraManager::Load(FILE* File)
{
}