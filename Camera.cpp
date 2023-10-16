#include "Camera.h"

Camera::Camera(std::string name) : AGameObject(name)
{
	this->name = name;
	InputSystem::getInstance()->addListener(this);
}

Camera::~Camera()
{
}

void Camera::onDestroy()
{
}

void Camera::onUpdate(float deltaTime)
{
	Vector3D localPos = this->getLocalPosition();
	float x = localPos.getX();
	float y = localPos.getY();
	float z = localPos.getZ();

	float moveSpeed = 10.0f;

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

	else if (InputSystem::getInstance()->isKeyDown('A')) {
		x += deltaTime * moveSpeed;
		this->SetPosition(x, y, z);
		this->updateViewMatrix();
	}

	else if (InputSystem::getInstance()->isKeyDown('D')) {
		x -= deltaTime * moveSpeed;
		this->SetPosition(x, y, z);
		this->updateViewMatrix();
	}
	//std::cout << "Local Position X" << localPos.x << std::endl;
	//std::cout << "Local Position Z" << localPos.z << std::endl;
}

Matrix4x4 Camera::getViewMatrix()
{
	//std::cout << "VIEW MATRIX OF Camera\n";
	//localMatrix.debugPrint();
	return localMatrix;
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam; worldCam.setIdentity();
	Matrix4x4 temp; temp.setIdentity();

	Vector3D localRot = this->getLocalRotation();

	temp.setRotationX(localRot.getX());
	worldCam = worldCam.multiplyTo(temp);

	temp.setRotationY(localRot.getY());
	worldCam = worldCam.multiplyTo(temp);

	temp.setTranslation(this->getLocalPosition());
	worldCam = worldCam.multiplyTo(temp);

	worldCam.inverse();
	this->localMatrix = worldCam;
}

void Camera::onRender(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
}

void Camera::onKeyUp(int key)
{
}

void Camera::onKeyDown(int key)
{
}

void Camera::onMouseMove(const Point deltaPos)
{
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
