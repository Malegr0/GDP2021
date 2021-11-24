#include "Material.h"
#include "WICTextureLoader.h"
#include "Utils.h"
#include <d3dcompiler.h>

using namespace DirectX;

INT Material::init(ID3D11Device* pD3DDevice, LPCWSTR textureName)
{
	//HRESULT hr = CreateWICTextureFromFile(pD3DDevice, textureName, &_pTexture);
	//CheckFailed(hr, 60);

	//_material.Ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
	//_material.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	//_material.Specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	//_material.Power = 1024.0f;
	//_material.Emissive = { 0.0f, 0.0f, 0.0f, 1.0f };

	INT error = createVertexShader(pD3DDevice);
	CheckError(error);

	error = createPixelShader(pD3DDevice);
	CheckError(error);

	error = createMatrixBuffer(pD3DDevice);
	CheckError(error);

	return 0;
}

void Material::render(ID3D11DeviceContext* pD3DDeviceContext, XMFLOAT4X4* pWorldMatrix, XMFLOAT4X4* pViewMatrix, XMFLOAT4X4* pProjectionMatrix)
{
	//// set texture
	//pD3DDevice->SetTexture(0, _pTexture);

	//// set sampler state
	//pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	//pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	//pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
	//pD3DDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_XRGB(255, 0, 255));
	//pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	//pD3DDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);

	//// set material
	//pD3DDevice->SetMaterial(&_material);

	// set up shader ressources
	setMatrixBuffer(pD3DDeviceContext, pWorldMatrix, pViewMatrix, pProjectionMatrix);

	// set up shader stages
	pD3DDeviceContext->VSSetShader(_pVertexShader, nullptr, 0);
	pD3DDeviceContext->PSSetShader(_pPixelShader, nullptr, 0);
	pD3DDeviceContext->IASetInputLayout(_pInputLayout);
}

void Material::deInit()
{
	//safeRelease<IDirect3DTexture9>(_pTexture);
	safeRelease<ID3D11Buffer>(_pMatrixBuffer);
	safeRelease<ID3D11VertexShader>(_pVertexShader);
	safeRelease<ID3D11PixelShader>(_pPixelShader);
	safeRelease<ID3D11InputLayout>(_pInputLayout);
}

INT Material::createVertexShader(ID3D11Device* pD3DDevice)
{
	// for compiling shader at runtime see https://docs.microsoft.com/en-us/windows/win32/api/d3dcompiler/nf-d3dcompiler-d3dcompilefromfile
	ID3DBlob* pCompiledShaderCode = nullptr;
	HRESULT hr = D3DReadFileToBlob(TEXT("ColorVertexShader.cso"), &pCompiledShaderCode);
	CheckFailed(hr, 60);

	hr = pD3DDevice->CreateVertexShader(pCompiledShaderCode->GetBufferPointer(), pCompiledShaderCode->GetBufferSize(), nullptr, &_pVertexShader);
	CheckFailed(hr, 62);

	INT error = createInputLayout(pD3DDevice, pCompiledShaderCode);
	CheckError(error);

	safeRelease<ID3DBlob>(pCompiledShaderCode);

	return 0;
}

INT Material::createPixelShader(ID3D11Device* pD3DDevice)
{
	ID3DBlob* pCompiledShaderCode = nullptr;
	HRESULT hr = D3DReadFileToBlob(TEXT("ColorPixelShader.cso"), &pCompiledShaderCode);
	CheckFailed(hr, 64);

	hr = pD3DDevice->CreatePixelShader(pCompiledShaderCode->GetBufferPointer(), pCompiledShaderCode->GetBufferSize(), nullptr, &_pPixelShader);
	CheckFailed(hr, 66);

	safeRelease<ID3DBlob>(pCompiledShaderCode);

	return 0;
}

INT Material::createInputLayout(ID3D11Device* pD3DDevice, ID3DBlob* pVertexShaderData)
{
	D3D11_INPUT_ELEMENT_DESC elements[4] = {};

	// position
	elements[0].SemanticName = "POSITION"; // https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics
	elements[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;

	// normal
	elements[1].SemanticName = "NORMAL";
	elements[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	elements[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	// uv
	elements[2].SemanticName = "TEXCOORD";
	elements[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	elements[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	// color
	elements[3].SemanticName = "COLOR";
	elements[3].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	elements[3].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	HRESULT hr = pD3DDevice->CreateInputLayout(elements, 4, pVertexShaderData->GetBufferPointer(), pVertexShaderData->GetBufferSize(), &_pInputLayout);
	CheckFailed(hr, 68)

		return 0;
}

INT Material::createMatrixBuffer(ID3D11Device* pD3DDevice)
{
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = sizeof(MatrixBuffer);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = pD3DDevice->CreateBuffer(&desc, nullptr, &_pMatrixBuffer);
	CheckFailed(hr, 61);

	return 0;
}

void Material::setMatrixBuffer(ID3D11DeviceContext* pD3DDeviceContext, XMFLOAT4X4* pWorldMatrix, XMFLOAT4X4* pViewMatrix, XMFLOAT4X4* pProjectionMatrix)
{
	D3D11_MAPPED_SUBRESOURCE data = {};
	HRESULT hr = pD3DDeviceContext->Map(_pMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	if (FAILED(hr)) return;

	XMMATRIX worldMatrix = XMLoadFloat4x4(pWorldMatrix);
	XMMATRIX viewMatrix = XMLoadFloat4x4(pViewMatrix);
	XMMATRIX projectionMatrix = XMLoadFloat4x4(pProjectionMatrix);

	XMMATRIX wvpMatrix = worldMatrix * viewMatrix * projectionMatrix;
	wvpMatrix = XMMatrixTranspose(wvpMatrix);

	MatrixBuffer* pMatrixBuffer = static_cast<MatrixBuffer*>(data.pData);
	XMStoreFloat4x4(&(pMatrixBuffer->worldViewProjectionMatrix), wvpMatrix);

	pD3DDeviceContext->Unmap(_pMatrixBuffer, 0);

	pD3DDeviceContext->VSSetConstantBuffers(0, 1, &_pMatrixBuffer);
}
