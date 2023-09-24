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

		{-0.5f,-0.5f,0.0f,    -0.32f,-0.11f,0.0f,   0,0,0,  0,1,0 }, // POS1
		{-0.5f,0.5f,0.0f,     -0.11f,0.78f,0.0f,    1,1,0,  0,1,1 }, // POS2
		{ 0.5f,-0.5f,0.0f,     0.75f,-0.73f,0.0f,   0,0,1,  1,0,0 },// POS2
		{ 0.5f,0.5f,0.0f,      0.88f,0.77f,0.0f,    1,1,1,  0,0,1 }
	};

	//Quad::vertex list2[] =
	//{
	//	//X - Y - Z
	//	{0.25f,0.25f,0.0f}, // POS1
	//	{0.25f,0.5f,0.0f}, // POS2
	//	{0.5f,0.25f,0.0f},
	//	{0.5f,0.5f,0.0f}
	//};

	//Quad::vertex list3[] =
	//{
	//	//X - Y - Z
	//	{-0.25f,0.25f,0.0f}, // POS1
	//	{-0.25f,0.5f,0.0f}, // POS2
	//	{0.f,0.25f,0.0f},
	//	{0.f,0.5f,0.0f}
	//};
	quad1.onCreate(list[0], list[1], list[2], list[3]);
	/*quad2.onCreate(list2[0], list2[1], list2[2], list2[3]);
	quad3.onCreate(list3[0], list3[1], list3[2], list3[3]);*/
	
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

	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();
	m_angle += 1.57f * m_delta_time;
	Quad::constant cc;
	cc.m_angle = m_angle;

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	quad1.onRender(m_cb);
	

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	//GraphicsEngine::get()->setShaders();
	
	/*quad2.onRender();
	quad3.onRender();*/

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	quad1.onDestroy();
	/*quad2.onDestroy();
	quad3.onDestroy();*/
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}