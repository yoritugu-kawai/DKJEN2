#include "FirstScene.h"

void FirstScene::Initialize()
{
	time = 12;
	uint32_t tex = TexManager::LoadTexture("resource/DKJEN/DKJEN.png");
	sprite = new Sprite;
	sprite->Initialize(tex);
	color = { 1.0f,1.0f,1.0f,1.0f };
}

void FirstScene::Update(GameManager* gameManager)
{



	///color.w -= 0.1f;
	if (color.w < 0) {
		
			gameManager->ChangeState(new StartSeen);

		
	}

}

void FirstScene::Draw()
{
	sprite->Draw({ 128,72,0 }, { 0,0,0 }, { 0,0,0 }, color);
}
