#pragma once
#include <string>
#include <vector>
#include "AGameObject.h"
#include <unordered_map>
class GameObjectManager
{
public:
	typedef std::string String;
	typedef std::vector<AGameObject*> List;
	typedef std::unordered_map<String, AGameObject*> HashTable;

	enum PrimitiveType {
		CUBE,
		PLANE,
		SPHERE
	};

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();
	AGameObject* findObjectByName(std::string name);
	List getAllObjects();
	int activeObjects();

	void updateAll();
	void renderAll(int viewportWidth, int viewportHeight, VertexShader* vertexShader, PixelShader* pixelShader);
	void addObject(AGameObject* gameObject);
	void createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader);
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(std::string name);
	void setSelectedObject(std::string name);
	void setSelectedObject(AGameObject* gameObject);
	AGameObject* getSelectedObject();

private:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	static GameObjectManager* sharedInstance;

	List objList;
	HashTable objTable;
	
};

