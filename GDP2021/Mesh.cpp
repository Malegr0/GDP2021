#include "Mesh.h"
#include "Utils.h"
#include "Vertex.h"
#include <DirectXMath.h>

using namespace DirectX;

INT Mesh::init(IDirect3DDevice9* pD3DDevice)
{
	INT error = initVertexBuffer(pD3DDevice);
	CheckError(error);

	error = initIndexBuffer(pD3DDevice);
	CheckError(error);

	XMMATRIX identity = XMMatrixIdentity();
	XMFLOAT4X4 worldMatrix;
	XMStoreFloat4x4(&worldMatrix, identity);
	_worldMatrix = *reinterpret_cast<D3DMATRIX*>(&worldMatrix);

	return 0;
}

void Mesh::update(FLOAT dt)
{
	static FLOAT posX = 0.0f;
	static FLOAT posY = 0.0f;
	static FLOAT posZ = 0.0f;
	static FLOAT rot = 0.0f;
	rot += XM_PI * 0.1f * dt;

	FLOAT move = dt;

	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('A') & 0x8000)) posX -= move;
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('D') & 0x8000)) posX += move;
	if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000)) posY += move;
	if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000)) posY -= move;
	if ((GetAsyncKeyState(VK_ADD) & 0x8000) || (GetAsyncKeyState('Q') & 0x8000)) posZ -= move;
	if ((GetAsyncKeyState(VK_SUBTRACT) & 0x8000) || (GetAsyncKeyState('E') & 0x8000)) posZ += move;

	XMMATRIX translation = XMMatrixTranslation(posX, posY, posZ);
	XMMATRIX rotation = XMMatrixRotationRollPitchYaw(0.5f, 0.0f, rot);
	XMMATRIX scaling = XMMatrixScaling(1.0f, 1.0f, 1.0f);

	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&_worldMatrix), scaling * rotation * translation);
}

void Mesh::render(IDirect3DDevice9* pD3DDevice)
{
	// set world transformation matrix
	pD3DDevice->SetTransform(D3DTS_WORLD, &_worldMatrix);

	// set flexible vertex format
	pD3DDevice->SetFVF(FVF);

	// set vertex buffer source
	pD3DDevice->SetStreamSource(0, _pVertexBuffer, 0, _vertexStride);

	// draw with vertex buffer only
	//pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, _vertexCount / 3);
	//pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, _vertexCount - 2);
	//pD3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, _vertexCount - 2);

	// draw with vertex and index buffer
	pD3DDevice->SetIndices(_pIndexBuffer);
	pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _vertexCount, 0, _indexCount / 3);
}

void Mesh::deInit()
{
	safeRelease<IDirect3DVertexBuffer9>(_pVertexBuffer);
	safeRelease<IDirect3DIndexBuffer9>(_pIndexBuffer);
}

INT Mesh::initVertexBuffer(IDirect3DDevice9* pD3DDevice)
{
	_vertexCount = 4;
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
	//vertices[0] = Vertex(-0.5f, 0.5f, 0.0f);	// left-top
	//vertices[1] = Vertex(0.5f, 0.5f, 0.0f);		// right-top
	//vertices[2] = Vertex(0.5f, -0.5f, 0.0f);	// right-bottom

	// primitive 2
	//vertices[3] = Vertex(-0.5f, 0.5f, 0.0f);	// left-top
	//vertices[4] = Vertex(0.5f, -0.5f, 0.0f);	// right-bottom
	//vertices[5] = Vertex(-0.5f, -0.5f, 0.0f);	// left-bottom

	// quad with trianglestrip
	//vertices[0] = Vertex(-0.5f, 0.5f, 0.0f);	// left-top
	//vertices[1] = Vertex(0.5f, 0.5f, 0.0f);		// right-top
	//vertices[2] = Vertex(-0.5f, -0.5f, 0.0f);	// left-bottom
	//vertices[3] = Vertex(0.5f, -0.5f, 0.0f);	// right-bottom

	// quad with trianglefan or with trianglelist with index buffer
	//vertices[0] = Vertex(-0.5f, 0.5f, 0.0f, 255, 0, 0);	// left-top
	//vertices[1] = Vertex(0.5f, 0.5f, 0.0f, 0, 255, 0);		// right-top
	//vertices[2] = Vertex(0.5f, -0.5f, 0.0f, 255, 0, 255);	// right-bottom
	//vertices[3] = Vertex(-0.5f, -0.5f, 0.0f, 0, 0, 255);	// left-bottom
	//vertices[4] = Vertex(0.0f, 0.0f, 0.0f, 255, 255, 255);

	// quad with uvs
	//vertices[0] = Vertex(-0.5f, 0.5f, 0.0f, 0.0f, 0.0f); // left-top
	//vertices[1] = Vertex(0.5f, 0.5f, 0.0f, 1.0f, 0.0f); // right-top
	//vertices[2] = Vertex(0.5f, -0.5f, 0.0f, 1.0f, 1.0f); // right-bottom
	//vertices[3] = Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f); // left-bottom
	//vertices[4] = Vertex(0.0f, 0.0f, 0.0f, 0.5f, 0.5f); // left-bottom

	// quad with normal & uvs
	vertices[0] = Vertex(-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f); // left-top
	vertices[1] = Vertex(0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f); // right-top
	vertices[2] = Vertex(0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f); // right-bottom
	vertices[3] = Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f); // left-bottom

	hr = _pVertexBuffer->Unlock();
	CheckFailed(hr, 34);

	vertices = nullptr;

	return 0;
}

INT Mesh::initIndexBuffer(IDirect3DDevice9* pD3DDevice)
{
	_indexCount = 6;

	HRESULT hr = pD3DDevice->CreateIndexBuffer(_indexCount * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &_pIndexBuffer, nullptr);
	CheckFailed(hr, 36);

	WORD* indices = nullptr;
	hr = _pIndexBuffer->Lock(0, 0, reinterpret_cast<void**>(&indices), 0);
	CheckFailed(hr, 38);

	// quad
	// primitive 1
	indices[0] = 0; indices[1] = 1; indices[2] = 2;

	// primitive 2
	indices[3] = 0; indices[4] = 2; indices[5] = 3;
	//indices[6] = 1; indices[7] = 2; indices[8] = 4;
	//indices[9] = 2; indices[10] = 3; indices[11] = 4;

	hr = _pIndexBuffer->Unlock();
	CheckFailed(hr, 39);

	indices = nullptr;

	return 0;
}
