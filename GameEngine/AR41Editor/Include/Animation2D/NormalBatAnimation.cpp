#include "NormalBatAnimation.h"
#include "Component/SpriteComponent.h"
#include "Scene/Scene.h"
#include "../GameObject/BatBullet.h"
#include "../GameObject/Banshee.h"

CNormalBatAnimation::CNormalBatAnimation()
{
	m_ClassName = "NormalBatAnimation";
}

CNormalBatAnimation::CNormalBatAnimation(const CNormalBatAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CNormalBatAnimation::~CNormalBatAnimation()
{
}

void CNormalBatAnimation::Start()
{
	CAnimation2D::Start();
}

bool CNormalBatAnimation::Init()
{
	AddAnimation("Idle", "Idle_NormalBat", 1.f, 1.f, true);

	return true;
}

void CNormalBatAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CNormalBatAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CNormalBatAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CNormalBatAnimation* CNormalBatAnimation::Clone()
{
	return new CNormalBatAnimation(*this);
}