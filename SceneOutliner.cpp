#include "SceneOutliner.h"

void SceneOutliner::drawUI()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize;
	flags = ImGuiWindowFlags_NoScrollbar;
	ImGui::SetNextWindowContentSize(ImVec2(200, 850));
	ImGui::SetNextWindowPos(ImVec2(560, 20));
	ImGui::Begin("Scene Outliner", NULL, flags);
	ImGui::End();
}

SceneOutliner::SceneOutliner(String name) : AUIScreen(name)
{
	this->name = name;
}

SceneOutliner::~SceneOutliner()
{
}
