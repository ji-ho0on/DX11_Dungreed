#pragma once

#include "../../Ref.h"

class CConstantBuffer :
	public CRef
{
	friend class CShaderManager;

private:
	CConstantBuffer();
	~CConstantBuffer();

private:
	ID3D11Buffer*	m_Buffer;			// Buffer data
	int				m_Size;				// Buffer Size
	int				m_Register;
	int				m_ShaderBufferType;	// enum class로 ShaderBufferType이 지정되어 있음

public:
	bool Init(int Size, int Register, int ShaderBufferType);
	void UpdateBuffer(void* Data);
};

