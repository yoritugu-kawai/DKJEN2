#include "SelectScene.h"

void SelectScene::Initialize()
{
	time = 12;
	uint32_t tex = TexManager::LoadTexture("GameResource/black.png");
	sprite = new Sprite;
	sprite->Initialize(tex);

	uint32_t texSelect = TexManager::LoadTexture("GameResource/select.png");
	spriteSelect = new Sprite;
	spriteSelect->Initialize(texSelect);
	color = { 1.0f,1.0f,1.0f,1.0f };
	 speed= 0.01f;
}

void SelectScene::Update(GameManager* gameManager)
{

	color.w -= speed;
#ifdef _DEBUG
	ImGui::Begin("Color");
	ImGui::DragFloat4("c", &color.x, 0.1f, -1.0f, 1.0f);


	ImGui::End();
#endif // _DEBUG
	if (color.w < 0) {
		
			if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
				
				
				
					gameManager->ChangeState(new PlayScene);
			
			}
	}
}

void SelectScene::Draw()
{
	sprite->Draw({ 128,72,0 }, { 0,0,0 }, { 0,0,0 }, color);
	spriteSelect->Draw({ 128,72,0 }, { 0,0,0 }, { 0,0,0 },{1,1,1,1});
}

void SelectScene::ImGui()
{
}

