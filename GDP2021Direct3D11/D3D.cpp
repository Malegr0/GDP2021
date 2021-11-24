#include "D3D.h"
#include "Utils.h"

INT D3D::init(HWND hWnd, UINT width, UINT height, BOOL isFullscreen)
{
	// 1. get Direct3D 9 interface (interface = connection to api)
	IDirect3D9* pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (pD3D9 == nullptr) return 20;

	// 2. check fixed function pipeline hardware support
	D3DCAPS9 d3dCaps = {};
	UINT adapter = D3DADAPTER_DEFAULT;	// which graphic card will be used if multiple are installed	// graphic card index
	D3DDEVTYPE devType = D3DDEVTYPE_HAL;	// device for rendering (HAL = Hardware Abstraction LAyer -> Graphic Card)
	HRESULT hr = pD3D9->GetDeviceCaps(adapter, devType, &d3dCaps);
	CheckFailed(hr, 22);

	DWORD vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;	// fallback, imitate fixed function pipeline by api
	if (d3dCaps.VertexProcessingCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)	// check for hardware support
		vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;	// graphic card support for fixed function pipeline

	// 3. set up presentation parameters
	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.hDeviceWindow = hWnd;	// target window
	d3dpp.Windowed = !isFullscreen;	// window mode or exclusive fullscreen
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;	// Alpha - Red - Green - Blue - each 8Bit
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// what happens with the front buffer after swapping

	// 4. create Direct3D 9 device (device = connection to pipeline)
	hr = pD3D9->CreateDevice(
		adapter,
		devType,
		hWnd,
		vertexProcessing,	// optional flags, e.g. vertex processing type
		&d3dpp,
		&_pD3DDevice
	);
	CheckFailed(hr, 24);

	// 5. tidy up
	safeRelease<IDirect3D9>(pD3D9);

	return 0;
}

void D3D::beginScene(D3DCOLOR backgroundColor)
{
	// clear the backbuffer with a solid color
	_pD3DDevice->Clear(
		0, nullptr,	// regions to clear
		D3DCLEAR_TARGET,	// what buffers to clear - target -> back buffer
		backgroundColor, 1.0f, 0	// clear values - back buffer, depth buffer, stencil buffer
	);
	_pD3DDevice->BeginScene();
}

void D3D::endScene()
{
	_pD3DDevice->EndScene();

	// swap front with back buffer
	_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

void D3D::deInit()
{
	safeRelease<IDirect3DDevice9>(_pD3DDevice);
}
