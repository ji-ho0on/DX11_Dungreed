#include "ConstantBuffer.h"
#include "../../Device.h"

CConstantBuffer::CConstantBuffer() :
	m_Buffer(nullptr),
	m_Size(0),
	m_Register(0),
	m_ShaderBufferType(0)
{
}

CConstantBuffer::~CConstantBuffer()
{
	SAFE_RELEASE(m_Buffer);
}

bool CConstantBuffer::Init(int Size, int Register, int ShaderBufferType)
{
	m_Size = Size;
	m_Register = Register;
	m_ShaderBufferType = ShaderBufferType;

	D3D11_BUFFER_DESC	Desc = {};

	Desc.Usage = D3D11_USAGE_DYNAMIC;
	Desc.ByteWidth = Size;
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// Device를 이용해 버퍼 생성
	if (FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&Desc, nullptr, &m_Buffer)))
		return false;

	return true;
}

void CConstantBuffer::UpdateBuffer(void* Data)
{
	// 버퍼를 갱신한다.
	D3D11_MAPPED_SUBRESOURCE	Map = {};

	// Map, UnMap을 이용해서 버퍼를 갱신하는 동안 다른곳에서 접근할 수 없게 Lock을 건다.
	CDevice::GetInst()->GetContext()->Map(m_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Map);

	memcpy(Map.pData, Data, m_Size);

	CDevice::GetInst()->GetContext()->Unmap(m_Buffer, 0);

	// Context를 이용해 ShaderType에 맞는 상수 버퍼로 등록 할 수 있음
	if (m_ShaderBufferType & (int)EShaderBufferType::Vertex)
		CDevice::GetInst()->GetContext()->VSSetConstantBuffers(m_Register, 1, &m_Buffer);

	if (m_ShaderBufferType & (int)EShaderBufferType::Pixel)
		CDevice::GetInst()->GetContext()->PSSetConstantBuffers(m_Register, 1, &m_Buffer);

	if (m_ShaderBufferType & (int)EShaderBufferType::Hull)
		CDevice::GetInst()->GetContext()->HSSetConstantBuffers(m_Register, 1, &m_Buffer);

	if (m_ShaderBufferType & (int)EShaderBufferType::Domain)
		CDevice::GetInst()->GetContext()->DSSetConstantBuffers(m_Register, 1, &m_Buffer);

	if (m_ShaderBufferType & (int)EShaderBufferType::Geometry)
		CDevice::GetInst()->GetContext()->GSSetConstantBuffers(m_Register, 1, &m_Buffer);

	if (m_ShaderBufferType & (int)EShaderBufferType::Compute)
		CDevice::GetInst()->GetContext()->CSSetConstantBuffers(m_Register, 1, &m_Buffer);
}
