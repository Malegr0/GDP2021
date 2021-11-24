#include "D3D.h"
#include "Utils.h"
#include <xutility>
#include <combaseapi.h>

INT D3D::init(HWND hWnd, UINT width, UINT height, BOOL isFullscreen)
{
	// 1. describe creation process
	DXGI_SWAP_CHAIN_DESC desc = {};
	desc.OutputWindow = hWnd;
	desc.Windowed = !isFullscreen;
	desc.BufferCount = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	desc.SampleDesc.Count = 1; // this MSAA count should be set to at least 1

	// 2. create device, device context & swap chain
	D3D_FEATURE_LEVEL supportedFeatureLevels[] = {
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	D3D_FEATURE_LEVEL choosenFeatureLevel = {};

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr, // use primary graphic card
		D3D_DRIVER_TYPE_HARDWARE, nullptr,
		0,
		supportedFeatureLevels, std::size(supportedFeatureLevels), // which D3D versions are supported by the application
		D3D11_SDK_VERSION,
		&desc, &_pDXGISwapChain, &_pD3DDevice, &choosenFeatureLevel, &_pD3DDeviceContext
	);
	CheckFailed(hr, 20);

	// 3. create render target view
	ID3D11Texture2D* pBackBufferTexture = nullptr;
	//hr = _pDXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBufferTexture));
	hr = _pDXGISwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBufferTexture));
	CheckFailed(hr, 22);

	hr = _pD3DDevice->CreateRenderTargetView(pBackBufferTexture, nullptr, &_pRenderTargetView);
	CheckFailed(hr, 24);

	safeRelease<ID3D11Texture2D>(pBackBufferTexture);

	// 6. set up view port
	_viewPort.TopLeftX = 0.0f;
	_viewPort.TopLeftY = 0.0f;
	_viewPort.Width = width;
	_viewPort.Height = height;
	_viewPort.MinDepth = 0.0f;
	_viewPort.MaxDepth = 1.0f;

	// 7. set up render pipeline
	_pD3DDeviceContext->OMSetRenderTargets(1, &_pRenderTargetView, nullptr);
	_pD3DDeviceContext->RSSetViewports(1, &_viewPort);

	return 0;
}

void D3D::beginScene(FLOAT red, FLOAT green, FLOAT blue)
{
	// clear the back buffer with a solid color
	const FLOAT backgroundColor[] = { red, green, blue, 1.0f };
	_pD3DDeviceContext->ClearRenderTargetView(_pRenderTargetView, backgroundColor);

	//_pD3DDevice->Clear(
	//    0, nullptr, // regions to clear
	//    D3DCLEAR_TARGET, // what buffers to clear - target -> back buffer
	//    backgroundColor, 1.0f, 0 // clear values - back buffer, depth buffer, stencil buffer
	//);

}

void D3D::endScene()
{
	// swap front with back buffer
	_pDXGISwapChain->Present(0, 0);
}

void D3D::deInit()
{
	safeRelease<ID3D11RenderTargetView>(_pRenderTargetView);
	safeRelease<ID3D11Device>(_pD3DDevice);
	safeRelease<ID3D11DeviceContext>(_pD3DDeviceContext);
	safeRelease<IDXGISwapChain>(_pDXGISwapChain);
}
