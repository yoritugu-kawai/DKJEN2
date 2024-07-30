#include "StartSeen.h"

void StartSeen::Initialize()
{
	time = 12;
	uint32_t tex = TexManager::LoadTexture("GameResource/title.png");
	sprite = new Sprite;
	sprite->Initialize(tex);
}

void StartSeen::Update(GameManager* gameManager)
{
	

	
	time -= 1;
	if (time < 0) {
		if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
			gameManager->ChangeState(new PlaySeen);

		}
	}

}

void StartSeen::Draw()
{
	sprite->Draw({128,72,0},{0,0,0},{0,0,0},{1.0f,1.0f,0.0f,1.0f});
}
