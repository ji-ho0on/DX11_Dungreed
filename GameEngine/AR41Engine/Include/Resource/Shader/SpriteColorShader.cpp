#include "SpriteColorShader.h"

CSpriteColorShader::CSpriteColorShader()
{
}

CSpriteColorShader::~CSpriteColorShader()
{
}

bool CSpriteColorShader::Init()
{
	// VertexShader와 PixelShader를 읽어야함
	if (!LoadVertexShader("SpriteColorVS", TEXT("Sprite.fx"), SHADER_PATH))
		return false;

	if (!LoadPixelShader("SpriteColorPS", TEXT("Sprite.fx"), SHADER_PATH))
		return false;

	// Position과 Color를 사용해야하기때문에 InputDesc 2개를 채워준다.
	// Position은 Vector3로 12바이트, Color는 Vector4로 16바이트
	AddInputDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0);
	AddInputDesc("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0);

	// InputLayout을 생성한다.
	if (!CreateInputLayout())
		return false;

	return true;
}
