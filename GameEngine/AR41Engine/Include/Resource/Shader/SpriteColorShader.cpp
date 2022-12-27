#include "SpriteColorShader.h"

CSpriteColorShader::CSpriteColorShader()
{
}

CSpriteColorShader::~CSpriteColorShader()
{
}

bool CSpriteColorShader::Init()
{
	// VertexShader�� PixelShader�� �о����
	if (!LoadVertexShader("SpriteColorVS", TEXT("Sprite.fx"), SHADER_PATH))
		return false;

	if (!LoadPixelShader("SpriteColorPS", TEXT("Sprite.fx"), SHADER_PATH))
		return false;

	// Position�� Color�� ����ؾ��ϱ⶧���� InputDesc 2���� ä���ش�.
	// Position�� Vector3�� 12����Ʈ, Color�� Vector4�� 16����Ʈ
	AddInputDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0);
	AddInputDesc("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0);

	// InputLayout�� �����Ѵ�.
	if (!CreateInputLayout())
		return false;

	return true;
}
