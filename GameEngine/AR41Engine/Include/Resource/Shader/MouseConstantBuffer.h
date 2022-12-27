#pragma once

#include "ConstantBufferData.h"

class CMouseConstantBuffer :
    public CConstantBufferData
{
public:
	CMouseConstantBuffer();
	CMouseConstantBuffer(const CMouseConstantBuffer& Buffer);
	virtual ~CMouseConstantBuffer();

private:
	MouseCBuffer	m_BufferData;

public:
	virtual bool Init();
	virtual void UpdateBuffer();
	virtual CMouseConstantBuffer* Clone();

public:
	void SetWVP(Matrix matWVP)
	{
		m_BufferData.MouseWVP = matWVP;
		m_BufferData.MouseWVP.Transpose();
	}
};

