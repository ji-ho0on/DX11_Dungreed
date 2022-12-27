#include "DustEffectAnimation.h"
#include "Component/SpriteComponent.h"
#include "GameObject/GameObject.h"

CDustEffectAnimation::CDustEffectAnimation()
{
	m_ClassName = "DustEffectAnimation";
}

CDustEffectAnimation::CDustEffectAnimation(const CDustEffectAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CDustEffectAnimation::~CDustEffectAnimation()
{
}

void CDustEffectAnimation::Start()
{
	CAnimation2D::Start();

	CAnimation2DData* Effect = FindAnimation("DustEffect");

	if (Effect)
		Effect->SetEndFunction<CDustEffectAnimation>(this, &CDustEffectAnimation::EffectEnd);
}

bool CDustEffectAnimation::Init()
{
	AddAnimation("DustEffect", "DustEffect", 0.5f, 1.f, false);

	return true;
}

void CDustEffectAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CDustEffectAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CDustEffectAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CDustEffectAnimation* CDustEffectAnimation::Clone()
{
	return new CDustEffectAnimation(*this);
}

void CDustEffectAnimation::EffectEnd()
{
	m_Owner->GetOwner()->Destroy();
}