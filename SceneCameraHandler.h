#pragma once
#include "Camera.h"
class SceneCameraHandler {
public:
	static SceneCameraHandler* getInstance();
	static void initialize(int width, int height);
	static void destroy();

	void update();
	void moveCamera(float x, float y);
	

	Matrix4x4 getSceneCameraViewMatrix();

private:
	SceneCameraHandler(int width, int height);
	~SceneCameraHandler();
	SceneCameraHandler(SceneCameraHandler const&) {};
	SceneCameraHandler& operator=(SceneCameraHandler const&) {};
	static SceneCameraHandler* sharedInstance;
	
	Camera* sceneCamera;
};