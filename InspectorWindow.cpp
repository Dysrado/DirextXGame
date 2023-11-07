#include "InspectorWindow.h"
#include "GameObjectManager.h"

void InspectorWindow::drawUI()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize;
	flags = ImGuiWindowFlags_NoScrollbar;
	ImGui::SetNextWindowContentSize(ImVec2(200, 850));
	ImGui::SetNextWindowPos(ImVec2(775, 20));
	ImGui::Begin("Inspector Window", NULL, flags);
	AGameObject* selectedObject = GameObjectManager::getInstance()->getSelectedObject();

	if (selectedObject == nullptr)
		ImGui::TextWrapped("No Object Selected, Select an object");

	else
	{
		String text = "Object Selected: ";
		text.append(selectedObject->getName());
		bool isActive = selectedObject->isActive;
		float pos[3] = {
			selectedObject->getLocalPosition().m_x,
			selectedObject->getLocalPosition().m_y,
			selectedObject->getLocalPosition().m_z
		};
		float rot[3] = {
			selectedObject->getLocalRotation().m_x,
			selectedObject->getLocalRotation().m_y,
			selectedObject->getLocalRotation().m_z
		};
		float scale[3] = {
			selectedObject->getLocalScale().m_x,
			selectedObject->getLocalScale().m_y,
			selectedObject->getLocalScale().m_z
		};



		ImGui::TextWrapped(text.c_str());

		if (ImGui::Checkbox("isActive", &isActive))
		{
			selectedObject->isActive = isActive;
		};

		ImGui::InputFloat3("Position", pos);
		ImGui::InputFloat3("Rotation", rot);
		ImGui::InputFloat3("Scale", scale);

		selectedObject->SetPosition(pos[0], pos[1], pos[2]);
		selectedObject->SetRotation(rot[0], rot[1], rot[2]);
		selectedObject->SetScale(scale[0], scale[1], scale[2]);
	}
	ImGui::End();
}

InspectorWindow::InspectorWindow(String name) : AUIScreen(name)
{
	this->name = name;
}

InspectorWindow::~InspectorWindow()
{
}
