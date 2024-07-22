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
	uint32_t skyBoxHandle_ = TexManager::LoadTexture("rostock_laage_airport_4k.dds");
	sky->Initialize(skyBoxHandle_);
	worldTransform = new WorldTransform;
	worldTransform->Create();
}

void GameScene::Update()
{
	LevelData->Update(cameraData);
	cameraData->Update();

	//////
	//　　描画処理
	worldTransform->UpdateMatrix(cameraData);

}

void GameScene::Draw()
{
	sky->Draw(cameraData, worldTransform);
	//////
	LevelData->Draw(cameraData);
}
