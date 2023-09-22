#pragma once
#include "VertexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

class Quad
{
public:
	struct vec3
	{
		float x, y, z;
	};

	struct vertex
	{
		vec3 position;
	};
	VertexBuffer* m_vb;
	vertex list[4];


	void onCreate(vertex v1, vertex v2, vertex v3, vertex v4);
	void onRender();
	void onDestroy();
	
};

