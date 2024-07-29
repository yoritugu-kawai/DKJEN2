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
	cRot = { 0.2f,-0.2f,0.0f };
	cPos = { 0.0f,3.0f,-20.0f };

	//
	tPos_ = { 0.0f,0.0f,0.0f };
	speed_= 0.01f;
}

void PlaySeen::LoadBlockPopData() {


}

void PlaySeen::UpdateBlockPopCommands() {

	
}

void PlaySeen::AllCollisions() {
	
}
void PlaySeen::Update(GameManager* gameManager)
{
	animaionTime += 1.0f / 60.0f;
	LevelData->Update(cameraData);
	cameraData->Update();
	//cameraAnime->Update();
	
	cameraData->SetTranslate(cPos);
	cameraData->SetRotate(cRot);


	cRot = cameraData->GetRotate();
	cPos = cameraData->GetTranslate();
	ImGui::Begin("camera");
	ImGui::DragFloat3("c", &cRot.x, 1.0f, -100.0f, 100.0f);
	ImGui::DragFloat3("p", &cPos.x, 1.0f, -1000.0f, 100.0f);
	ImGui::End();

	ImGui::Begin("Speed");
	ImGui::DragFloat("c", &speed_, 1.0f, -100.0f, 100.0f);
	
	ImGui::End();

	ImGui::Begin("pos");
	ImGui::DragFloat3("c", &tPos_.x, 1.0f, -100.0f, 100.0f);

	ImGui::End();
	tPos_.z += speed_;
	cPos.z += speed_;
	//cPos.y += 0.01;
	worldTransform->SetTranslate(tPos_);

	worldTransform->UpdateMatrix(cameraData);
	////Animation
	bone->ApplyAnimation(skeleton, animatio, animaionTime);
	//Skeleton

	bone->Update(skeleton);
	//SkinCluster

	skin->SkinUpdate(skinCluster, skeleton);
	/////////
	time -= 1;
	if (time < 0) {
		if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
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
