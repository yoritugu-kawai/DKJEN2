#include "PlaySeen.h"

void PlaySeen::Initialize()
{
	player_ = new Player;
	player_->Initialize();
	time = 12;
	block_ = new Block;
	block_->Initialize({0,0,0});
}

void PlaySeen::Update(GameManager* gameManager)
{
	player_->Update();
	time -= 1;
	if (time < 0) {
		if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
			gameManager->ChangeState(new StartSeen);

		}
	}


}

void PlaySeen::Draw()
{
	player_->Draw();
	block_->Draw();
}
