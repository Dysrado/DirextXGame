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

void AGameObject::attachComponent(AComponent* component)
{
	component->attachOwner(this);
	componentList.push_back(component);
	componentTable.insert({ component->getName(), component });
}

void AGameObject::detachComponent(AComponent* component)
{
	component->detachOwner();
	componentTable.erase(component->getName());
	for (int i = 0; i < componentList.size(); i++) {
		if (componentList[i] == component) {
			componentList.erase(componentList.begin() + i);
			break;
		}
	}
}

AComponent* AGameObject::findComponentByName(std::string name)
{
	return componentTable[name];
}

AComponent* AGameObject::findComponentofType(AComponent::ComponentType type, std::string name)
{
	return nullptr;
}

void AGameObject::recomputeMatrix(float matrix[16])
{
	Matrix4x4 matrix4x4;
	matrix4x4.m_mat[0][0] = matrix[0];
	matrix4x4.m_mat[0][1] = matrix[1];
	matrix4x4.m_mat[0][2] = matrix[2];
	matrix4x4.m_mat[0][3] = matrix[3];

	matrix4x4.m_mat[1][0] = matrix[4];
	matrix4x4.m_mat[1][1] = matrix[5];
	matrix4x4.m_mat[1][2] = matrix[6];
	matrix4x4.m_mat[1][3] = matrix[7];

	matrix4x4.m_mat[2][0] = matrix[8];
	matrix4x4.m_mat[2][1] = matrix[9];
	matrix4x4.m_mat[2][2] = matrix[10];
	matrix4x4.m_mat[2][3] = matrix[11];

	matrix4x4.m_mat[3][0] = matrix[12];
	matrix4x4.m_mat[3][1] = matrix[13];
	matrix4x4.m_mat[3][2] = matrix[14];
	matrix4x4.m_mat[3][3] = matrix[15];

	Matrix4x4 newMatrix; newMatrix.setMatrix(matrix4x4);
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->localScale);
	Matrix4x4 transMatrix; transMatrix.setTranslation(this->localPosition);
	this->localMatrix = scaleMatrix.multiplyTo(transMatrix.multiplyTo(newMatrix));
}

float* AGameObject::getPhysicsLocalMatrix()
{
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity();
	translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(Vector3D::ones()); //physics 3D only accepts uniform scale for rigidbody
	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.m_x);
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.m_y);
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.m_z);

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);

	return allMatrix.getMatrix();
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
