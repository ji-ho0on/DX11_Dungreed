#include "BatBulletAnimation.h"
#include "Component/SpriteComponent.h"
#include "GameObject/GameObject.h"

CBatBulletAnimation::CBatBulletAnimation()
{
	m_ClassName = "BatBulletAnimation";
}

CBatBulletAnimation::CBatBulletAnimation(const CBatBulletAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CBatBulletAnimation::~CBatBulletAnimation()
{
}

void CBatBulletAnimation::Start()
{
	CAnimation2D::Start();

	CAnimation2DData* Destroy = FindAnimation("Destroy");

	if (Destroy)
	{
		Destroy->SetEndFunction<CBatBulletAnimation>(this, &CBatBulletAnimation::DestroyEnd);
	}
}

bool CBatBulletAnimation::Init()
{
	AddAnimation("Idle", "BatSmallBullet_Idle", 1.f, 1.f, true);
	AddAnimation("Destroy", "BatSmallBullet_Destroy", 1.f, 2.f, false);

	return true;
}

void CBatBulletAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CBatBulletAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CBatBulletAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CBatBulletAnimation* CBatBulletAnimation::Clone()
{
	return new CBatBulletAnimation(*this);
}

void CBatBulletAnimation::DestroyEnd()
{
	m_Owner->GetOwner()->Destroy();
}