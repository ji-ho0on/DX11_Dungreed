#include "ColliderLine2DConstantBuffer.h"

CColliderLine2DConstantBuffer::CColliderLine2DConstantBuffer() :
	m_BufferData{}
{
}

CColliderLine2DConstantBuffer::CColliderLine2DConstantBuffer(const CColliderLine2DConstantBuffer& Buffer) :
	CConstantBufferData(Buffer)
{
	m_BufferData = Buffer.m_BufferData;
}

CColliderLine2DConstantBuffer::~CColliderLine2DConstantBuffer()
{
}

bool CColliderLine2DConstantBuffer::Init()
{
	SetConstantBuffer("ColliderLine2D");

	return true;
}

void CColliderLine2DConstantBuffer::UpdateBuffer()
{
	m_Buffer->UpdateBuffer(&m_BufferData);
}

CColliderLine2DConstantBuffer* CColliderLine2DConstantBuffer::Clone()
{
	return new CColliderLine2DConstantBuffer(*this);
}
