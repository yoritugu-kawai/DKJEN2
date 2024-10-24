#include "GameScene.h"

void GameScene::Initialize()
{
	
	
	
	/*///
	player = make_unique<Obj3D>();
	ModelData modelDat_ = LoadObjManagement::NewLoadObjFile("resource", "wood.obj");
	player->Initialize(modelDat_);*/

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
