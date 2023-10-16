#pragma once
#include "Matrix4x4.h"
#include "Camera.h"
class SceneCameraHandler
{
public:
	static SceneCameraHandler* getInstance();
	static void initialize();
	static void destroy();

	void update(float deltaTime);

	Matrix4x4 getSceneCameraViewMatrix();

private:
	SceneCameraHandler();
	~SceneCameraHandler();
	SceneCameraHandler(SceneCameraHandler const&) {};
	SceneCameraHandler& operator=(SceneCameraHandler const&) {};
	static SceneCameraHandler* sharedInstance;

	Camera* sceneCamera;
	

	
};

