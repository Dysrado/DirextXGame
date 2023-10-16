#pragma once
#include "AGameObject.h"
#include "InputListener.h"
#include "Matrix4x4.h"
#include <string>
#include "EngineTime.h"
class Camera : public AGameObject, public InputListener {
public:
	Camera(std::string name, int width, int height);
	~Camera();

	Matrix4x4 getViewMatrix();

	void updateViewMatrix();
	void addLocalRot(float x, float y);

	// Inherited via AGameObject
	void onRender(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;

	void onDestroy() override;

	void onUpdate(float deltaTime) override;
	

	// Inherited via InputListener
	void onKeyUp(int key) override;

	void onKeyDown(int key) override;

	void onMouseMove(const Point deltaPos) override;

	void onLeftMouseDown(const Point deltaPos) override;

	void onLeftMouseUp(const Point deltaPos) override;

	void onRightMouseDown(const Point deltaPos) override;

	void onRightMouseUp(const Point deltaPos) override;

	int width;
	int height;
};