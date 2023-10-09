#pragma once
class Vector3D
{
public:
	Vector3D();
	~Vector3D();

	Vector3D(float x, float y, float z);
	Vector3D(const Vector3D* vector);

	struct Vect {
		float x;
		float y;
		float z;
	};

	Vector3D::Vect getValues() const;

	static Vector3D lerp(const Vector3D start, const Vector3D end, float delta);
	static Vector3D zeros() { Vector3D v; v = Vector3D(0, 0, 0); return v; };
	static Vector3D ones() { Vector3D v; v = Vector3D(1,1,1); return v; };
public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};