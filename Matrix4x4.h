#pragma once
#include <memory>
#include "Vector3D.h"
#include "Vector4D.h"
#include <iostream>

class Matrix4x4
{
public:
	Matrix4x4();
	~Matrix4x4();
	void setIdentity();
	void setTranslation(const Vector3D translation);
	void setScale(const Vector3D scale);
	void setRotationX(float x);
	void setRotationY(float y);
	void setRotationZ(float z);
	void setOrthoLH(float width, float height, float near_plane, float far_plane);
	Matrix4x4 multiplyTo(Matrix4x4 matrix);
	void operator *= (const Matrix4x4& matrix);
	void inverse();
	void setPerspectiveFovLH(float fov, float aspect, float znear, float zfar);
	float getDeterminant();
	void debugPrint();
	void setMatrix(const Matrix4x4& matrix);

private:
	void matrixInitialize();

	float matrix[4][4] = {};
};