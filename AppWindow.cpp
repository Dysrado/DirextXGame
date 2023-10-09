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
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	EngineTime::initialize();
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	for (int i = 0; i < 9; i++) {
		
		Cube* cube;
		cube = new Cube("NICE", shader_byte_code, size_shader);
		cube->setAnimSpeed(distint(rd));
		cube->SetScale(Vector3D(0.5, 0.5, 0.5));
		cube->SetPosition(distfloat(rd), distfloat(rd), distfloat(rd));
		cubeList.push_back(cube);
	}

	

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
	GraphicsEngine::get()->releaseCompiledShader();

}

void AppWindow::onUpdate()
{


	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(m_swap_chain, 0.2f, 0.2f, 0.2f, 1);

	RECT rc = getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);


	/*AGameObject::constant cc;
	Matrix4x4 temp;

	cc.worldMatrix.setScale(Vector3D(1.0f, 1.0f, 1.0f));

	temp.setIdentity();
	temp.setRotationZ(ticks);
	cc.worldMatrix = cc.worldMatrix.multiplyTo(temp);

	temp.setIdentity();
	temp.setRotationY(ticks);
	cc.worldMatrix = cc.worldMatrix.multiplyTo(temp);

	temp.setIdentity();
	temp.setRotationX(ticks);
	cc.worldMatrix = cc.worldMatrix.multiplyTo(temp);


	cc.viewMatrix.setIdentity();
	cc.projMatrix.setOrthoLH
	(
		(rc.right - rc.left) / 300.0f,
		(rc.bottom - rc.top) / 300.0f,
		-4.0f,
		4.0f
	);


	cc.m_time = this->ticks;*/

	//std::cout << "m_time: " << cc.m_time << "\n";
	//std::cout << "sin(m_time): " << (std::sin(cc.m_time) + 1) / 2 << "\n";

	/*m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);*/
	//Window::onUpdate();
	////CLEAR THE RENDER TARGET 
	//GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
	//	0, 0.3f, 0.4f, 1);
	////SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	//RECT rc = this->getClientWindowRect();
	//GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//
	//m_angle += EngineTime::getDeltaTime();
	//AGameObject::constant cc;
	//
	//Matrix4x4 temp;

	//cc.worldMatrix.setScale(Vector3D(1.0f, 1.0f, 1.0f));

	//temp.setIdentity();
	//temp.setRotationZ(ticks);
	//cc.worldMatrix = cc.worldMatrix.multiplyTo(temp);

	//temp.setIdentity();
	//temp.setRotationY(ticks);
	//cc.worldMatrix = cc.worldMatrix.multiplyTo(temp);

	//temp.setIdentity();
	//temp.setRotationX(ticks);
	//cc.worldMatrix = cc.worldMatrix.multiplyTo(temp);


	//cc.viewMatrix.setIdentity();
	//cc.projMatrix.setOrthoLH
	//(
	//	(rc.right - rc.left) / 300.0f,
	//	(rc.bottom - rc.top) / 300.0f,
	//	-4.0f,
	//	4.0f
	//);


	//cc.m_time = this->ticks;

	/*cc.m_angle = m_angle + ((sin(m_angle / 10.0f) + (m_angle / 10.0f))) * 150.0f;

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);*/

	//quad1.onRender(m_cb);
	
	for (int i = 0; i < cubeList.size(); i++) {
		cubeList[i]->onUpdate(EngineTime::getDeltaTime());
		cubeList[i]->onRender(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);
	}
	

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
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}