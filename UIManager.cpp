#include "UIManager.h"
UIManager* UIManager::sharedInstance = nullptr;

UIManager* UIManager::getInstance()
{
    return sharedInstance;
}

void UIManager::initialize(HWND windowHandle)
{
    sharedInstance = new UIManager(windowHandle);
}

void UIManager::destroy()
{
}

void UIManager::drawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (int i = 0; i < this->uiList.size(); i++) {
		this->uiList[i]->drawUI();
	}
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}



UIManager::UIManager(HWND windowHandle)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getDirect3DDevice(), GraphicsEngine::get()->getImmediateDeviceContext()->getDeviceContext());
	UINames uinames;
	MenuScreen* menuScreen = new MenuScreen(uinames.MENU_SCREEN);
	uiList.push_back(menuScreen);
	InspectorWindow* insWindow = new InspectorWindow(uinames.INSPECTOR_SCREEN);
	uiList.push_back(insWindow);
	SceneOutliner* sceneOut = new SceneOutliner(uinames.HIERARCHY_SCREEN);
	uiList.push_back(sceneOut);
	EngineProfiler* engProf = new EngineProfiler(uinames.PROFILER_SCREEN);
	uiList.push_back(engProf);
}

UIManager::~UIManager()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
