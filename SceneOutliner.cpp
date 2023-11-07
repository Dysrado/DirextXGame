#include "SceneOutliner.h"
#include "GameObjectManager.h"
#include "UIManager.h"


void SceneOutliner::drawUI()
{
	float xButtonSize = UIManager::WINDOW_HEIGHT * 0.19f;
	float yButtonSize = UIManager::WINDOW_HEIGHT * 0.025f;
	ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize;
	flags = ImGuiWindowFlags_NoScrollbar;
	ImGui::SetNextWindowContentSize(ImVec2(200, 850));
	ImGui::SetNextWindowPos(ImVec2(560, 20));
	ImGui::Begin("Scene Outliner", NULL, flags);

	std::vector<AGameObject* >list = GameObjectManager::getInstance()->getAllObjects();

	for (AGameObject* GameObject : list)
	{
		String name = GameObject->getName();
		if (ImGui::Button(name.c_str(), ImVec2(xButtonSize, yButtonSize)))
		{
			GameObjectManager::getInstance()->setSelectedObject(GameObject);
		}
	}
	ImGui::End();
}

SceneOutliner::SceneOutliner(String name) : AUIScreen(name)
{
	this->name = name;
}

SceneOutliner::~SceneOutliner()
{
}
