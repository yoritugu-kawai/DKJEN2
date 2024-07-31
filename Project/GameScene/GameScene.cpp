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
	
	sky = make_unique<SkyBox>();
	uint32_t skyBoxHandle_ = TexManager::DDSLoadTexture("rostock_laage_airport_4k.dds");
	sky->Initialize(skyBoxHandle_);
	skyWorldTransform = new WorldTransform;
	skyWorldTransform->Create();
	skyWorldTransform->SetScale({ 32.0f,32.0f,32.0f });

	worldTransform = new WorldTransform;
	worldTransform->Create();
	worldTransform->SetRotate({ 0.0f,2.0f,0.0f });
	skin = new Skinning;
	bone = new Bone;
	lod = new LoadObjManagement;

	walk3d = make_unique<Animation3D>();
	ModelData modelData_ = LoadObjManagement::NewLoadObjFile("resource/hu", "walk.gltf");

	animatio = lod->LoadAnimationFile("resource/hu", "walk.gltf");
	skeleton = bone->CreateSkeleton(modelData_.rootNode);
	skinCluster = skin->CreateSkinCluster(skeleton, modelData_);
	walk3d->Initialize(modelData_);
	walk3d->SetEviromentTexture(skyBoxHandle_);
	/*gameManager_ = new GameManager;
	gameManager_->Initialize();*/
	cPos = { 0.0f,3.0f,-20.0f };
}

void GameScene::Update()
{
	animaionTime += 1.0f / 60.0f;
	
	cameraData->Update();

	skyWorldTransform->UpdateMatrix(cameraData);
	worldTransform->UpdateMatrix(cameraData);
	bone->ApplyAnimation(skeleton, animatio, animaionTime);
	//Skeleton

	bone->Update(skeleton);
	//SkinCluster

	skin->SkinUpdate(skinCluster, skeleton);
	/////////
	
	////
	//gameManager_->Update();
	cameraData->SetTranslate(cPos);
	cameraData->SetRotate(cRot);


	cRot = cameraData->GetRotate();
	cPos = cameraData->GetTranslate();
	ImGui::Begin("camera");
	ImGui::DragFloat3("c", &cRot.x, 1.0f, -100.0f, 100.0f);
	ImGui::DragFloat3("p", &cPos.x, 1.0f, -1000.0f, 100.0f);
	ImGui::End();

	
}

void GameScene::Draw()
{
	sky->Draw(cameraData, skyWorldTransform);
	//////
	//gameManager_->Draw();
	walk3d->Draw({ 1,1,1,1 }, cameraData, worldTransform, skinCluster);
}
