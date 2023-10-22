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
	std::uniform_real_distribution<float> distfloat(-0.5f, 0.5f);
	Window::onCreate();
	InputSystem::initialize();

	InputSystem::getInstance()->addListener(this);
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	EngineTime::initialize();
	RECT rc = this->getClientWindowRect();
	SceneCameraHandler::initialize(rc.right - rc.left, rc.bottom - rc.top);
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	for (int i = 0; i < 3; i++) {
		
		Cube* cube;
		cube = new Cube("Cube " + i, shader_byte_code, size_shader);
		cube->setAnimSpeed(0);
		cube->SetScale(Vector3D(1,1,1));
		switch (i) {
			case 0:
				cube->SetPosition(Vector3D(-1.5, 1, -3.0f));
				break;
			case 1:
				cube->SetPosition(Vector3D(0, 1, 0));
				break;
			case 2:
				cube->SetPosition(Vector3D(2.6, 1, 2.0f));
				break;
		}
		//cube->SetPosition(Vector3D(1,1,0));
		//cube->SetPosition(distfloat(rd), distfloat(rd), distfloat(rd));
		cubeList.push_back(cube);
	}

	
	
	cube1 = new Cube("Plane", shader_byte_code, size_shader);
	cube1->setAnimSpeed(0);
	cube1->SetScale(Vector3D(6, 0.1, 6));
	cube1->SetPosition(Vector3D(0, 0, 0));
	//isForward = true;
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
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(m_swap_chain, 0.2f, 0.2f, 0.2f, 1);

	RECT rc = getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	
	SceneCameraHandler::getInstance()->update();

	
	if (isForward && !isBackward ) {
		for (int i = 0; i < cubeList.size(); i++) {
			cubeList[i]->addMovement(0, EngineTime::getDeltaTime());
		}
	}
	else if (!isForward && isBackward) {
		for (int i = 0; i < cubeList.size(); i++) {
			cubeList[i]->addMovement(1, EngineTime::getDeltaTime());
		}
	}

	for (int i = 0; i < cubeList.size(); i++) {
		cubeList[i]->onUpdate(EngineTime::getDeltaTime());
		cubeList[i]->onRender(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);
	}

	
	cube1->onUpdate(EngineTime::getDeltaTime());
	cube1->onRender(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);
	
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW

	m_swap_chain->present(true);
	EngineTime::LogFrameEnd();

	
	
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	//quad1.onDestroy();
	
	for (int i = 0; i < cubeList.size(); i++) {
		cubeList[i]->onDestroy();
	}
	cube1->onDestroy();
	m_swap_chain->release();
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
