#pragma once
#include <d3d9.h>

class D3D 
{
public:
	INT init(HWND hWnd, UINT width, UINT height, BOOL isFullscreen);
	void beginScene(D3DCOLOR backgroundColor);
	void endScene();
	void deInit();

	IDirect3DDevice9* getDevice() { return _pD3DDevice; }

private:
	IDirect3DDevice9* _pD3DDevice = nullptr; // COM object (Component Object Model)
};