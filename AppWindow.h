
#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "PixelShader.h"
#include <Windows.h>
#include "Cube.h"
#include <vector>

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
private:
	SwapChain* m_swap_chain;
	std::vector<Cube*> cubeList;
	
	ConstantBuffer* m_cb;
	
	float deltaTime = 0.0f;
	PixelShader* m_ps;
	VertexShader* m_vs;

};