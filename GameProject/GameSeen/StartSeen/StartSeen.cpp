#include "StartSeen.h"

void StartSeen::Initialize()
{
	time = 12;
	uint32_t tex = TexManager::LoadTexture("GameResource/title.png");
	sprite = new Sprite;
	sprite->Initialize(tex);
	color = { 1.0f,1.0f,1.0f,1.0f };
	uint32_t texBlack = TexManager::LoadTexture("GameResource/black.png");
	spriteBlack = new Sprite;
	spriteBlack->Initialize(texBlack);
}

void StartSeen::Update(GameManager* gameManager)
{
	

	
	color.w -= 0.01f;
#ifdef _DEBUG
	ImGui::Begin("Color");
	ImGui::DragFloat4("c", &color.x, 0.1f, -1.0f, 1.0f);


	ImGui::End();
#endif // _DEBUG

	if (color.w < 0) {
		if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
			gameManager->ChangeState(new SelectScene);

		}
	}

}

void StartSeen::Draw()
{
	sprite->Draw({128,72,0},{0,0,0},{0,0,0},{1.0f,1.0f,1.0f,1.0f});
	spriteBlack->Draw({ 128,72,0 }, { 0,0,0 }, { 0,0,0 }, color);
}
