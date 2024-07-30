#include "PlaySeen.h"

void PlaySeen::Initialize()
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

	cPos = { 0.0f,3.0f,-20.0f };

	//
	tPos_ = { 0.0f,1.390f,0.0f };
	tRot = { 0,0,0 };
	speed_= 0.1f;
}

void PlaySeen::LoadBlockPopData() {


}

void PlaySeen::UpdateBlockPopCommands() {

	
}

void PlaySeen::AllCollisions() {
	
}
void PlaySeen::Update(GameManager* gameManager)
{
	animaionTime += 2.0f / 60.0f;
	LevelData->Update(cameraData);
	cameraData->Update();
	//cameraAnime->Update();
	
	cameraData->SetTranslate(cPos);
	cameraData->SetRotate(cRot);

#ifdef _DEBUG

	ImGui::Begin("camera");
	ImGui::DragFloat3("c", &cRot.x, 1.0f, -100.0f, 100.0f);
	ImGui::DragFloat3("p", &cPos.x, 1.0f, -1000.0f, 100.0f);
	ImGui::End();

	ImGui::Begin("Speed");
	ImGui::DragFloat("c", &speed_, 1.0f, -100.0f, 100.0f);

	ImGui::End();

	ImGui::Begin("pos");
	ImGui::DragFloat3("p", &tPos_.x, 1.0f, -100.0f, 100.0f);
	ImGui::DragFloat3("r", &tRot.x, 1.0f, -100.0f, 100.0f);
	ImGui::End();

#endif // _DEBUG



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
		cRot.z = 1;
		tPos_.x = -1.7f;
		tPos_.y = 1;
		tRot.z = 1;
	}
	if (Input::GetInstance()->PushKey(DIK_D)) {
		cRot.z = -1;
		tPos_.x = 1.7f;
		tPos_.y = 1;
		tRot.z = -1;
	}


	time -= 1;
	if (time < 0) {
		if (worldTransform->GetTranslate().z>=55.0f) {
			gameManager->ChangeState(new StartSeen);

		}
	}
}

void PlaySeen::Draw()
{
	LevelData->Draw(cameraData);
	//player->Draw({ 1,1,1,1 }, cameraData, worldTransform);
	walk3d->Draw({ 1,1,1,1 }, cameraData, worldTransform, skinCluster);
}
