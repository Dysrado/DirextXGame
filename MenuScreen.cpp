#include "MenuScreen.h"

void MenuScreen::drawUI()
{
	//ImGui::Begin(this->getName().c_str(), NULL, ImGuiWindowFlags_NoTitleBar);
	ImGui::BeginMainMenuBar();
	ImGui::MenuItem("File");
	if(ImGui::BeginMenu("Game Object")) {
		
		ImGui::MenuItem("Create Cube");
		ImGui::MenuItem("Create Plane");
		ImGui::MenuItem("Create Cylinder");
		
		if (ImGui::BeginMenu("Create Light")) {
			ImGui::MenuItem("Point Light");
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
	

	ImGui::EndMainMenuBar();
}

MenuScreen::MenuScreen(String name) : AUIScreen(name)
{
	this->name = name;
}

MenuScreen::~MenuScreen()
{
}
