#include "TestAnimation2D.h"

CTestAnimation2D::CTestAnimation2D()
{
	m_ClassName = "TestAnimation2D";
}

CTestAnimation2D::CTestAnimation2D(const CTestAnimation2D& Anim) :
	CAnimation2D(Anim)
{
}

CTestAnimation2D::~CTestAnimation2D()
{
}

bool CTestAnimation2D::Init()
{
	//AddAnimation("Test", "Test", 1.f, 1.f, true);

	return true;
}

void CTestAnimation2D::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CTestAnimation2D::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CTestAnimation2D::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CTestAnimation2D* CTestAnimation2D::Clone()
{
	return new CTestAnimation2D(*this);
}
