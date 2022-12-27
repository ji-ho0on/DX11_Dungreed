#include "GiantRedBatAnimation.h"
#include "Component/SpriteComponent.h"
#include "Scene/Scene.h"
#include "../GameObject/BatBullet.h"
#include "../GameObject/Banshee.h"

CGiantRedBatAnimation::CGiantRedBatAnimation()
{
	m_ClassName = "GiantNormalBatAnimation";
}

CGiantRedBatAnimation::CGiantRedBatAnimation(const CGiantRedBatAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CGiantRedBatAnimation::~CGiantRedBatAnimation()
{
}

void CGiantRedBatAnimation::Start()
{
	CAnimation2D::Start();

	//CAnimation2DData* Attack = FindAnimation("Attack");

	//if (Attack)
	//{
	//	Attack->AddNotify<CGiantRedBatAnimation>("SummonBullet", 5, this, &CGiantRedBatAnimation::SummonBullet);
	//	Attack->SetEndFunction<CGiantRedBatAnimation>(this, &CGiantRedBatAnimation::AttackEnd);
	//}
}

bool CGiantRedBatAnimation::Init()
{
	AddAnimation("Idle", "Idle_GiantRedBat", 1.f, 1.f, true);
	AddAnimation("Attack", "Attack_GiantRedBat", 1.f, 0.5f, false);

	return true;
}

void CGiantRedBatAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CGiantRedBatAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CGiantRedBatAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CGiantRedBatAnimation* CGiantRedBatAnimation::Clone()
{
	return new CGiantRedBatAnimation(*this);
}