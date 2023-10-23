#include "EngineProfiler.h"
#include "EngineTime.h"

void EngineProfiler::drawUI()
{

	ImGui::SetNextWindowSize(ImVec2(350, 100));
	ImGui::SetNextWindowPos(ImVec2(0, 625));
	ImGui::Begin("EngineProfiler", NULL);
	ImGui::Text("Application average %000.00f ms/frame (%000.0f FPS)", EngineTime::getDeltaTime() * 10000.0f, 1.0f/ EngineTime::getDeltaTime());
	ImGui::End();
}

EngineProfiler::EngineProfiler(String name): AUIScreen(name)
{
	this->name = name;
}

EngineProfiler::~EngineProfiler()
{
}
