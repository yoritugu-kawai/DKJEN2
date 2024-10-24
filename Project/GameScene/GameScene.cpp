#include "GameScene.h"

void GameScene::Initialize()
{
	//初期化
	gameManager_ = new GameManager;
	gameManager_->Initialize();
	
}

void GameScene::Update()
{
	
	////更新
	gameManager_->Update();
	
}

void GameScene::Draw()
{
	
	//////描画
	gameManager_->Draw();
}
