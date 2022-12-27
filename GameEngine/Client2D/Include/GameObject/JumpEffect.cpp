#include "JumpEffect.h"
#include "Component/SpriteComponent.h"
#include "../Animation2D/JumpEffectAnimation.h"

CJumpEffect::CJumpEffect()
{
	SetTypeID<CJumpEffect>();

	m_ObjectTypeName = "JumpEffect";
}

CJumpEffect::CJumpEffect(const CJumpEffect& Obj) :
	CGameObject(Obj)
{
}

CJumpEffect::~CJumpEffect()
{
}

void CJumpEffect::SetEffectInfo(const Vector2& Position)
{
	m_Effect->SetWorldPosition(Position);
}

void CJumpEffect::Start()
{
	CGameObject::Start();
}

bool CJumpEffect::Init()
{
	CGameObject::Init();

	m_Effect = CreateComponent<CSpriteComponent>("Effect");
	m_Effect->SetAnimation<CJumpEffectAnimation>("JumpEffectAnimation");
	m_Effect->SetRenderLayerName("Effect");
	m_Effect->SetWorldScale(27.f, 33.f);
	m_Effect->SetPivot(0.5f, 0.f);

	// юс╫ц
	m_Effect->SetWorldPosition(500.f, 200.f);

	return true;
}

void CJumpEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CJumpEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CJumpEffect* CJumpEffect::Clone() const
{
	return new CJumpEffect(*this);
}

void CJumpEffect::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CJumpEffect::Load(FILE* File)
{
	CGameObject::Load(File);
}