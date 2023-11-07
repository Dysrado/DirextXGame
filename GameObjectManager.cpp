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
	sharedInstance->objList.clear();
	sharedInstance->objTable.clear();
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
	String Key = gameObject->getName();
	int i = 0;
	while (objTable[Key] != nullptr)
	{
		i++;
		Key = gameObject->getName();
		Key.append(std::to_string(i));
	}
	//std::pair<String, AGameObject*> pair(Key, gameObject);
	objTable[Key] = gameObject;
	objList.push_back(gameObject);
}

void GameObjectManager::createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader)
{
	switch (type)
	{
	case PrimitiveType::CUBE:
	{
		Cube* cube = new Cube("Cube ", shaderByteCode, sizeShader);
		cube->setAnimSpeed(10);
		cube->SetScale(Vector3D(1, 1, 1));
		cube->SetPosition(Vector3D(0, 0, 0));

		addObject((AGameObject*)cube);
	}
	break;
	case PrimitiveType::PLANE:
	{
		Cube* cube = new Cube("Plane", shaderByteCode, sizeShader);
		cube->setAnimSpeed(0);
		cube->SetScale(Vector3D(6, 0.001, 6));
		cube->SetPosition(Vector3D(0, 0, 0));
		addObject((AGameObject*)cube);
	}
	break;

	case PrimitiveType::SPHERE:
	{
	}
	break;

	}
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
	String Key = gameObject->getName();
	int i = 0;
	while (objTable[Key] != gameObject)
	{
		i++;
		Key = gameObject->getName();
		Key.append(std::to_string(i));
	}
	selectedObject = objTable[Key];
}

AGameObject* GameObjectManager::getSelectedObject()
{
	return selectedObject;
}

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}
