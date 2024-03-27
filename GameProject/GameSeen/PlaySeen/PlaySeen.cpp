#include "PlaySeen.h"

void PlaySeen::Initialize()
{
	player_ = new Player;

	player_->Initialize();

	enemy_ = new Enemy;
	enemy_->Initialize();
}

void PlaySeen::Update(GameManager* gameManager)
{
	//gameManager;
	player_->Update();
	enemy_->Update();
	if (player_->GetBulletPos().x <= enemy_->GetPos().x + 10 &&
		enemy_->GetPos().x <= player_->GetBulletPos().x + 10 &&
		player_->GetBulletPos().y <= enemy_->GetPos().y + 10 &&
		enemy_->GetPos().y <= player_->GetBulletPos().y + 10) {
		des = true;
	}
	
}

void PlaySeen::Draw()
{
	if (des == false)
	{
		enemy_->Draw();
	}
	player_->Draw();
}
