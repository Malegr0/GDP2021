#pragma once
#include <d3d9.h>

// bitmask value is important for data order in vertex structure
#define FVF D3DFVF_XYZ

struct Vertex
{
	//position
	FLOAT x;
	FLOAT y;
	FLOAT z;

	Vertex(FLOAT _x, FLOAT _y, FLOAT _z) : x(_x), y(_y), z(_z) {}
};