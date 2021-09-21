#pragma once
#include <d3d9.h>

// bitmask value is important for data order in vertex structure
#define FVF D3DFVF_XYZ | D3DFVF_DIFFUSE

struct Vertex
{
	//position
	FLOAT x;
	FLOAT y;
	FLOAT z;

	D3DCOLOR color;

	Vertex(FLOAT _x, FLOAT _y, FLOAT _z) : x(_x), y(_y), z(_z), color(D3DCOLOR_XRGB(255, 255, 255)) {}
	Vertex(FLOAT _x, FLOAT _y, FLOAT _z, int r, int g, int b) : x(_x), y(_y), z(_z), color(D3DCOLOR_XRGB(r, g, b)) {}
};