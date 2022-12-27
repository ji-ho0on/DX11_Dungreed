#include "ColliderLIne2DShader.h"

CColliderLIne2DShader::CColliderLIne2DShader()
{
}

CColliderLIne2DShader::~CColliderLIne2DShader()
{
}

bool CColliderLIne2DShader::Init()
{
	if (!LoadVertexShader("ColliderLine2DVS", TEXT("Collider.fx"), SHADER_PATH))
		return false;

	if (!LoadPixelShader("ColliderLine2DPS", TEXT("Collider.fx"), SHADER_PATH))
		return false;

	AddInputDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0);

	if (!CreateInputLayout())
		return false;

	return true;
}
