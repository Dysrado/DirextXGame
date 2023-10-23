#include "GameObjectManager.h"
#include "EngineTime.h"
GameObjectManager* GameObjectManager::sharedInstance = nullptr;

GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager();
}

void GameObjectManager::destroy()
{
}

AGameObject* GameObjectManager::findObjectByName(std::string name)
{
	for (int i = 0; i < objList.size(); i++) {
		if (objList[i]->getName() == name) {
			return objList[i];
		}
	}
	return nullptr;
}

GameObjectManager::List GameObjectManager::getAllObjects()
{
	return objList;
}

int GameObjectManager::activeObjects()
{
	int count = 0;
	for (int i = 0; i < objList.size(); i++) {
		if (objList[i]->isActive == true) {
			count++;
		}
	}
	return count;
}

void GameObjectManager::updateAll()
{
	for (int i = 0; i < objList.size(); i++) {
		if (objList[i]->isActive == true) {
			objList[i]->onUpdate(EngineTime::getDeltaTime());
		}
	}
}

void GameObjectManager::renderAll(int viewportWidth, int viewportHeight, VertexShader* vertexShader, PixelShader* pixelShader)
{
	for (int i = 0; i < objList.size(); i++) {
		if (objList[i]->isActive == true) {
			objList[i]->onRender(viewportWidth, viewportHeight, vertexShader, pixelShader);
		}
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	objList.push_back(gameObject);
}

void GameObjectManager::createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader)
{
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
}

void GameObjectManager::deleteObjectByName(std::string name)
{
	for (int i = 0; i < objList.size(); i++) {
		if (objList[i]->getName() == name) {
			objList[i]->onDestroy();
			//objList.erase(i);
		}
	}
}

void GameObjectManager::setSelectedObject(std::string name)
{
}

void GameObjectManager::setSelectedObject(AGameObject* gameObject)
{
}

AGameObject* GameObjectManager::getSelectedObject()
{
	return nullptr;
}

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}
