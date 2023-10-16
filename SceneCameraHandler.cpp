#include "SceneCameraHandler.h"
SceneCameraHandler* SceneCameraHandler::sharedInstance = nullptr;
SceneCameraHandler* SceneCameraHandler::getInstance()
{
	return sharedInstance;
}

void SceneCameraHandler::initialize()
{
	sharedInstance = new SceneCameraHandler();
	
}

void SceneCameraHandler::destroy()
{
	delete sharedInstance;
}

void SceneCameraHandler::update(float deltaTime)
{
	sceneCamera->onUpdate(deltaTime);
}

Matrix4x4 SceneCameraHandler::getSceneCameraViewMatrix()
{

	return sceneCamera->getViewMatrix();
}

SceneCameraHandler::SceneCameraHandler()
{
	sceneCamera = new Camera("Cam1");

}

SceneCameraHandler::~SceneCameraHandler()
{
}
