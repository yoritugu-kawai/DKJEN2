#include "PlaySeen.h"

void PlaySeen::Initialize()
{
	uv = new Sprite;
	uint32_t uvTex = TexManager::LoadTexture("resource/uvChecker.png");
	uv->Initialize(uvTex);
	ball = new Sprite;
	uint32_t ballTex = TexManager::LoadTexture("resource/monsterBall.png");
	ball->Initialize(ballTex);
	time = 12;
}

void PlaySeen::Update(GameManager* gameManager)
{
	time -= 1;
	if (time < 0) {
		if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
			gameManager->ChangeState(new StartSeen);

		}
	}


}

void PlaySeen::Draw()
{
	uv->Draw({ 20.0f,20.0f,1 }, { 0,0,0 }, { 1,1,1 }, { 1.0f,1.0f,1.0f,1.0f });
	ball->Draw({ 20.0f,20.0f,1 }, { 0,0,0 }, { 200,1,1 }, { 1.0f,1.0f,1.0f,1.0f });
}
