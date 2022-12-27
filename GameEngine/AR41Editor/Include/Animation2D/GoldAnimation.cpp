#include "GoldAnimation.h"
#include "Component/SpriteComponent.h"
#include "GameObject/GameObject.h"

CGoldAnimation::CGoldAnimation()
{
	m_ClassName = "GoldAnimation";
}

CGoldAnimation::CGoldAnimation(const CGoldAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CGoldAnimation::~CGoldAnimation()
{
}

void CGoldAnimation::Start()
{
	CAnimation2D::Start();
}

bool CGoldAnimation::Init()
{
	AddAnimation("GoldCoin", "GoldCoin", 1.f, 1.5f, true);

	return true;
}

void CGoldAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CGoldAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CGoldAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CGoldAnimation* CGoldAnimation::Clone()
{
	return new CGoldAnimation(*this);
}
