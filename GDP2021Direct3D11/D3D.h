#pragma once
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

class D3D
{
public:
	INT init(HWND hWnd, UINT width, UINT height, BOOL isFullscreen);
	void beginScene(FLOAT red, FLOAT green, FLOAT blue);
	void endScene();
	void deInit();

	ID3D11Device* getDevice() { return _pD3DDevice; }
	ID3D11DeviceContext* getDeviceContext() { return _pD3DDeviceContext; }

private:
	ID3D11Device* _pD3DDevice = nullptr; // creating objects, e.g. vertex buffer
	ID3D11DeviceContext* _pD3DDeviceContext = nullptr; // handling render pipeline, e.g. set pipeline resources or draw call
	IDXGISwapChain* _pDXGISwapChain = nullptr; // hold references to front- and backbuffer and swap them
	ID3D11RenderTargetView* _pRenderTargetView = nullptr; // describe a target the render pipeline should render on, e.g. backbuffer
};
