#pragma once

#include "ConstantBufferData.h"

class CColliderLine2DConstantBuffer :
    public CConstantBufferData
{
public:
	CColliderLine2DConstantBuffer();
	CColliderLine2DConstantBuffer(const CColliderLine2DConstantBuffer& Buffer);
	virtual ~CColliderLine2DConstantBuffer();

private:
	ColliderLine2DCBuffer	m_BufferData;

public:
	virtual bool Init();
	virtual void UpdateBuffer();
	virtual CColliderLine2DConstantBuffer* Clone();

public:
	void SetColor(const Vector4& Color)
	{
		m_BufferData.Color = Color;
	}

	void SetWVP(const Matrix& matWVP)
	{
		m_BufferData.matWVP = matWVP;
		m_BufferData.matWVP.Transpose();
	}
	
	void SetConvertPoint(const Vector3& Point)
	{
		m_BufferData.ConvertPoint = Point;
	}
};

