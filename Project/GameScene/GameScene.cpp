#include "GameScene.h"

void GameScene::Initialize()
{
	cameraData = new CameraData;
	cameraData->Create();

	LevelData = make_unique<JsonLoad>();
	LevelData->Load("resource/json/", "test.json");

	cameraData->SetTranslate(Vector3(0.0f, 2.0f, -32.0f));
	cameraData->Update();
}

void GameScene::Update()
{
	LevelData->Update(cameraData);
	cameraData->Update();

	//////
	//　　描画処理


}

void GameScene::Draw()
{
	//////
	LevelData->Draw(cameraData);
}
