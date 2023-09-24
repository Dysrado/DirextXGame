#pragma once
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "PixelShader.h"
#include <Windows.h>

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
		vec3 position1;
		vec3 color;
		vec3 color1;
	};
	__declspec(align(16))
		struct constant
	{
		float m_angle;
	};
	VertexBuffer* m_vb;
	
	vertex list[4];


	void onCreate(vertex v1, vertex v2, vertex v3, vertex v4);
	void onRender(ConstantBuffer* m_cb);
	void onDestroy();
private:
	PixelShader* m_ps;
	VertexShader* m_vs;
	
};

