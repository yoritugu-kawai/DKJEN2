#include "StartSeen.h"

void StartSeen::Initialize()
{
	time = 12;
	uint32_t tex = TexManager::LoadTexture("");
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
	
}
