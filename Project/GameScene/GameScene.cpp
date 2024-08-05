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
	skyWorldTransform->SetScale({ 20.0f,20.0f,20.0f });

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
	cPos = { 0.0f,0.0f,-20.0f };
}

void GameScene::Update()
{
	animaionTime += 1.0f / 60.0f;
	
	
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

	const float MOVE = 0.05f;
	if(Input::GetInstance()->PushKey(DIK_UP) == true) {
		cPos.y += MOVE;
	}
	if (Input::GetInstance()->PushKey(DIK_DOWN) == true) {
		cPos.y -= MOVE;
	}
	if (Input::GetInstance()->PushKey(DIK_RIGHT) == true) {
		cPos.x += MOVE;
	}
	if (Input::GetInstance()->PushKey(DIK_LEFT) == true) {
		cPos.x -= MOVE;
	}
	if (Input::GetInstance()->PushKey(DIK_W) == true) {
		cPos.z += MOVE;
	}
	if (Input::GetInstance()->PushKey(DIK_S) == true) {
		cPos.z -= MOVE;
	}

	cameraData->SetTranslate(cPos);
	cameraData->SetRotate(cRot);


	cRot = cameraData->GetRotate();
	cPos = cameraData->GetTranslate();

	cameraData->Update();

	Matrix4x4 vp = Multiply(cameraData->GetView(), cameraData->GetProjection());

	ImGui::Begin("camera");
	ImGui::DragFloat3("c", &cRot.x, 0.01f, -3.0f, 13.0f);
	ImGui::DragFloat3("p", &cPos.x, 0.01f, -1000.0f, 100.0f);
	ImGui::End();

	
}

void GameScene::Draw()
{
	sky->Draw(cameraData, skyWorldTransform);
	//////
	//gameManager_->Draw();
	walk3d->Draw({ 1,1,1,1 }, cameraData, worldTransform, skinCluster);
}
