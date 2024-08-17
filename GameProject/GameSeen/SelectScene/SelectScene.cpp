#include "SelectScene.h"

void SelectScene::Initialize()
{
	time = 12;
}

void SelectScene::Update(GameManager* gameManager)
{
	time -= 1;
	if (time < 0) {
		if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
			gameManager->ChangeState(new PlayScene);

		}
	}
}

void SelectScene::Draw()
{
}

