#pragma once
#include <d3d11.h>
#include "PixelShader.h"
#include "VertexShader.h"
class SwapChain;
class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	void clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);
	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void setIndexBuffer(IndexBuffer* Index_buffer);
	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
	void setViewportSize(UINT width, UINT height);
	void setPixelShader(PixelShader* pixel_shader);
	void setVertexShader(VertexShader* vertex_shader);
	void setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* buffer);
	void setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* buffer);

	ID3D11DeviceContext* getDeviceContext();
	bool release();
	~DeviceContext();
private:
	ID3D11DeviceContext* m_device_context;
private:
	friend class ConstantBuffer;
};