#include "AppWindow.h"


#include <random>     

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	
	std::random_device rd;
	std::uniform_int_distribution<int> distint(1, 10);
	std::uniform_real_distribution<float> distfloat(-1.0f, 1.0f);
	Window::onCreate();
	InputSystem::initialize();
	BaseComponentSystem::initialize();
	
	InputSystem::getInstance()->addListener(this);
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	EngineTime::initialize();
	RECT rc = this->getClientWindowRect();
	SceneCameraHandler::initialize(rc.right - rc.left, rc.bottom - rc.top);
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	UIManager::initialize(m_hwnd);
	GameObjectManager::initialize();



	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	
	GraphicsEngine::get()->releaseCompiledShader();
	

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);
	
	InputSystem::getInstance()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));

}

void AppWindow::onUpdate()
{
	
	InputSystem::getInstance()->update();
	
	
	
	float colors[4];
	colors[0] = clear_color.x;
	colors[1] = clear_color.y;
	colors[2] = clear_color.z;
	colors[3] = clear_color.w;
	
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(m_swap_chain,colors[0], colors[1], colors[2], colors[3]);

	RECT rc = getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	
	SceneCameraHandler::getInstance()->update();

	
	BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAllComponents();
	GameObjectManager::getInstance()->updateAll();
	GameObjectManager::getInstance()->renderAll(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);

	

	
	
	
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW

	EngineTime::LogFrameEnd();

	// Rendering
	UIManager::getInstance()->drawAllUI();
	
	// (Your code calls swapchain's Present() function)
	m_swap_chain->present(true);
	
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	
	for (int i = 0; i < cubeList.size(); i++) {
		cubeList[i]->onDestroy();
	}
	GameObjectManager::getInstance()->destroy();
	m_swap_chain->release();

	
	UIManager::getInstance()->destroy();
	InputSystem::getInstance()->destroy();
	GraphicsEngine::get()->release();
}

void AppWindow::onKeyUp(int key)
{
	if (key == 'W') {
		isForward = false;
	}
	else if (key == 'S') {
		isBackward = false;
	}
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W') {
		isForward = true;
	}
	else if (key == 'S') {
		isBackward = true;
	}
}

void AppWindow::onMouseMove(const Point deltaPos)
{
	

}

void AppWindow::onLeftMouseDown(const Point deltaPos)
{
}

void AppWindow::onLeftMouseUp(const Point deltaPos)
{
}

void AppWindow::onRightMouseDown(const Point deltaPos)
{
}

void AppWindow::onRightMouseUp(const Point deltaPos)
{
}
