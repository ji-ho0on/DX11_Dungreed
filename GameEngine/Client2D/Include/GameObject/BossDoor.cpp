#include "BossDoor.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../Animation2D/DoorAnimation.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "PathManager.h"
#include "Input.h"
#include "../TransferInfo/TransferCharacterInfo.h"
#include "Character.h"
#include "Resource/Sound/Sound.h"

CBossDoor::CBossDoor()
{
	SetTypeID<CBossDoor>();

	m_ObjectTypeName = "BossDoor";
}

CBossDoor::CBossDoor(const CBossDoor& Obj) :
	CGameObject(Obj)
{
	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_Door = (CSpriteComponent*)FindComponent("Door");
	m_DoorInteraction = (CSpriteComponent*)FindComponent("DoorInteraction");
}

CBossDoor::~CBossDoor()
{
	CInput::GetInst()->DeleteBindFunction<CBossDoor>("F", Input_Type::Down, this);
}

void CBossDoor::Start()
{
	CGameObject::Start();

	m_Body->SetCollisionCallback<CBossDoor>(ECollision_Result::Collision, this, &CBossDoor::DoorCollision);
	m_Body->SetCollisionCallback<CBossDoor>(ECollision_Result::Release, this, &CBossDoor::DoorRelease);

	m_Door->GetAnimation()->SetPlay(false);

	// F키 등록
	CInput::GetInst()->AddBindFunction<CBossDoor>("F", Input_Type::Push, this, &CBossDoor::DoorEntrance, m_Scene);
}

bool CBossDoor::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Body->SetCollisionProfile("NPC");
	m_Body->SetInheritScale(true);
	m_Body->SetPivot(0.5f, 0.f);
	m_Body->SetBoxSize(100.f, 180.f);

	m_Door = CreateComponent<CSpriteComponent>("Door");
	m_Door->SetAnimation<CDoorAnimation>("DoorAnimation");
	m_Door->SetRenderLayerName("NPC");
	m_Door->SetWorldScale(200.f, 230.f);
	m_Door->SetPivot(0.5f, 0.f);
	m_Door->Set2DZOffset(500.f);

	m_DoorInteraction = CreateComponent<CSpriteComponent>("DoorInteraction");
	m_DoorInteraction->SetTexture("Keyboard_F", TEXT("common/key/Keyboard_F.png"));
	m_DoorInteraction->SetRenderLayerName("NPC");
	m_DoorInteraction->SetWorldScale(52.f, 56.f);
	m_DoorInteraction->SetPivot(0.5f, 0.f);
	m_DoorInteraction->SetRelativePositionY(130.f);
	m_DoorInteraction->Set2DZOffset(-100.f);
	m_DoorInteraction->SetEnable(false);

	m_Body->AddChild(m_Door);
	m_Body->AddChild(m_DoorInteraction);

	// 임시
	m_Body->SetWorldPosition(1100.f, 128.f);

	return true;
}

void CBossDoor::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBossDoor::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBossDoor* CBossDoor::Clone() const
{
	return new CBossDoor(*this);
}

void CBossDoor::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CBossDoor::Load(FILE* File)
{
	CGameObject::Load(File);

	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_Door = (CSpriteComponent*)FindComponent("Door");
	m_DoorInteraction = (CSpriteComponent*)FindComponent("DoorInteraction");
}

void CBossDoor::DoorCollision(const CollisionResult& Result)
{
	if (m_DoorInteraction)
		m_DoorInteraction->SetEnable(true);
}

void CBossDoor::DoorRelease(const CollisionResult& Result)
{
	if (m_DoorInteraction && m_Body->GetActive())
		m_DoorInteraction->SetEnable(false);
}

void CBossDoor::DoorEntrance()
{
	if (m_DoorInteraction->GetEnable())
	{
		// 다음 씬으로 넘어감
		CSceneManager::GetInst()->CreateNextScene();
		CScene* CurrentScene = CSceneManager::GetInst()->GetScene();
		CScene* NextScene = CSceneManager::GetInst()->GetNextScene();



		// 현재 씬의 MonsterClear 여부를 true로 바꾸고 저장
		const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

		char	FullPath[MAX_PATH] = {};

		strcpy_s(FullPath, Info->PathMultibyte);
		strcat_s(FullPath, "Scene/NormalScene6.scn");

		// 새로 로드해와서 MonsterClear 여부만 바꿔주고 다시 저장
		NextScene->Load(FullPath);
		NextScene->GetSceneInfo()->SetMonsterClear(true);
		NextScene->Save(FullPath);



		// 씬을 새로 만듬
		CSceneManager::GetInst()->CreateNextScene();

		NextScene = CSceneManager::GetInst()->GetNextScene();


		// 다음 씬 로드
		char	FullPath1[MAX_PATH] = {};

		strcpy_s(FullPath1, Info->PathMultibyte);
		strcat_s(FullPath1, "Scene/BossEntranceScene.scn");

		NextScene->Load(FullPath1);

		// 현재 씬의 캐릭터 정보를 받아와서 다음 씬의 캐릭터에게 정보를 이전시킴
		CTransferCharacterInfo::GetInst()->ReadInfo((CCharacter*)(CurrentScene->GetSceneInfo()->GetPlayerObject()));

		CCharacter* Character = (CCharacter*)(NextScene->GetSceneInfo()->GetPlayerObject());

		if (Character)
		{
			CTransferCharacterInfo::GetInst()->SetInfo(Character);
			Character->SetCharacterPosition(Vector2(482.f, 250.f));
		}

		CSound* JailField = m_Scene->GetResource()->FindSound("JailField");
		if (JailField)
			JailField->Stop();
	}
}
