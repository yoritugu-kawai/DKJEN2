#include "GameScene.h"

void GameScene::Initialize()
{

	gameManager_ = new GameManager;
	gameManager_->Initialize();
	
}

void GameScene::Update()
{
	
	////
	gameManager_->Update();
	
}

void GameScene::Draw()
{
	
	//////
	gameManager_->Draw();
}
