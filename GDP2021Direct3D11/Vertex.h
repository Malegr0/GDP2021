#pragma once
#include <DirectXMath.h>

using namespace DirectX;

struct Vertex
{
	XMFLOAT3 position;
	XMFLOAT3 normal;
	XMFLOAT2 uv;
	XMFLOAT4 color;

	Vertex(FLOAT x, FLOAT y, FLOAT z) : position(x, y, z), color(1.0f, 1.0f, 1.0f, 1.0f), uv(0.0f, 0.0f), normal(0.0f, 0.0f, 0.0f) {}
	Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT r, FLOAT g, FLOAT b) : position(x, y, z), color(r, g, b, 1.0f), uv(0.0f, 0.0f), normal(0.0f, 0.0f, 0.0f) {}
	Vertex(FLOAT x, FLOAT y, FLOAT z, XMFLOAT4 &_color) : position(x, y, z), color(_color), uv(0.0f, 0.0f), normal(0.0f, 0.0f, 0.0f) {}
	Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT u, FLOAT v) : position(x, y, z), color(1.0f, 1.0f, 1.0f, 1.0f), uv(u, v), normal(0.0f, 0.0f, 0.0f) {}
	Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT nx, FLOAT ny, FLOAT nz, FLOAT u, FLOAT v) : position(x, y, z), color(1.0f, 1.0f, 1.0f, 1.0f), uv(0.0f, 0.0f), normal(nx, ny, nz) {}
};