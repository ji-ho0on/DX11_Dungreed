#include "Device.h"

DEFINITION_SINGLE(CDevice)

CDevice::CDevice()	:
	m_Device(nullptr),
	m_Context(nullptr),
	m_SwapChain(nullptr),
	m_TargetView(nullptr),
	m_DepthView(nullptr),
	m_hWnd(0),
	m_RS{},
	m_2DTarget(nullptr),
	m_2DTargetWorld(nullptr),
	m_2DFactory(nullptr)
{
}

CDevice::~CDevice()
{
	SAFE_RELEASE(m_2DTarget);
	SAFE_RELEASE(m_2DTargetWorld);
	SAFE_RELEASE(m_2DFactory);

	// Device �Ҹ� �� �İ�ü���� ��� Release����
	SAFE_RELEASE(m_TargetView);
	SAFE_RELEASE(m_DepthView);
	SAFE_RELEASE(m_SwapChain);

	if (m_Context)
		m_Context->ClearState();

	SAFE_RELEASE(m_Context);
	SAFE_RELEASE(m_Device);
}

Vector2 CDevice::GetResolutionRatio() const
{
	RECT	WindowRC;

	GetClientRect(m_hWnd, &WindowRC);

	float Width = (float)(WindowRC.right - WindowRC.left);
	float Height = (float)(WindowRC.bottom - WindowRC.top);

	return Vector2(m_RS.Width / Width, m_RS.Height / Height);
}

