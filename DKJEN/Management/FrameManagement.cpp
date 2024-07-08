#include "FrameManagement.h"

FrameManagement* FrameManagement::GetInstance()
{
	static FrameManagement instance;

	return &instance;
}

void FrameManagement::BeginFrame()
{
	//DxCommon::BeginFrame();
	ImguiManager::BeginFrame();
	Input::BeginFlame();
}

void FrameManagement::EndFrame()
{
	ImguiManager::EndFrame();
	//DxCommon::EndFrame();
}