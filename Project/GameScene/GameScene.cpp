#include "GameScene.h"

void GameScene::Initialize()
{
	cameraData = new CameraData;
	cameraData->Create();
	cameraData->Update();
	cameraData->SetRotate({ 0,0,0 });
	cameraData->SetTranslate({ 0,0,-20 });
	worldTransform = new WorldTransform;
	worldTransform->Create();

	LevelData = make_unique<JsonLoad>();
	LevelData->Load("resource/json/", "wood.json");
	///
	skin =new Skinning;
	bone =new Bone;
	lod = new LoadObjManagement;
	
	walk3d = make_unique<Animation3D>();
	ModelData modelData_ = LoadObjManagement::NewLoadObjFile("resource/hu", "walk.gltf");

	animatio = lod->LoadAnimationFile("resource/hu", "walk.gltf");
	skeleton = bone->CreateSkeleton(modelData_.rootNode);
	skinCluster = skin->CreateSkinCluster(skeleton, modelData_);
	walk3d->Initialize(modelData_);
	/*cameraAnime = new CameraData;
	cameraAnime->Create();
	cameraAnime->Update();
	cameraAnime->SetRotate({ 0,0,0 });
	cameraAnime->SetTranslate({ 0,0,-20 });*/
	
	///
	player = make_unique<Obj3D>();
	ModelData modelDat_ = LoadObjManagement::NewLoadObjFile("resource", "wood.obj");
	player->Initialize(modelDat_);


}

void GameScene::Update()
{
	animaionTime += 1.0f / 60.0f;
	LevelData->Update(cameraData);
	cameraData->Update();
	//cameraAnime->Update();
	cRot = cameraData->GetRotate();
	cPos = cameraData->GetTranslate();
	ImGui::Begin("camera");
	ImGui::DragFloat3("c", &cRot.x,1.0f, -100.0f, 100.0f);
	ImGui::DragFloat3("p", &cPos.x,1.0f, -1000.0f, 100.0f);
	ImGui::End();
	cameraData->SetTranslate(cPos);
	cameraData->SetRotate(cRot);
	worldTransform->UpdateMatrix(cameraData);
	////Animation
	bone->ApplyAnimation(skeleton, animatio, animaionTime);
	//Skeleton

	bone->Update(skeleton);
	//SkinCluster

	skin->SkinUpdate(skinCluster, skeleton);
	////
}

void GameScene::Draw()
{
	LevelData->Draw(cameraData);
	player->Draw({ 1,1,1,1 }, cameraData, worldTransform);
	walk3d->Draw({ 1,1,1,1 }, cameraData, worldTransform, skinCluster);
	//////
}
