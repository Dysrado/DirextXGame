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

	InputSystem::getInstance()->addListener(this);
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	EngineTime::initialize();
	RECT rc = this->getClientWindowRect();
	SceneCameraHandler::initialize(rc.right - rc.left, rc.bottom - rc.top);
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	UIManager::initialize(m_hwnd);
	GameObjectManager::initialize();

	//// Setup Dear ImGui context
	//IMGUI_CHECKVERSION();
	//ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO();
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	////io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	//// Setup Platform/Renderer backends
	//ImGui_ImplWin32_Init(m_hwnd);
	//ImGui_ImplDX11_Init(GraphicsEngine::get()->getDirect3DDevice(),GraphicsEngine::get()->getImmediateDeviceContext()->getDeviceContext());
	//clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//for (int i = 0; i < 50; i++) {
	//	
	//	Cube* cube;
	//	cube = new Cube("Cube " + i, shader_byte_code, size_shader);
	//	cube->setAnimSpeed(10);
	//	cube->SetScale(Vector3D(1,1,1));
	//	
	//	//cube->SetPosition(Vector3D(1,1,0));
	//	cube->SetPosition(distfloat(rd), distfloat(rd), distfloat(rd));
	//	cubeList.push_back(cube);
	//}

	//
	//
	//cube1 = new Cube("Plane", shader_byte_code, size_shader);
	//cube1->setAnimSpeed(0);
	//cube1->SetScale(Vector3D(6, 0.1, 6));
	//cube1->SetPosition(Vector3D(0, 0, 0));
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
	// (Your code process and dispatch Win32 messages)
	// Start the Dear ImGui frame
	/*ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame()*/;
	//if (show_demo_window)
	//	ImGui::ShowDemoWindow(&show_demo_window);
	//ImGui::Begin("Scene Settings", NULL, ImGuiWindowFlags_NoResize);

	//

	//ImGui::Text("Below are settings for configuring the Scene");
	//ImGui::Checkbox("Show Demo Window", &show_demo_window);

	//// Edit a color stored as 3
	//ImGui::ColorEdit3("clear color", (float*)&clear_color);

	//if (isPaused) {
	//	if (ImGui::Button("Resume Animation")) {
	//		isPaused = false;
	//	}
	//}

	//else if (!isPaused) {
	//	if (ImGui::Button("Pause Animation")) {
	//		isPaused = true;
	//	}
	//}
	
	float colors[4];
	colors[0] = clear_color.x;
	colors[1] = clear_color.y;
	colors[2] = clear_color.z;
	colors[3] = clear_color.w;
	//ImGui::End();
	//ImGui::ShowDemoWindow(); // Show demo window! :)
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(m_swap_chain,colors[0], colors[1], colors[2], colors[3]);

	RECT rc = getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	
	SceneCameraHandler::getInstance()->update();

	
	GameObjectManager::getInstance()->updateAll();
	GameObjectManager::getInstance()->renderAll(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);

	/*for (int i = 0; i < cubeList.size(); i++) {
		if (!isPaused) {
			cubeList[i]->addMovement(1, EngineTime::getDeltaTime());
		}
		cubeList[i]->onUpdate(EngineTime::getDeltaTime());
		cubeList[i]->onRender(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);
	}*/

	
	//cube1->onUpdate(EngineTime::getDeltaTime());
	//cube1->onRender(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);
	
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW

	EngineTime::LogFrameEnd();

	// Rendering
	// (Your code clears your framebuffer, renders your other stuff etc.)
	UIManager::getInstance()->drawAllUI();
	/*ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());*/
	// (Your code calls swapchain's Present() function)
	m_swap_chain->present(true);
	
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	//quad1.onDestroy();
	
	for (int i = 0; i < cubeList.size(); i++) {
		cubeList[i]->onDestroy();
	}
	//cube1->onDestroy();
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
