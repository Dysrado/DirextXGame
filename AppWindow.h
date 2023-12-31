
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
#include "InputListener.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"
#include "UIManager.h"
#include "GameObjectManager.h"
#include <reactphysics3d/reactphysics3d.h>

#include "PhysicsSystem.h"
#include "BaseComponentSystem.h"
using namespace reactphysics3d;


class AppWindow : public Window, public InputListener
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
	Cube* cube1;
	
	ConstantBuffer* m_cb;
	
	float deltaTime = 0.0f;
	PixelShader* m_ps;
	VertexShader* m_vs;

	bool isForward = false;
	bool isBackward = false;
	bool show_demo_window;
	bool isPaused = false;
	ImVec4 clear_color = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);


	// Inherited via InputListener
	virtual void onKeyUp(int key) override;

	virtual void onKeyDown(int key) override;

	virtual void onMouseMove(const Point deltaPos) override;

	virtual void onLeftMouseDown(const Point deltaPos) override;

	virtual void onLeftMouseUp(const Point deltaPos) override;

	virtual void onRightMouseDown(const Point deltaPos) override;

	virtual void onRightMouseUp(const Point deltaPos) override;

};