#include "clearScene.h"

void clearScene::Initialize()
{
	time = 12;
}

void clearScene::Update(GameManager* gameManager)
{
	time -= 1;
	if (time < 0) {
		if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
			gameManager->ChangeState(new StartSeen);

		}
	}
}

void clearScene::Draw()
{
}
