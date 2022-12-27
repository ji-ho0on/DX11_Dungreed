#include "DustEffect.h"
#include "Component/SpriteComponent.h"
#include "../Animation2D/DustEffectAnimation.h"

CDustEffect::CDustEffect()
{
	SetTypeID<CDustEffect>();

	m_ObjectTypeName = "DustEffect";
}

CDustEffect::CDustEffect(const CDustEffect& Obj) :
	CGameObject(Obj)
{
}

CDustEffect::~CDustEffect()
{
}

void CDustEffect::SetEffectInfo(const Vector2& Position)
{
	m_Effect->SetWorldPosition(Position);
}

void CDustEffect::SetEffectDir(EDirection Dir)
{
	if (Dir == EDirection::Left)
		m_Effect->SetDir(EDirection::Left);

	else if(Dir == EDirection::Right)
		m_Effect->SetDir(EDirection::Right);
}

void CDustEffect::Start()
{
	CGameObject::Start();
}

bool CDustEffect::Init()
{
	CGameObject::Init();

	m_Effect = CreateComponent<CSpriteComponent>("Effect");
	m_Effect->SetAnimation<CDustEffectAnimation>("DustEffectAnimation");
	m_Effect->SetRenderLayerName("Effect");
	m_Effect->SetWorldScale(42.f, 39.f);
	m_Effect->SetPivot(0.5f, 0.f);

	// юс╫ц
	m_Effect->SetWorldPosition(500.f, 200.f);

	return true;
}

void CDustEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CDustEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDustEffect* CDustEffect::Clone() const
{
	return new CDustEffect(*this);
}

void CDustEffect::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CDustEffect::Load(FILE* File)
{
	CGameObject::Load(File);
}