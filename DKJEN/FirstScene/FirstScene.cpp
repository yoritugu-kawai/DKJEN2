#include "FirstScene.h"

void FirstScene::Initialize()
{
	time = 12;
	uint32_t tex = TexManager::LoadTexture("GameResource/black.png");
	sprite = new Sprite;
	sprite->Initialize(tex);
	color = { 1.0f,1.0f,1.0f,1.0f };
}

void FirstScene::Update(GameManager* gameManager)
{



	//color.w -= 0.1f;
#ifdef _DEBUG
	ImGui::Begin("Color");
	ImGui::DragFloat4("c", &color.x, 0.1f, -1.0f, 1.0f);
	

	ImGui::End();
#endif // _DEBUG
	/*if (color.w < 0) {
		
			gameManager->ChangeState(new StartSeen);

		
	}*/

}

void FirstScene::Draw()
{
	sprite->Draw({ 128,72,0 }, { 0,0,0 }, { 0,0,0 }, color);
}
