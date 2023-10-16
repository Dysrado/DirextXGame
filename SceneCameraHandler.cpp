#include "SceneCameraHandler.h"
#include "EngineTime.h"

SceneCameraHandler* SceneCameraHandler::sharedInstance = NULL;
SceneCameraHandler* SceneCameraHandler::getInstance()
{
	return sharedInstance;
}

void SceneCameraHandler::initialize(int width, int height)
{
	sharedInstance = new SceneCameraHandler(width, height);
}

void SceneCameraHandler::destroy()
{
}

void SceneCameraHandler::update()
{
	sceneCamera->onUpdate(EngineTime::getDeltaTime());

}

void SceneCameraHandler::moveCamera(float x, float y)
{
	sceneCamera->addLocalRot(x, y);

}

Matrix4x4 SceneCameraHandler::getSceneCameraViewMatrix()
{
	return sceneCamera->getViewMatrix();
}

SceneCameraHandler::SceneCameraHandler(int width, int height)
{
	sceneCamera = new Camera("Cam", width, height);
}

SceneCameraHandler::~SceneCameraHandler()
{
}
