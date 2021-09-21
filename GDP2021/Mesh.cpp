#include "Mesh.h"
#include "Utils.h"
#include "Vertex.h"

INT Mesh::init(IDirect3DDevice9* pD3DDevice)
{
	INT error = initVertexBuffer(pD3DDevice);
	CheckError(error);

	error = initIndexBuffer(pD3DDevice);
	CheckError(error);

	return 0;
}

void Mesh::update(FLOAT dt)
{
}

void Mesh::render(IDirect3DDevice9* pD3DDevice)
{
	// set flexible vertex format
	pD3DDevice->SetFVF(FVF);

	// set vertex buffer source
	pD3DDevice->SetStreamSource(0, _pVertexBuffer, 0, _vertexStride);

	// draw with vertex buffer only
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, _vertexCount / 3);
}

void Mesh::deInit()
{
	safeRelease<IDirect3DVertexBuffer9>(_pVertexBuffer);
	safeRelease<IDirect3DIndexBuffer9>(_pIndexBuffer);
}

INT Mesh::initVertexBuffer(IDirect3DDevice9* pD3DDevice)
{
	_vertexCount = 6;
	_vertexStride = sizeof(Vertex);

	HRESULT hr = pD3DDevice->CreateVertexBuffer(
		_vertexCount * _vertexStride,	// byte length of buffer
		D3DUSAGE_WRITEONLY,		// write and/or read buffer
		FVF,	// FVF -> Flexible Vertex Format
		D3DPOOL_MANAGED,	// managed memory management
		&_pVertexBuffer, nullptr	// object itself, last argument isnt used
	);
	CheckFailed(hr, 30);

	Vertex* vertices = nullptr;
	hr = _pVertexBuffer->Lock(0, 0, reinterpret_cast<void**>(&vertices), 0);
	CheckFailed(hr, 32);

	// triangle
	//vertices[0] = Vertex(0.0f, 0.5f, 0.0f);
	//vertices[1] = Vertex(0.5f, -0.5f, 0.0f);
	//vertices[2] = Vertex(-0.5f, -0.5f, 0.0f);

	// quad without index buffer
	// primitive 1
	vertices[0] = Vertex(-0.5f, 0.5f, 0.0f);	// left-top
	vertices[1] = Vertex(0.5f, 0.5f, 0.0f);		// right-top
	vertices[2] = Vertex(0.5f, -0.5f, 0.0f);	// right-bottom

	// primitive 2
	vertices[3] = Vertex(-0.5f, 0.5f, 0.0f);	// left-top
	vertices[4] = Vertex(0.5f, -0.5f, 0.0f);	// right-bottom
	vertices[5] = Vertex(-0.5f, -0.5f, 0.0f);	// left-bottom

	hr = _pVertexBuffer->Unlock();
	CheckFailed(hr, 34);

	vertices = nullptr;

	return 0;
}

INT Mesh::initIndexBuffer(IDirect3DDevice9* pD3DDevice)
{
	return 0;
}
