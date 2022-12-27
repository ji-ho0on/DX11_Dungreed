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

	// Device 소멸 시 컴객체들은 모두 Release해줌
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

	// OR 연산으로 둘다 넣어줌
	Flag |= D3D11_CREATE_DEVICE_DEBUG;

#endif // _DEBUG

	D3D_FEATURE_LEVEL FLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL FLevelResult;

	// Device 생성 (Device, Context 생성)
	// 리턴타입 HRESULT : 값에 따라 어떤 에러가 발생했는지를 판단하기 위한 반환 값
	// FAILED 매크로를 통해 반환값을 체크해서 - 값이 나오면 에러로 판단
	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, Flag, &FLevel, 1,
		D3D11_SDK_VERSION, &m_Device, &FLevelResult, &m_Context)))
		return false;

	// SampleCount를 4개로 잡고, Check가 1보다 작으면 SampleCount를 1로 하여 SwapChain Description을 채운다.
	int	SampleCount = 4;

	UINT	Check = 0;
	m_Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM,	4, &Check);

	if (Check < 1)
		SampleCount = 1;

	// SwapChain 생성에 필요한 Description을 채워준다.
	DXGI_SWAP_CHAIN_DESC	SwapDesc = {};

	// 백버퍼를 어떻게 만들 것인가
	// 백버퍼의 가로 해상도
	SwapDesc.BufferDesc.Width = DeviceWidth;

	// 백버퍼의 가로 해상도
	SwapDesc.BufferDesc.Height = DeviceHeight;

	// 백버퍼의 픽셀이 어떤 포멧으로 만들어질 것인가
	// RGBA 8888 을 일반적으로 사용 (r, g , b, a 에 8비트씩)
	// UNORM = usigned로 된 0 ~ 1 사이로 정규화된 값
	SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// 갱신주기(수직동기화)
	SwapDesc.BufferDesc.RefreshRate.Numerator = 1;		// 분자
	SwapDesc.BufferDesc.RefreshRate.Denominator = 60;	// 분모

	// 창모드, 풀모드 전환 시 화면의 크기를 어떤식으로 스케일링 할 것인지
	SwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// 갱신시 어떤방식으로 할지
	SwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	// 백버퍼를 몇 개 사용할 지
	SwapDesc.BufferCount = 1;

	// 버퍼의 용도가 무엇인지 (랜더타겟에서 출력용도로 사용)
	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// 뷰포트(출력을 위한 얇은 막)가 윈도우 창의 클라이언트 영역을 덮어서 출력을 함
	SwapDesc.OutputWindow = hWnd;

	// Anti-Aliasing 기능을 지원? 멀티샘플링 느려서 안씀 (나중에 쉐이더에서 직접 구현해서 사용)
	SwapDesc.SampleDesc.Quality = 0;			// 사용 안함, 나중에 알파블랜딩 할 떄 샘플링카운트를 높여서 해결하기 위해 사용할 듯
	SwapDesc.SampleDesc.Count = SampleCount;	// 안쓰지만 안쓰는 걸로 하나 필요함, 알파블랜딩을 위해 샘플카운트를 4개 사용

	// 창모드 인지 풀스크린인지 true false로 설정
	SwapDesc.Windowed = WindowMode;

	// 스왑이펙트
	SwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;



	// SwapChain 생성
	IDXGIDevice* DXGIDevice = nullptr;
	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&DXGIDevice);

	IDXGIAdapter* Adapter = nullptr;
	DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&Adapter);

	IDXGIFactory* Factory = nullptr;
	Adapter->GetParent(__uuidof(IDXGIFactory), (void**)&Factory);

	if (FAILED(Factory->CreateSwapChain(m_Device, &SwapDesc, &m_SwapChain)))
	{
		// SwapChain 생성을 위해 선언 했던 컴 객체들 Release
		SAFE_RELEASE(DXGIDevice);
		SAFE_RELEASE(Adapter);
		SAFE_RELEASE(Factory);
		return false;
	}

	SAFE_RELEASE(DXGIDevice);
	SAFE_RELEASE(Adapter);
	SAFE_RELEASE(Factory);

	// SwapChain이 만들어 졌다면 SwapChain이 가지고 있는 백버퍼를 얻어온다.
	ID3D11Texture2D* BackBuffer = nullptr;
	if (FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer)))
		return false;

	// 백버퍼와 연결된 RenderTargetView를 생성한다.
	if (FAILED(m_Device->CreateRenderTargetView(BackBuffer, nullptr, &m_TargetView)))
		return false;

	// TargetView 생성을 위해 선언했던 BackBuffer 컴객체 Release
	SAFE_RELEASE(BackBuffer);


	// DepthBuffer 생성을 위한 Description을 채워준다.
	D3D11_TEXTURE2D_DESC	DepthDesc = {};
	DepthDesc.Width = DeviceWidth;
	DepthDesc.Height = DeviceHeight;

	DepthDesc.ArraySize = 1;

	// 깊이갚으로 3바이트를 쓰겠다는 것, 스탠실 버퍼에 8비트
	DepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// 깊이 스텐실 용도로 묶을 것
	DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	// 용도
	// 비디오 메모리를 이용함, 갱신 가능
	DepthDesc.Usage = D3D11_USAGE_DEFAULT;

	DepthDesc.SampleDesc.Count = SampleCount;
	DepthDesc.SampleDesc.Quality = 0;

	DepthDesc.MipLevels = 1;

	// DepthBuffer를 생성한다.
	ID3D11Texture2D* DepthBuffer = nullptr;

	if (FAILED(m_Device->CreateTexture2D(&DepthDesc, nullptr, &DepthBuffer)))
		return false;

	if (FAILED(m_Device->CreateDepthStencilView(DepthBuffer, nullptr, &m_DepthView)))
		return false;

	// DepthBuffer 생성을 위해 선언한 컴객체 Release
	SAFE_RELEASE(DepthBuffer);


	// ViewPort를 생성한다.
	D3D11_VIEWPORT VP = {};

	// TopLeft를 지정하면 지정한 위치부터 화면이 출력됨.
	//VP.TopLeftX = 100.f;
	//VP.TopLeftY = 100.f;

	// 출력될 화면의 크기를 지정
	// 현재 Device 크기로 지정
	VP.Width = (float)DeviceWidth;
	VP.Height = (float)DeviceHeight;

	// 최대 깊이는 1로 지정
	VP.MaxDepth = 1.f;

	// Context를 이용해 ViewPort를 지정한다.
	m_Context->RSSetViewports(1, &VP);

	// 2D Factory 생성
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &m_2DFactory)))
		return false;

	// 3D BackBuffer의 Surface를 얻어온다.
	IDXGISurface* BackSurface = nullptr;

	m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&BackSurface));

	// 2D용 렌더타겟을 만들어준다 출력하는 BackBuffer를 3D BackBuffer로 지정해주어서 출력한다
	D2D1_RENDER_TARGET_PROPERTIES	props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));

	if (FAILED(m_2DFactory->CreateDxgiSurfaceRenderTarget(BackSurface, props, &m_2DTarget)))
		return false;

	SAFE_RELEASE(BackSurface);

	return true;
}

void CDevice::ClearRenderTarget(float ClearColor[4])
{
	// PageFliping 전에 RenderTarget으로 지정된 백버퍼를 지정된 색으로 밀어준다.
	// 클리어를 검은색으로 하지 말것!!
	m_Context->ClearRenderTargetView(m_TargetView, ClearColor);
}

void CDevice::ClearDepthStencil(float Depth, unsigned char Stencil)
{
	// DepthView와 StencilView를 밀어준다.
	m_Context->ClearDepthStencilView(m_DepthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, Depth, Stencil);
}

void CDevice::RenderStart()
{
	// Context를 이용해 OM(OutputMerger, 출력병합기)에 랜더링할 TargetView와 DepthView를 지정한다.
	m_Context->OMSetRenderTargets(1, &m_TargetView, m_DepthView);
}

void CDevice::Flip()
{
	// RenderManager를 통해 백버퍼에 그려진 화면을 주표면 버퍼와 Fliping한다.
	m_SwapChain->Present(0, 0);
}
