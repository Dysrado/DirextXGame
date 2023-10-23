#include "InspectorWindow.h"

void InspectorWindow::drawUI()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize;
	flags = ImGuiWindowFlags_NoScrollbar;
	ImGui::SetNextWindowContentSize(ImVec2(200, 850));
	ImGui::SetNextWindowPos(ImVec2(775, 20));
	ImGui::Begin("Inspector Window", NULL, flags);
	ImGui::Text("No object selected.Select an object from the scene.");
	ImGui::End();
}

InspectorWindow::InspectorWindow(String name) : AUIScreen(name)
{
	this->name = name;
}

InspectorWindow::~InspectorWindow()
{
}
