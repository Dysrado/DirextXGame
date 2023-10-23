#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "PixelShader.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include "Matrix4x4.h"
#include <string>

class AGameObject
{
public:
	struct vec3
	{
		float x, y, z;
	};

	struct vertex
	{
		vec3 position;
		vec3 position1;
		vec3 color;
		vec3 color1;
	};

	struct vertexCube
	{
		Vector3D position;
		Vector3D color0;
		Vector3D color1;
	};

	__declspec(align(16))
		struct constant
	{
		Matrix4x4 worldMatrix;
		Matrix4x4 viewMatrix;
		Matrix4x4 projMatrix;
		float m_time;
	};
	
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	ConstantBuffer* m_cb;
	

	AGameObject(std::string name);
	~AGameObject();
	virtual void onRender(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) = 0;
	virtual void onDestroy() = 0;
	virtual void onUpdate(float deltaTime) = 0;

	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void SetRotation(float x, float y, float z);
	void SetRotation(Vector3D rot);
	Vector3D getLocalRotation();

	void SetScale(float x, float y, float z);
	void SetScale(Vector3D Scale);
	Vector3D getLocalScale();
	std::string getName();
	
	constant cc;
	float ticks = 0.0f;
	float speedFactor = 0.1f;
	bool isIncreasing = true;
	bool isActive = true;

protected:
	Matrix4x4 localMatrix;
	std::string name;
	Vector3D localRotation;
	Vector3D localPosition;
	Vector3D localScale;
	
};

