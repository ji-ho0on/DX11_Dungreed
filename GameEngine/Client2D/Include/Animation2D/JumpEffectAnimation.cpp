#include "JumpEffectAnimation.h"
#include "Component/SpriteComponent.h"
#include "GameObject/GameObject.h"

CJumpEffectAnimation::CJumpEffectAnimation()
{
	m_ClassName = "JumpEffectAnimation";
}

CJumpEffectAnimation::CJumpEffectAnimation(const CJumpEffectAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CJumpEffectAnimation::~CJumpEffectAnimation()
{
}

void CJumpEffectAnimation::Start()
{
	CAnimation2D::Start();

	CAnimation2DData* Effect = FindAnimation("JumpEffect");

	if (Effect)
		Effect->SetEndFunction<CJumpEffectAnimation>(this, &CJumpEffectAnimation::EffectEnd);
}

bool CJumpEffectAnimation::Init()
{
	AddAnimation("JumpEffect", "JumpEffect", 0.5f, 1.f, false);

	return true;
}

void CJumpEffectAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CJumpEffectAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CJumpEffectAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CJumpEffectAnimation* CJumpEffectAnimation::Clone()
{
	return new CJumpEffectAnimation(*this);
}

void CJumpEffectAnimation::EffectEnd()
{
	m_Owner->GetOwner()->Destroy();
}