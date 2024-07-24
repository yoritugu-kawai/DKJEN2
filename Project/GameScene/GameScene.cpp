#include "GameScene.h"

void GameScene::Initialize()
{
	cameraData = new CameraData;
	cameraData->Create();
	cameraData->Update();
	cameraData->SetRotate({ 0,0,0 });
	cameraData->SetTranslate({ 0,0,-200 });
	worldTransform = new WorldTransform;
	worldTransform->Create();

	LevelData = make_unique<JsonLoad>();
	LevelData->Load("resource/json/", "wood.json");

	skin =new Skinning;
	bone =new Bone;
	lod = new LoadObjManagement;
	
	walk3d = unique_ptr<Animation3D>();
	ModelData modelData_ = LoadObjManagement::NewLoadObjFile("resource/hu", "walk.gltf");

	animatio = lod->LoadAnimationFile("resource/hu", "walk.gltf");
	skeleton = bone->CreateSkeleton(modelData_.rootNode);
	skinCluster = skin->CreateSkinCluster(skeleton, modelData_);
	walk3d->Initialize(modelData_);
	
	///
	


}

void GameScene::Update()
{
	animaionTime += 1 / 60;
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
	worldTransform->UpdateMatrix(cameraData);
	//Animation
	bone->ApplyAnimation(skeleton, animatio, animaionTime);
	//Skeleton

	bone->Update(skeleton);
	//SkinCluster

	skin->SkinUpdate(skinCluster, skeleton);
	//////
	//　　描画処理

}

void GameScene::Draw()
{
	walk3d->Draw({ 1,1,1,1 }, cameraData, worldTransform, skinCluster);
	//////
	LevelData->Draw(cameraData);
}
