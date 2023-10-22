#include "Cube.h"
#include "SceneCameraHandler.h"

Cube ::Cube (std::string name, void* shader_byte_code, size_t size_shader) : AGameObject(name)
{
	//isUpdating = true; //for animations
	AGameObject::vertexCube vertex_list[] =
	{
		//// RAINBOW
		//{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),   Vector3D(1,0,0) },
		//{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(1,1,0) },
		//{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(1,1,0) },
		//{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(1,0,0) },

		////BACK FACE
		//{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,1,0) },
		//{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,1,1) },
		//{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,1,1) },
		//{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,1,0) }


		//White
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,1,1),   Vector3D(1,1,1) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,1), Vector3D(1,1,1) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,1),  Vector3D(1,1,1) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,1,1), Vector3D(1,1,1) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(1,1,1), Vector3D(1,1,1) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(1,1,1), Vector3D(1,1,1) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(1,1,1),  Vector3D(1,1,1) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(1,1,1), Vector3D(1,1,1) }

		////Plane
		//{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(0,0,1),   Vector3D(1,0,0) },
		//{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(0,0,1), Vector3D(1,0,0) },
		//{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(0,0,1),  Vector3D(1,0,0) },
		//{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(0,0,1), Vector3D(1,0,0) },

		////BACK FACE
		//{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,0,1), Vector3D(1,0,0) },
		//{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,0,1), Vector3D(1,0,0) },
		//{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,0,1),  Vector3D(1,0,0) },
		//{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,0,1), Vector3D(1,0,0) },
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

	Matrix4x4 temp;
	cc.m_time += deltaTime * 20;
	cc.worldMatrix.setScale(Vector3D(1.0f, 1.0f, 1.0f));
	temp.setScale(localScale);
	cc.worldMatrix *= temp;


	temp.setIdentity();
	temp.setTranslation(localPosition);
	cc.worldMatrix *= temp;
	
	////Implementation of Cube Scaling
	//if (isUpdating) { 
	//	Vector3D scale;
	//	temp.setIdentity();
	//	scale = scale.lerp(this->getLocalScale(), Vector3D(0.25f, 0.25f, 0.25f), deltaTime * speed);
	//	temp.setScale(scale);
	//	cc.worldMatrix *= temp;
	//	this->SetScale(scale);
	//	
	//	Vector3D position;
	//	temp.setIdentity();
	//	position = position.lerp(this->getLocalPosition(), Vector3D(0.25f, 0.25f, this->getLocalPosition().m_z), deltaTime * speed);
	//	temp.setTranslation(position);
	//	this->SetPosition(position);
	//	cc.worldMatrix *= temp;
	//	if (this->getLocalScale().m_y < 0.27) {
	//		isUpdating = false;
	//		isReturning = true;
	//	}
	//}

	//else if (isReturning) {
	//	Vector3D scale;
	//	temp.setIdentity();
	//	scale = scale.lerp(this->getLocalScale(), Vector3D(1,1, this->getLocalPosition().m_z), deltaTime * speed);
	//	temp.setScale(scale);
	//	cc.worldMatrix *= temp;
	//	this->SetScale(scale);

	//	Vector3D position;
	//	temp.setIdentity();
	//	position = position.lerp(this->getLocalPosition(), Vector3D(1,1,this->getLocalPosition().m_z), deltaTime * speed);
	//	temp.setTranslation(position);
	//	this->SetPosition(position);
	//	cc.worldMatrix *= temp;
	//	if (this->getLocalScale().m_y > 0.95) {
	//		isUpdating = true;
	//		isReturning = false;
	//	}
	//}

		//std::cout << this->getLocalPosition().m_x << " " << this->getLocalPosition().m_y << " " << this->getLocalPosition().m_z << std::endl;


	/*// IMPLEMENTATION FOR CUBE TO PLANE
	if (isUpdating) { //Only for lerp
		Vector3D scale;
		temp.setIdentity();
		scale = scale.lerp(this->getLocalScale(), Vector3D(2, 0.1, 2), deltaTime * speed) ;
		temp.setScale(scale);
		cc.worldMatrix *= temp;
		//temp.setScale(scale);
		this->SetScale(scale);
		if (this->getLocalScale().m_y < 0.15) {
			isUpdating = false;
			isReturning = true;
			std::cout << "CHANGING BACK TO CUBE" << std::endl;
		}
	}

	else if (isReturning) {
		Vector3D scale;
		temp.setIdentity();
		scale = scale.lerp(this->getLocalScale(), Vector3D(1, 1, 1), deltaTime * speed);
		temp.setScale(scale);
		cc.worldMatrix *= temp;
		//temp.setScale(scale);
		this->SetScale(scale);
		if ( this->getLocalScale().m_y > 0.95 ) {
			isUpdating = true;
			isReturning = false;
		}
	}*/

	temp.setIdentity();
	temp.setRotationZ(ticks);
	cc.worldMatrix *= temp;

	temp.setIdentity();
	temp.setRotationY(ticks);
	cc.worldMatrix *= temp;

	temp.setIdentity();
	temp.setRotationX(ticks);
	cc.worldMatrix *= temp;




	//if (isUpdating) {
	//	temp.setIdentity();
	//	Vector3D scale = this->getLocalScale();
	//	scale.m_x += 0.25 * deltaTime * speed;
	//	scale.m_y -= 0.25 * deltaTime * speed;
	//	scale.m_z += 0.25 * deltaTime * speed;
	//	temp.setScale(scale);

	//	this->SetScale(scale);
	//	
	//	cc.worldMatrix *= temp;
	//	//temp.setScale(scale);
	//	std::cout << this->getLocalScale().m_x << " " << this->getLocalScale().m_y << " " << this->getLocalScale().m_z << std::endl;

	//	if (this->getLocalScale().m_x >= 2 || this->getLocalScale().m_y <= 0.2 || this->getLocalScale().m_z >= 2) {
	//		isUpdating = false;
	//	}
	//}
	

	
	//temp.setScale(localScale);
	//cc.worldMatrix *= temp;
	

	
	
	
	
	//scale = scale.lerp(scale, Vector3D(5, 0.1, 5), deltaTime);
	//temp.setIdentity();
	
	
	
	


}



