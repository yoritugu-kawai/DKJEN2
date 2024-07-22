#include "GameScene.h"

void GameScene::Initialize()
{
	cameraData = new CameraData;
	cameraData->Create();

	LevelData = make_unique<JsonLoad>();
	LevelData->Load("resource/json/", "test.json");

	cameraData->SetTranslate(Vector3(0.0f, 2.0f, -32.0f));
	cameraData->Update();

	sky = make_unique < SkyBox>();
	uint32_t skyBoxHandle_ = ImageLoading::LoadTexture("rostock_laage_airport_4k.dds");
	sky->Initialize();
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
