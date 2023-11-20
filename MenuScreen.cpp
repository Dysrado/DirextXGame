#include "MenuScreen.h"

void MenuScreen::drawUI()
{
	//ImGui::Begin(this->getName().c_str(), NULL, ImGuiWindowFlags_NoTitleBar);
	ImGui::BeginMainMenuBar();
	ImGui::MenuItem("File");
	if(ImGui::BeginMenu("Game Object")) {
		
		if (ImGui::MenuItem("Create Cube"))
		{
			void* shader_byte_code = nullptr;
			size_t size_shader = 0;
			GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
			GameObjectManager::getInstance()->createObject(GameObjectManager::CUBE, shader_byte_code, size_shader);
			GraphicsEngine::get()->releaseCompiledShader();
		}
		if (ImGui::MenuItem("Create Sphere"))
		{
			/*void* shader_byte_code = nullptr;
			size_t size_shader = 0;
			GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
			GameObjectManager::getInstance()->createObject(GameObjectManager::SPHERE, shader_byte_code, size_shader);
			GraphicsEngine::get()->releaseCompiledShader();*/
		}
		if (ImGui::MenuItem("Create Plane"))
		{
			void* shader_byte_code = nullptr;
			size_t size_shader = 0;
			GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
			GameObjectManager::getInstance()->createObject(GameObjectManager::PLANE, shader_byte_code, size_shader);
			GraphicsEngine::get()->releaseCompiledShader();
		}
		if (ImGui::BeginMenu("Create Light"))
		{
			if (ImGui::MenuItem("Point Light")) {}
			ImGui::EndMenu();
		}

		if (ImGui::MenuItem("Create Physics Cube"))
		{
			void* shader_byte_code = nullptr;
			size_t size_shader = 0;
			GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
			GameObjectManager::getInstance()->createObject(GameObjectManager::PHYSICS_CUBE, shader_byte_code, size_shader);
			GraphicsEngine::get()->releaseCompiledShader();
		}
		if (ImGui::MenuItem("Create Physics Plane"))
		{
			void* shader_byte_code = nullptr;
			size_t size_shader = 0;
			GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
			GameObjectManager::getInstance()->createObject(GameObjectManager::PHYSICS_PLANE, shader_byte_code, size_shader);
			GraphicsEngine::get()->releaseCompiledShader();
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
