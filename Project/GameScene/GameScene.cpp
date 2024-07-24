#include "GameScene.h"

void GameScene::Initialize()
{
	cameraData = new CameraData;
	cameraData->Create();

	LevelData = make_unique<JsonLoad>();
	LevelData->Load("resource/json/", "wood.json");

	
	cameraData->Update();

	cameraData->SetRotate({ 0,0,0 });
	cameraData->SetTranslate({ 0,0,-200 });
	worldTransform = new WorldTransform;
	worldTransform->Create();


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

	//////
	LevelData->Draw(cameraData);
}
