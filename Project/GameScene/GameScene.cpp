#include "GameScene.h"

void GameScene::Initialize()
{
	cameraData = new CameraData;
	cameraData->Create();

	LevelData = make_unique<JsonLoad>();
	LevelData->Load("resource/json/", "test.json");

	cameraData->SetTranslate(Vector3(0.0f, 2.0f, -32.0f));
	cameraData->Update();

	sky = make_unique<SkyBox>();
	uint32_t skyBoxHandle_ = TexManager::DDSLoadTexture("test.dds");
	sky->Initialize(skyBoxHandle_);
	worldTransform = new WorldTransform;
	worldTransform->Create();
	worldTransform->SetScale({ 32.0f,32.0f,32.0f });

}

void GameScene::Update()
{
	LevelData->Update(cameraData);
	cameraData->Update();
	cRot = cameraData->GetRotate();
	cPos = cameraData->GetTranslate();
	ImGui::Begin("camera");
	ImGui::SliderFloat3("c", &cRot.x, -100.0f, 100.0f);
	ImGui::SliderFloat3("p", &cPos.x, -1000.0f, 100.0f);
	ImGui::End();
	cameraData->SetTranslate(cPos);
	cameraData->SetRotate(cRot);

	//////
	//　　描画処理
	worldTransform->UpdateMatrix(cameraData);

}

void GameScene::Draw()
{
	sky->Draw(cameraData, worldTransform);
	//sky->Draw({10,10,10},{0,0,0},{0,0,0},{1,1,1,});
	//////
	LevelData->Draw(cameraData);
}
