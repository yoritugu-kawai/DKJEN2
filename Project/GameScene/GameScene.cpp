#include "GameScene.h"

void GameScene::Initialize()
{
	cameraData = new CameraData;
	cameraData->Create();

	LevelData = make_unique<JsonLoad>();
	LevelData->Load("resource/json/", "wood.json");

	skin = unique_ptr <Skinning>();
	bone = unique_ptr <Bone>();
	lod =  unique_ptr <LoadObjManagement>();
	
	walk3d = unique_ptr<Animation3D>();
	ModelData modelData_ = LoadObjManagement::NewLoadObjFile("resource/hu", "walk.gltf");

	 animatio = lod->LoadAnimationFile("resource/hu", "walk.gltf");
	 skeleton = bone->CreateSkeleton(modelData_.rootNode);
	  skinCluster = skin->CreateSkinCluster(skeleton, modelData_);
	walk3d->Initialize(modelData_);
	
	///
	cameraData->Update();
	cameraData->SetRotate({ 0,0,0 });
	cameraData->SetTranslate({ 0,0,-200 });
	worldTransform = new WorldTransform;
	worldTransform->Create();


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
	//Animation
	bone->ApplyAnimation(skeleton, animatio, animaionTime);
	//Skeleton

	bone->Update(skeleton);
	//SkinCluster

	skin->SkinUpdate(skinCluster, skeleton);
	//////
	//　　描画処理
	worldTransform->UpdateMatrix(cameraData);

}

void GameScene::Draw()
{

	//////
	LevelData->Draw(cameraData);
}
