#include "AGameObject.h"


AGameObject::AGameObject(std::string name)
{
	this->name = name;
	this->localPosition = Vector3D::zeros();
	this->localRotation = Vector3D::zeros();
	this->localScale = Vector3D::ones();
}

AGameObject::~AGameObject()
{
}

void AGameObject::onRender(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
}

void AGameObject::onDestroy()
{
	m_vb->release();
	
	m_ib->release();
}

void AGameObject::onUpdate(float deltaTime)
{
}

void AGameObject::SetPosition(float x, float y, float z)
{
	this->localPosition = Vector3D(x, y, z);
}

void AGameObject::SetPosition(Vector3D pos)
{
	this->localPosition = pos;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->localPosition;
}

void AGameObject::SetRotation(float x, float y, float z)
{
	this->localRotation = Vector3D(x, y, z);
}

void AGameObject::SetRotation(Vector3D rot)
{
	this->localRotation = rot;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->localRotation;
}

void AGameObject::SetScale(float x, float y, float z)
{
	this->localScale = Vector3D(x, y, z);
}

void AGameObject::SetScale(Vector3D Scale)
{
	this->localScale = Scale;
}

Vector3D AGameObject::getLocalScale()
{
	return this->localScale;
}

std::string AGameObject::getName()
{
	return name;
}
