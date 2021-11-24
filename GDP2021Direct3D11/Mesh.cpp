#include "Mesh.h"
#include "Utils.h"
#include "Vertex.h"
#include <DirectXMath.h>

using namespace DirectX;

INT Mesh::init(ID3D11Device* pD3DDevice)
{
	INT error = initVertexBuffer(pD3DDevice);
	CheckError(error);

	error = initIndexBuffer(pD3DDevice);
	CheckError(error);

	XMStoreFloat4x4(&_worldMatrix, XMMatrixIdentity());

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

	XMStoreFloat4x4(&_worldMatrix, scaling * rotation * translation);
}

void Mesh::render(ID3D11DeviceContext* pD3DDeviceContext)
{
	// set mesh data
	static UINT offset = 0;
	pD3DDeviceContext->IASetVertexBuffers(0, 1, &_pVertexBuffer, &_vertexStride, &offset);
	pD3DDeviceContext->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	pD3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// draw with vertex and index buffer
	pD3DDeviceContext->DrawIndexed(_indexCount, 0, 0);
}

void Mesh::deInit()
{
	safeRelease<ID3D11Buffer>(_pVertexBuffer);
	safeRelease<ID3D11Buffer>(_pIndexBuffer);
}

INT Mesh::initVertexBuffer(ID3D11Device* pD3DDevice)
{
	_vertexCount = 4;
	_vertexStride = sizeof(Vertex);

	Vertex vertices[] = {
		// quad with normal & uvs
		vertices[0] = Vertex(-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f), // left-top
		vertices[1] = Vertex(0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f), // right-top
		vertices[2] = Vertex(0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f), // right-bottom
		vertices[3] = Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f) // left-bottom
	};

	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = _vertexCount * _vertexStride; // byte length of buffer
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // buffer type
	desc.Usage = D3D11_USAGE_IMMUTABLE;	// how it is used, https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_usage

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = vertices;

	HRESULT hr = pD3DDevice->CreateBuffer(&desc, &data, &_pVertexBuffer);
	CheckFailed(hr, 30);

	return 0;
}

INT Mesh::initIndexBuffer(ID3D11Device* pD3DDevice)
{
	_indexCount = 6;

	WORD indices[] = {
		//quad
		//primitive 1
		0, 1, 2,

		//primitive 2
		0, 2, 3
	};

	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = _indexCount * sizeof(WORD); // byte length of buffer
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER; // buffer type
	desc.Usage = D3D11_USAGE_IMMUTABLE;	// how it is used

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = indices;

	HRESULT hr = pD3DDevice->CreateBuffer(&desc, &data, &_pIndexBuffer);
	CheckFailed(hr, 32);

	return 0;
}
