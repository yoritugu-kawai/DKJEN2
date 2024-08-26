#include "clearScene.h"

void clearScene::Initialize()
{
	uint32_t texClear = TexManager::LoadTexture("GameResource/clear.png");
	uint32_t texBlack = TexManager::LoadTexture("GameResource/black.png");
	spriteClear = new Sprite;
	spriteClear->Initialize(texClear);
	color = { 1.0f,1.0f,1.0f,1.0f };
	spriteBlack = new Sprite;
	spriteBlack->Initialize(texBlack);
}

void clearScene::Update(GameManager* gameManager)
{
	color.w -= 0.01f;
#ifdef _DEBUG
	ImGui::Begin("Color");
	ImGui::DragFloat4("c", &color.x, 0.1f, -1.0f, 1.0f);


	ImGui::End();
#endif // _DEBUG
	if (color.w < 0) {
		if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
			gameManager->ChangeState(new StartSeen);

		}
	}
}

void clearScene::Draw()
{
	spriteBlack->Draw({ 128,72,0 }, { 0,0,0 }, { 0,0,0 }, color);
	spriteClear->Draw({ 128,72,0 }, { 0,0,0 }, { 0,0,0 }, { 1.0f,1.0f,1.0f,1.0f });
}
