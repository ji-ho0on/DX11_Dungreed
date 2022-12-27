#include "EndingPortal.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../Animation2D/PortalAnimation.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "PathManager.h"
#include "Input.h"
#include "../TransferInfo/TransferCharacterInfo.h"
#include "Character.h"
#include "Resource/Sound/Sound.h"
#include "../Scene/EndingScene.h"

CEndingPortal::CEndingPortal()
{
	SetTypeID<CEndingPortal>();

	m_ObjectTypeName = "EndingPortal";
}

CEndingPortal::CEndingPortal(const CEndingPortal& Obj) :
	CGameObject(Obj)
{
	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_Portal = (CSpriteComponent*)FindComponent("Portal");
	m_PortalInteraction = (CSpriteComponent*)FindComponent("PortalInteraction");
}

CEndingPortal::~CEndingPortal()
{
	CInput::GetInst()->DeleteBindFunction<CEndingPortal>("F", Input_Type::Down, this);
}

void CEndingPortal::Start()
{
	CGameObject::Start();

	m_Body->SetCollisionCallback<CEndingPortal>(ECollision_Result::Collision, this, &CEndingPortal::PortalCollision);
	m_Body->SetCollisionCallback<CEndingPortal>(ECollision_Result::Release, this, &CEndingPortal::PortalRelease);

	// F키 등록
	CInput::GetInst()->AddBindFunction<CEndingPortal>("F", Input_Type::Push, this, &CEndingPortal::PortalEntrance, m_Scene);
}

bool CEndingPortal::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Body->SetCollisionProfile("NPC");
	m_Body->SetInheritScale(true);
	m_Body->SetPivot(0.5f, 0.f);
	m_Body->SetBoxSize(100.f, 180.f);

	m_Portal = CreateComponent<CSpriteComponent>("Portal");
	m_Portal->SetAnimation<CPortalAnimation>("PortalAnimation");
	m_Portal->SetRenderLayerName("NPC");
	m_Portal->SetWorldScale(200.f, 230.f);
	m_Portal->SetPivot(0.5f, 0.f);
	m_Portal->Set2DZOffset(500.f);

	m_PortalInteraction = CreateComponent<CSpriteComponent>("PortalInteraction");
	m_PortalInteraction->SetTexture("Keyboard_F", TEXT("common/key/Keyboard_F.png"));
	m_PortalInteraction->SetRenderLayerName("NPC");
	m_PortalInteraction->SetWorldScale(52.f, 56.f);
	m_PortalInteraction->SetPivot(0.5f, 0.f);
	m_PortalInteraction->SetRelativePositionY(130.f);
	m_PortalInteraction->Set2DZOffset(-100.f);
	m_PortalInteraction->SetEnable(false);

	m_Body->AddChild(m_Portal);
	m_Body->AddChild(m_PortalInteraction);

	// 임시
	m_Body->SetWorldPosition(300.f, 128.f);

	return true;
}

void CEndingPortal::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CEndingPortal::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CEndingPortal* CEndingPortal::Clone() const
{
	return new CEndingPortal(*this);
}

void CEndingPortal::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CEndingPortal::Load(FILE* File)
{
	CGameObject::Load(File);

	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_Portal = (CSpriteComponent*)FindComponent("Portal");
	m_PortalInteraction = (CSpriteComponent*)FindComponent("PortalInteraction");
}

void CEndingPortal::PortalCollision(const CollisionResult& Result)
{
	if (m_PortalInteraction)
		m_PortalInteraction->SetEnable(true);
}

void CEndingPortal::PortalRelease(const CollisionResult& Result)
{
	if (m_PortalInteraction && GetActive())
		m_PortalInteraction->SetEnable(false);
}

void CEndingPortal::PortalEntrance()
{
	if (m_PortalInteraction->GetEnable())
	{
		// 다음 씬으로 넘어감
		CSceneManager::GetInst()->CreateNextScene();
		CScene* NextScene = CSceneManager::GetInst()->GetNextScene();

		NextScene->CreateSceneInfo<CEndingScene>();
	}
}