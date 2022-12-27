#pragma once

#include "EngineInfo.h"

class CDevice
{
private:
	// 앞에 I가 붙으면 COM 객체이다. (Component Object Model)
	// COM 객체는 GUID를 가지고 있음(128비트로 구성된 고유 ID값)
	ID3D11Device*			m_Device;	// 주로 버퍼(임시 저장 공간) 생성 용도로 활용, 비디오 메모리에 버퍼를 만들어 저장
	ID3D11DeviceContext*	m_Context;	// 실제 랜더링에 필요한 명령을 내려주는 역할
	IDXGISwapChain*			m_SwapChain;	// 백버퍼를 만들고 깊이버퍼를 만듬, page flip을 지원 

	ID3D11RenderTargetView* m_TargetView;	// 지정한 버퍼에 랜더링할 수 있는 타겟
	ID3D11DepthStencilView* m_DepthView;	// 깊이

	// 출력을 위한 버퍼 3종
	// 백 버퍼 : 화면에 출력하기 위한 픽셀을 저장하기 위한 버퍼
	// 깊이 버퍼 : 각각의 픽셀들 마다 가까이 있는지를 판단하기 위한 깊이값(0 ~ 1)을 저장하기 위한 버퍼
	// 스텐실 버퍼 : 각각의 픽셀들마다 원하는 값을 저장해 특수효과를 만들기 위한 버퍼 (꼭 필요한 곳에는 쓰는데 잘 안씀)

	// 윈도우 핸들과 Resolution을 가지고 있음
	HWND					m_hWnd;
	Resolution				m_RS;

private:
	ID2D1RenderTarget*		m_2DTarget;
	ID2D1RenderTarget*		m_2DTargetWorld;
	ID2D1Factory*			m_2DFactory;

public:
	ID2D1RenderTarget* Get2DTarget()	const
	{
		return m_2DTarget;
	}

	ID2D1RenderTarget* Get2DWorldTarget()	const
	{
		return m_2DTargetWorld;
	}

	ID2D1Factory* Get2DFactory()	const
	{
		return m_2DFactory;
	}

	Resolution GetResolution()	const
	{
		return m_RS;
	}

	ID3D11Device* GetDevice()	const
	{
		return m_Device;
	}

	ID3D11DeviceContext* GetContext()	const
	{
		return m_Context;
	}

	IDXGISwapChain* GetSwapChain()	const
	{
		return m_SwapChain;
	}

	Vector2 GetResolutionRatio()	const;

public:
	bool Init(HWND hWnd, unsigned int DeviceWidth, unsigned int DeviceHeight, bool WindowMode);
	void ClearRenderTarget(float ClearColor[4]);
	void ClearDepthStencil(float Depth, unsigned char Stencil);
	void RenderStart();
	void Flip();

	DECLARE_SINGLE(CDevice)
};

