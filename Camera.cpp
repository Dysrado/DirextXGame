#include "Camera.h"
#include "InputSystem.h"

Camera::Camera(std::string name, int width, int height) : AGameObject(name)
{
	this->name = name;
	this->width = width;
	this->height = height;
	InputSystem::getInstance()->addListener(this);
}

Camera::~Camera()
{
}

Matrix4x4 Camera::getViewMatrix()
{
	return localMatrix;
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam; worldCam.setIdentity();
	Matrix4x4 temp; temp.setIdentity();

	Vector3D localRot = this->getLocalRotation();

	temp.setRotationX(localRot.m_x);
	worldCam *= temp;

	temp.setRotationY(localRot.m_y);
	worldCam *= temp;

	temp.setTranslation(this->getLocalPosition());
	worldCam *= temp;

	worldCam.inverse();
	this->localMatrix = worldCam;

}

void Camera::addLocalRot(float x, float y)
{
	localRotation.m_x += x;
	localRotation.m_y += y;
}

void Camera::onRender(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	
}

void Camera::onDestroy()
{
}

void Camera::onUpdate(float deltaTime)
{
	Vector3D localPos = this->getLocalPosition();
	float x = localPos.m_x;
	float y = localPos.m_y;
	float z = localPos.m_z;

	float moveSpeed = 100.0f;

	if (InputSystem::getInstance()->isKeyDown('W')) {
		z += deltaTime * moveSpeed;
		this->SetPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		z -= deltaTime * moveSpeed;
		this->SetPosition(x, y, z);
		this->updateViewMatrix();
	}

	else  if (InputSystem::getInstance()->isKeyDown('A')) {
		x += deltaTime * moveSpeed;
		this->SetPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		x -= deltaTime * moveSpeed;
		this->SetPosition(x, y, z);
		this->updateViewMatrix();
	}
	this->updateViewMatrix();

	
	
}

void Camera::onKeyUp(int key)
{
}

void Camera::onKeyDown(int key)
{
}

void Camera::onMouseMove(const Point deltaPos)
{
	
	localRotation.m_x -= deltaPos.getY() * EngineTime::getDeltaTime();
	localRotation.m_y -= deltaPos.getX() * EngineTime::getDeltaTime();
	this->updateViewMatrix();

	
	//InputSystem::getInstance()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));
}

void Camera::onLeftMouseDown(const Point deltaPos)
{
}

void Camera::onLeftMouseUp(const Point deltaPos)
{
}

void Camera::onRightMouseDown(const Point deltaPos)
{
}

void Camera::onRightMouseUp(const Point deltaPos)
{
}
