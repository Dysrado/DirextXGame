#pragma once
#include "AGameObject.h"
#include "InputListener.h"
#include <string>
#include "Matrix4x4.h"
#include "Vector3D.h"
#include "InputSystem.h"
class Camera: public AGameObject, public InputListener
{
public:
	Camera(std::string name);
	~Camera();

	void onUpdate(float deltaTime) override;
	Matrix4x4 getViewMatrix();
	void  updateViewMatrix();
	void onRender(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;
	void onDestroy() override;



	// Inherited via InputListener
	void onKeyUp(int key) override;

	void onKeyDown(int key) override;

	void onMouseMove(const Point deltaPos) override;

	void onLeftMouseDown(const Point deltaPos) override;

	void onLeftMouseUp(const Point deltaPos) override;

	void onRightMouseDown(const Point deltaPos) override;

	void onRightMouseUp(const Point deltaPos) override;

};

