#include "Cube.h"
#include "SceneCameraHandler.h"

Cube ::Cube (std::string name, void* shader_byte_code, size_t size_shader) : AGameObject(name)
{
	
	AGameObject::vertexCube vertex_list[] =
	{
		// FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),   Vector3D(1,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(1,1,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(1,1,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(1,0,0) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,1,0) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,1,1) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,1,1) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,1,0) }

	};

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};
	
	
	
	//std::cout << "Size of ver list: " << sizeof(vertex_list) << std::endl;
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT const size_list = ARRAYSIZE(vertex_list);

	
	m_ib = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib->load(index_list, size_index_list);

	
	
	m_vb->load(vertex_list, sizeof(vertexCube), size_list, shader_byte_code, size_shader);

	
	// Constant Buffer setup
	AGameObject::constant cc;
	cc.m_time = 0;
	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(AGameObject::constant)); // load initial value and format
	
}

Cube::~Cube()
{
}

void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}

void Cube::addMovement(bool direction, float deltaTime)
{
	if (direction) {
		ticks += speed * deltaTime;
	}
	else {
		
		ticks -= speed * deltaTime;
	}
}

void Cube::onRender(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{

	cc.viewMatrix.setIdentity();
	
	/*cc.projMatrix.setOrthoLH
	(
		width / 300.0f,
		height / 300.0f,
		-4.0f,
		4.0f
	);*/

	//cc.projMatrix.setPerspectiveFovLH(1.57f, (float)width/height,0.1f, 100.0f);
	cc.projMatrix.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);
	Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cc.viewMatrix = cameraMatrix;
	//std::cout << "VIEW MATRIX OF CUBe\n";
	//cc.viewMatrix.debugPrint();

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixelShader);
	
	//SET THE CONSTANT BUFFERS
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, m_cb);
	//std::cout << "index buffer size: " << m_ib->getSizeIndexList() << std::endl;
	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Cube::onDestroy()
{
}

void Cube::onUpdate(float deltaTime)
{

	//ticks += deltaTime;
	Matrix4x4 temp;

	cc.worldMatrix.setScale(Vector3D(1.0f, 1.0f, 1.0f));
	temp.setScale(localScale);
	cc.worldMatrix *= temp;
	

	temp.setIdentity();
	temp.setRotationZ(0.0f);
	cc.worldMatrix *= temp;

	temp.setIdentity();
	temp.setRotationY(ticks);
	cc.worldMatrix *= temp;

	temp.setIdentity();
	temp.setRotationX(ticks);
	cc.worldMatrix *= temp;


	temp.setIdentity();
	temp.setTranslation(localPosition);
	cc.worldMatrix *= temp;
	

	


}



