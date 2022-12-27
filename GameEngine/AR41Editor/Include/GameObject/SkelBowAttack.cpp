#include "SkelBowAttack.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderOBB2D.h"
#include "Character.h"
#include "Scene/Scene.h"
#include "ArrowHitEffect.h"

CSkelBowAttack::CSkelBowAttack()
{
	SetTypeID<CSkelBowAttack>();

	m_ObjectTypeName = "SkelBowAttack";
}

CSkelBowAttack::CSkelBowAttack(const CSkelBowAttack& Obj) :
	CGameObject(Obj)
{
	m_Body = (CColliderOBB2D*)FindComponent("Body");
	m_Arrow = (CSpriteComponent*)FindComponent("Arrow");
}

CSkelBowAttack::~CSkelBowAttack()
{
}

void CSkelBowAttack::SetAttackInfo(const Vector2& Position, const Vector3& Dir, float Angle)
{
	m_Dir = Dir;
	m_Dir.Normalize();

	m_InitPosition = Position;

	m_Body->SetWorldPosition(Position);

	m_Body->SetWorldRotationZ(Angle);
}

void CSkelBowAttack::Start()
{
	CGameObject::Start();

	m_Body->SetCollisionCallback<CSkelBowAttack>(ECollision_Result::Collision, this, &CSkelBowAttack::EffectCollision);
}

bool CSkelBowAttack::Init()
{
	CGameObject::Init();

	// �浹�� Collider ����
	m_Body = CreateComponent<CColliderOBB2D>("Body");
	m_Body->SetCollisionProfile("MonsterAttack");

	// Effect ����
	m_Arrow = CreateComponent<CSpriteComponent>("Arrow");
	m_Arrow->SetTexture("Arrow", TEXT("weapon/longDistanceWeapon/Arrow00.png"));
	m_Arrow->SetRenderLayerName("Weapon");

	m_Body->AddChild(m_Arrow);

	m_Arrow->SetInheritScale(false);
	m_Arrow->SetInheritRotZ(true);

	m_Arrow->SetWorldScale(50.f, 20.f);
	m_Arrow->SetPivot(0.f, 0.5f);

	m_Body->SetBoxHalfSize(m_Arrow->GetWorldScale().x / 2.f, m_Arrow->GetWorldScale().y / 2.f);
	m_Body->SetPivot(0.f, 0.5f);

	return true;
}

void CSkelBowAttack::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Body->AddWorldPosition(m_Dir * 1000.f * DeltaTime);

	if (m_InitPosition.Distance(GetWorldPos()) >= 700.f)
	{
		// ������ ����Ʈ ����
		m_Scene->CreateObject<CArrowHitEffect>("ArrowHitEffect")->SetEffectInfo(GetWorldPos(), GetWorldRot().z);

		Destroy();
	}
}

void CSkelBowAttack::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CSkelBowAttack* CSkelBowAttack::Clone() const
{
	return new CSkelBowAttack(*this);
}

void CSkelBowAttack::EffectCollision(const CollisionResult& Result)
{
	// ���Ϳ��� �������� �ش�.
	((CCharacter*)Result.Dest->GetOwner())->InflictDamage(10);

	// ������ ����Ʈ ����
	m_Scene->CreateObject<CArrowHitEffect>("ArrowHitEffect")->SetEffectInfo(GetWorldPos(), GetWorldRot().z);

	Destroy();
}