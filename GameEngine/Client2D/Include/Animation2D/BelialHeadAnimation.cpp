#include "BelialHeadAnimation.h"
#include "Component/SpriteComponent.h"
#include "GameObject/GameObject.h"

CBelialHeadAnimation::CBelialHeadAnimation()
{
	m_ClassName = "BelialHeadAnimation";
}

CBelialHeadAnimation::CBelialHeadAnimation(const CBelialHeadAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CBelialHeadAnimation::~CBelialHeadAnimation()
{
}

void CBelialHeadAnimation::Start()
{
	CAnimation2D::Start();

	//CAnimation2DData* WeaponEffect = FindAnimation("WeaponEffect");

	//if (WeaponEffect)
	//	WeaponEffect->SetEndFunction<CBelialHeadAnimation>(this, &CBelialHeadAnimation::ShortSwordSwingEnd);
}

bool CBelialHeadAnimation::Init()
{
	AddAnimation("Idle", "BelialHead_Idle", 1.f, 1.f, true);
	AddAnimation("Attack", "BelialHead_Attack", 1.f, 1.f, false);

	return true;
}

void CBelialHeadAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CBelialHeadAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CBelialHeadAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CBelialHeadAnimation* CBelialHeadAnimation::Clone()
{
	return new CBelialHeadAnimation(*this);
}