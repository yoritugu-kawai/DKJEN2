#include "PowerUP.h"

void PowerUP::Initialize()
{
	hit_ = 1;
	up_ = 1.5f;

}

void PowerUP::Update()
{
	//up_ += 1;
	hit_ *= up_;
	

}

void PowerUP::ImGui()
{
	ImGui::Begin("hit");
	ImGui::Text("%fup", up_);
	ImGui::Text("%fhit", hit_);
	ImGui::End();
}
