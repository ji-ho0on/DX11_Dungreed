#include "MouseConstantBuffer.h"

CMouseConstantBuffer::CMouseConstantBuffer() :
	m_BufferData{}
{
}

CMouseConstantBuffer::CMouseConstantBuffer(const CMouseConstantBuffer& Buffer) :
	CConstantBufferData(Buffer)
{
	m_BufferData = Buffer.m_BufferData;
}

CMouseConstantBuffer::~CMouseConstantBuffer()
{
}

bool CMouseConstantBuffer::Init()
{
	SetConstantBuffer("Mouse");

	return true;
}

void CMouseConstantBuffer::UpdateBuffer()
{
	m_Buffer->UpdateBuffer(&m_BufferData);
}

CMouseConstantBuffer* CMouseConstantBuffer::Clone()
{
	return new CMouseConstantBuffer(*this);
}