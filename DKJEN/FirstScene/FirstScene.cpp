#include "FirstScene.h"

void FirstScene::Initialize()
{
	//ロゴ
	time = 12;
	uint32_t texDKJEN = TexManager::LoadTexture("resource/DKJEN/DKJEN.png");
	uint32_t texBlack = TexManager::LoadTexture("GameResource/black.png");
	spriteDKJEN = new Sprite;
	spriteDKJEN->Initialize(texDKJEN);
	color = { 1.0f,1.0f,1.0f,1.0f };
	spriteBlack = new Sprite;
	spriteBlack->Initialize(texBlack);
}

void FirstScene::Update(GameManager* gameManager)
{



	color.w -= 0.01f;
#ifdef _DEBUG
	ImGui::Begin("Color");
	ImGui::DragFloat4("c", &color.x, 0.1f, -1.0f, 1.0f);
	

	ImGui::End();
#endif // _DEBUG
	if (color.w < 0) {
		
			gameManager->ChangeState(new StartSeen);

		
	}

}

void FirstScene::Draw()
{
	spriteBlack->Draw({ 128,72,0 }, { 0,0,0 }, { 0,0,0 }, {1.0f,1.0f,1.0f,1.0f});
	spriteDKJEN->Draw({ 128,72,0 }, { 0,0,0 }, { 0,0,0 }, color);
}

void FirstScene::ImGui()
{
}
