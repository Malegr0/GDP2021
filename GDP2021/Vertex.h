#pragma once
#include <d3d9.h>

// bitmask value is important for data order in vertex structure
#define FVF D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1

struct Vertex
{
	//position
	FLOAT x;
	FLOAT y;
	FLOAT z;

	//color
	D3DCOLOR color;

	//uv
	FLOAT u;
	FLOAT v;

	Vertex(FLOAT _x, FLOAT _y, FLOAT _z) : x(_x), y(_y), z(_z), color(D3DCOLOR_XRGB(255, 255, 255)), u(0.0f), v(0.0f) {}
	Vertex(FLOAT _x, FLOAT _y, FLOAT _z, int r, int g, int b) : x(_x), y(_y), z(_z), color(D3DCOLOR_XRGB(r, g, b)), u(0.0f), v(0.0f) {}
	Vertex(FLOAT _x, FLOAT _y, FLOAT _z, D3DCOLOR _color) : x(_x), y(_y), z(_z), color(_color), u(0.0f), v(0.0f) {}
	Vertex(FLOAT _x, FLOAT _y, FLOAT _z, FLOAT _u, FLOAT _v) : x(_x), y(_y), z(_z), color(0xffffffff), u(_u), v(_v) {}
};