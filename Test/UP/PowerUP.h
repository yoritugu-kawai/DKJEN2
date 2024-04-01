#pragma once
#include"../../DKJEN/Imgui/imguiManager.h"
class PowerUP
{
public:
	void Initialize();
	void Update();
	void ImGui();
	int GetHit() { return hit_; }
private:
	float up_;
	float hit_;
};