bool CDevice::Init(HWND hWnd, unsigned int DeviceWidth, unsigned int DeviceHeight, bool WindowMode)
{
	m_hWnd = hWnd;
	m_RS.Width = DeviceWidth;
	m_RS.Height = DeviceHeight;

	unsigned int Flag = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG

	// OR �������� �Ѵ� �־���
	Flag |= D3D11_CREATE_DEVICE_DEBUG;

#endif // _DEBUG

	D3D_FEATURE_LEVEL FLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL FLevelResult;

	// Device ���� (Device, Context ����)
	// ����Ÿ�� HRESULT : ���� ���� � ������ �߻��ߴ����� �Ǵ��ϱ� ���� ��ȯ ��
	// FAILED ��ũ�θ� ���� ��ȯ���� üũ�ؼ� - ���� ������ ������ �Ǵ�
	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, Flag, &FLevel, 1,
		D3D11_SDK_VERSION, &m_Device, &FLevelResult, &m_Context)))
		return false;

	// SampleCount�� 4���� ���, Check�� 1���� ������ SampleCount�� 1�� �Ͽ� SwapChain Description�� ä���.
	int	SampleCount = 4;

	UINT	Check = 0;
	m_Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM,	4, &Check);

	if (Check < 1)
		SampleCount = 1;

	// SwapChain ������ �ʿ��� Description�� ä���ش�.
	DXGI_SWAP_CHAIN_DESC	SwapDesc = {};

	// ����۸� ��� ���� ���ΰ�
	// ������� ���� �ػ�
	SwapDesc.BufferDesc.Width = DeviceWidth;

	// ������� ���� �ػ�
	SwapDesc.BufferDesc.Height = DeviceHeight;

	// ������� �ȼ��� � �������� ������� ���ΰ�
	// RGBA 8888 �� �Ϲ������� ��� (r, g , b, a �� 8��Ʈ��)
	// UNORM = usigned�� �� 0 ~ 1 ���̷� ����ȭ�� ��
	SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// �����ֱ�(��������ȭ)
	SwapDesc.BufferDesc.RefreshRate.Numerator = 1;		// ����
	SwapDesc.BufferDesc.RefreshRate.Denominator = 60;	// �и�

	// â���, Ǯ��� ��ȯ �� ȭ���� ũ�⸦ ������� �����ϸ� �� ������
	SwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// ���Ž� �������� ����
	SwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	// ����۸� �� �� ����� ��
	SwapDesc.BufferCount = 1;

	// ������ �뵵�� �������� (����Ÿ�ٿ��� ��¿뵵�� ���)
	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// ����Ʈ(����� ���� ���� ��)�� ������ â�� Ŭ���̾�Ʈ ������ ��� ����� ��
	SwapDesc.OutputWindow = hWnd;

	// Anti-Aliasing ����� ����? ��Ƽ���ø� ������ �Ⱦ� (���߿� ���̴����� ���� �����ؼ� ���)
	SwapDesc.SampleDesc.Quality = 0;			// ��� ����, ���߿� ���ĺ��� �� �� ���ø�ī��Ʈ�� ������ �ذ��ϱ� ���� ����� ��
	SwapDesc.SampleDesc.Count = SampleCount;	// �Ⱦ����� �Ⱦ��� �ɷ� �ϳ� �ʿ���, ���ĺ����� ���� ����ī��Ʈ�� 4�� ���

	// â��� ���� Ǯ��ũ������ true false�� ����
	SwapDesc.Windowed = WindowMode;

	// ��������Ʈ
	SwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;



	// SwapChain ����
	IDXGIDevice* DXGIDevice = nullptr;
	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&DXGIDevice);

	IDXGIAdapter* Adapter = nullptr;
	DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&Adapter);

	IDXGIFactory* Factory = nullptr;
	Adapter->GetParent(__uuidof(IDXGIFactory), (void**)&Factory);

	if (FAILED(Factory->CreateSwapChain(m_Device, &SwapDesc, &m_SwapChain)))
	{
		// SwapChain ������ ���� ���� �ߴ� �� ��ü�� Release
		SAFE_RELEASE(DXGIDevice);
		SAFE_RELEASE(Adapter);
		SAFE_RELEASE(Factory);
		return false;
	}

	SAFE_RELEASE(DXGIDevice);
	SAFE_RELEASE(Adapter);
	SAFE_RELEASE(Factory);

	// SwapChain�� ����� ���ٸ� SwapChain�� ������ �ִ� ����۸� ���´�.
	ID3D11Texture2D* BackBuffer = nullptr;
	if (FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer)))
		return false;

	// ����ۿ� ����� RenderTargetView�� �����Ѵ�.
	if (FAILED(m_Device->CreateRenderTargetView(BackBuffer, nullptr, &m_TargetView)))
		return false;

	// TargetView ������ ���� �����ߴ� BackBuffer �İ�ü Release
	SAFE_RELEASE(BackBuffer);


	// DepthBuffer ������ ���� Description�� ä���ش�.
	D3D11_TEXTURE2D_DESC	DepthDesc = {};
	DepthDesc.Width = DeviceWidth;
	DepthDesc.Height = DeviceHeight;

	DepthDesc.ArraySize = 1;

	// ���̰����� 3����Ʈ�� ���ڴٴ� ��, ���Ľ� ���ۿ� 8��Ʈ
	DepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// ���� ���ٽ� �뵵�� ���� ��
	DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	// �뵵
	// ���� �޸𸮸� �̿���, ���� ����
	DepthDesc.Usage = D3D11_USAGE_DEFAULT;

	DepthDesc.SampleDesc.Count = SampleCount;
	DepthDesc.SampleDesc.Quality = 0;

	DepthDesc.MipLevels = 1;

	// DepthBuffer�� �����Ѵ�.
	ID3D11Texture2D* DepthBuffer = nullptr;

	if (FAILED(m_Device->CreateTexture2D(&DepthDesc, nullptr, &DepthBuffer)))
		return false;

	if (FAILED(m_Device->CreateDepthStencilView(DepthBuffer, nullptr, &m_DepthView)))
		return false;

	// DepthBuffer ������ ���� ������ �İ�ü Release
	SAFE_RELEASE(DepthBuffer);


	// ViewPort�� �����Ѵ�.
	D3D11_VIEWPORT VP = {};

	// TopLeft�� �����ϸ� ������ ��ġ���� ȭ���� ��µ�.
	//VP.TopLeftX = 100.f;
	//VP.TopLeftY = 100.f;

	// ��µ� ȭ���� ũ�⸦ ����
	// ���� Device ũ��� ����
	VP.Width = (float)DeviceWidth;
	VP.Height = (float)DeviceHeight;

	// �ִ� ���̴� 1�� ����
	VP.MaxDepth = 1.f;

	// Context�� �̿��� ViewPort�� �����Ѵ�.
	m_Context->RSSetViewports(1, &VP);

	// 2D Factory ����
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &m_2DFactory)))
		return false;

	// 3D BackBuffer�� Surface�� ���´�.
	IDXGISurface* BackSurface = nullptr;

	m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&BackSurface));

	// 2D�� ����Ÿ���� ������ش� ����ϴ� BackBuffer�� 3D BackBuffer�� �������־ ����Ѵ�
	D2D1_RENDER_TARGET_PROPERTIES	props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));

	if (FAILED(m_2DFactory->CreateDxgiSurfaceRenderTarget(BackSurface, props, &m_2DTarget)))
		return false;

	SAFE_RELEASE(BackSurface);

	return true;
}

void CDevice::ClearRenderTarget(float ClearColor[4])
{
	// PageFliping ���� RenderTarget���� ������ ����۸� ������ ������ �о��ش�.
	// Ŭ��� ���������� ���� ����!!
	m_Context->ClearRenderTargetView(m_TargetView, ClearColor);
}

void CDevice::ClearDepthStencil(float Depth, unsigned char Stencil)
{
	// DepthView�� StencilView�� �о��ش�.
	m_Context->ClearDepthStencilView(m_DepthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, Depth, Stencil);
}

void CDevice::RenderStart()
{
	// Context�� �̿��� OM(OutputMerger, ��º��ձ�)�� �������� TargetView�� DepthView�� �����Ѵ�.
	m_Context->OMSetRenderTargets(1, &m_TargetView, m_DepthView);
}

void CDevice::Flip()
{
	// RenderManager�� ���� ����ۿ� �׷��� ȭ���� ��ǥ�� ���ۿ� Fliping�Ѵ�.
	m_SwapChain->Present(0, 0);
}
