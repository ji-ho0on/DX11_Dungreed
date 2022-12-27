#include "GhostAnimation.h"
#include "Component/SpriteComponent.h"
#include "Scene/Scene.h"

CGhostAnimation::CGhostAnimation()
{
	m_ClassName = "GhostAnimation";
}

CGhostAnimation::CGhostAnimation(const CGhostAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CGhostAnimation::~CGhostAnimation()
{
}

void CGhostAnimation::Start()
{
	CAnimation2D::Start();

	CAnimation2DData* Attack = FindAnimation("Attack");

	//if (Attack)
	//{
	//	Attack->SetEndFunction<CGhostAnimation>(this, &CGhostAnimation::AttackEnd);
	//}
}

bool CGhostAnimation::Init()
{
	AddAnimation("Idle", "Idle_Ghost", 1.f, 1.f, true);
	AddAnimation("Attack", "Attack_Ghost", 1.f, 1.f, false);

	return true;
}

void CGhostAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CGhostAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CGhostAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CGhostAnimation* CGhostAnimation::Clone()
{
	return new CGhostAnimation(*this);
}

void CGhostAnimation::AttackEnd()
{
}