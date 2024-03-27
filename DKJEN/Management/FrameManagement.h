#pragma once
#include"../Base/DxCommon.h"
#include"../Imgui/imguiManager.h"
#include"../Utilipy/Input.h"
class FrameManagement
{
public:
	static FrameManagement* GetInstance();
	static void BeginFrame(); 
	static void EndFrame();
private:

};
