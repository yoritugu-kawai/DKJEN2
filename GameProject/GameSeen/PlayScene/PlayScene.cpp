#include "PlayScene.h"

void PlayScene::Initialize()
{
	
	time = 12;
	/////
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
	skin = new Skinning;
	bone = new Bone;
	lod = new LoadObjManagement;

	walk3d = make_unique<Animation3D>();
	ModelData modelData_ = LoadObjManagement::NewLoadObjFile("resource/hu", "walk.gltf");

	animatio = lod->LoadAnimationFile("resource/hu", "walk.gltf");
	skeleton = bone->CreateSkeleton(modelData_.rootNode);
	skinCluster = skin->CreateSkinCluster(skeleton, modelData_);
	walk3d->Initialize(modelData_);
	cRot = { 0.0f,-0.0f,0.0f };

	cPos = { 0.0f,10.0f,-20.0f };

	//
	tPos_ = { 0.0f,0.0f,0.0f };
	tRot = { 0,0,0 };
	speed_= 0.1f;
	//
	dKey = new Sprite;
	uint32_t dTex = TexManager::LoadTexture("GameResource/D.png");
	dKey->Initialize(dTex);
	uint32_t aTex = TexManager::LoadTexture("GameResource/A.png");
	aKey = new Sprite;
	aKey->Initialize(aTex);

}


void PlayScene::AllCollisions(GameManager* gameManager) {
	for (auto& obj1 : LevelData->GetObjects()) {
		auto& it = obj1.second;
	
			if (it.center.x - it.size.x / 3.2 < tPos_.x + worldTransform->GetScale().x / 3 &&
				it.center.x + it.size.x / 3.2 > tPos_.x - worldTransform->GetScale().x / 3 &&
				it.center.y - it.size.y / 3.2 < tPos_.y + worldTransform->GetScale().y / 3 &&
				it.center.y + it.size.y / 3.2 > tPos_.y - worldTransform->GetScale().y / 3 &&
				it.center.z - it.size.z / 3.2 < tPos_.z + worldTransform->GetScale().z / 3 &&
				it.center.z + it.size.z / 3.2 > tPos_.z - worldTransform->GetScale().z / 3) {
				// 衝突処理
				tPos_.z = 0;
				cPos.z = 0;
			}
		
	}
}

void PlayScene::Update(GameManager* gameManager)
{
	animaionTime += 2.0f / 60.0f;
	LevelData->Update(cameraData);
	cameraData->Update();
	//cameraAnime->Update();
	
	AllCollisions(gameManager);

#ifdef _DEBUG

	ImGui::Begin("camera");
	ImGui::DragFloat3("c", &cRot.x, 0.1f, -100.0f, 100.0f);
	ImGui::DragFloat3("p", &cPos.x, 1.0f, -1000.0f, 100.0f);
	ImGui::End();

	ImGui::Begin("Speed");
	ImGui::DragFloat("c", &speed_, 1.0f, -100.0f, 100.0f);

	ImGui::End();

	ImGui::Begin("pos");
	ImGui::DragFloat3("p", &tPos_.x, 0.1f, -100.0f, 100.0f);
	ImGui::DragFloat3("r", &tRot.x, 0.1f, -100.0f, 100.0f);
	ImGui::End();

#endif // _DEBUG

	cameraData->SetTranslate(cPos);
	cameraData->SetRotate(cRot);

	cRot = cameraData->GetRotate();
	cPos = cameraData->GetTranslate();

	
	tPos_.z += speed_;
	cPos.z += speed_;
	
	worldTransform->SetTranslate(tPos_);
	worldTransform->SetRotate(tRot);
	worldTransform->UpdateMatrix(cameraData);
	////Animation
	bone->ApplyAnimation(skeleton, animatio, animaionTime);
	//Skeleton

	bone->Update(skeleton);
	//SkinCluster

	skin->SkinUpdate(skinCluster, skeleton);
	/////////

	if (Input::GetInstance()->PushKey(DIK_A)) {
		tRot.z += 0.1f;
		cRot.z += 0.1f;

	}
	if (Input::GetInstance()->PushKey(DIK_D)) {
		tRot.z -= 0.1f;
		cRot.z -= 0.1f;
	}

	
	time -= 1;
	/*if (time < 0) {
		if (worldTransform->GetTranslate().z>=234.0f) {
			gameManager->ChangeState(new StartSeen);

		}
	}*/
}

void PlayScene::Draw()
{
	LevelData->Draw(cameraData);
	//player->Draw({ 1,1,1,1 }, cameraData, worldTransform);
	walk3d->Draw({ 1,1,1,1 }, cameraData, worldTransform, skinCluster);

	//dKey->Draw({12.8f,12.8f,0,},{0,0,0}, { 130,580,0}, {1,1,1,1});
	//aKey->Draw({ 12.8f,12.8f,0, }, { 0,0,0 }, { 0,580,0 }, { 1,1,1,1 });
}
