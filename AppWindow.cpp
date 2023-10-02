#include "AppWindow.h"

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	Quad::vertex list[] =
	{
		//X - Y - Z
		//{-0.25f,-0.25f,0.0f,   0,0,0}, // POS1
		//{-0.25f,0.f,0.0f,    1,1,0}, // POS2
		//{0.0f,-0.25f,0.0f,   0,0,1},
		//{0.f,0.f,0.0f,    1,1,1 }

		{ -0.4f, -0.45f,    0.0f,  -0.16f, -0.25f, 0.0f,   0, 0, 0,   0, 1, 0}, // POS1 
		{ -0.45f,  0.2f,    0.0f, -0.11f,  0.36f, 0.0f,   1, 1, 0,   1, 1, 0}, // POS2
		{  0.45f, -0.15f,    0.0f,   0.37f, -0.77f, 0.0f,   0, 0, 1,   1, 0, 0}, // POS3
		{  -0.4f, -0.45f,    0.0f,   0.44f,  0.38f, 0.0f,   1, 1, 1,   0, 0, 1}, // POS4 
	};

	quad1.onCreate(list[0], list[1], list[2], list[3]);
	
	
	Quad::constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(Quad::constant));

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	
	m_angle += EngineTime::getDeltaTime();
	Quad::constant cc;
	
	cc.m_angle = m_angle + ((sin(m_angle / 10.0f) + (m_angle / 10.0f))) * 150.0f;

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	quad1.onRender(m_cb);
	

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	

	m_swap_chain->present(true);
	EngineTime::LogFrameEnd();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	quad1.onDestroy();
	
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}