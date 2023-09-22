#include "Quad.h"



void Quad::onRender()
{
	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void Quad::onCreate(vertex v1, vertex v2, vertex v3, vertex v4)
{
	list[0] = v1;
	list[1] = v2;
	list[2] = v3;
	list[3] = v4;

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);
	GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	UINT size_shader = 0;
	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
}

void Quad::onDestroy()
{
	m_vb->release();
}
