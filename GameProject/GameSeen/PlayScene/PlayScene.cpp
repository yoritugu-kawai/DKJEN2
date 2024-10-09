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
	ModelData modelData_ = LoadObjManagement::NewLoadObjFile("resource/hu", "Run.gltf");

	animatio = lod->LoadAnimationFile("resource/hu", "Run.gltf");
	skeleton = bone->CreateSkeleton(modelData_.rootNode);
	skinCluster = skin->CreateSkinCluster(skeleton, modelData_);
	walk3d->Initialize(modelData_);
	cRot = { 0.0f,-0.0f,0.0f };

	cPos = { 0.0f,9.0f,11.0f };

	//
	tPos_ = { 0.0f,0.0f,0.0f };
	tRot = { 0,0,0 };
	speed_ = 0.5f;
	//
	dKey = new Sprite;
	uint32_t dTex = TexManager::LoadTexture("GameResource/D.png");
	dKey->Initialize(dTex);
	uint32_t aTex = TexManager::LoadTexture("GameResource/A.png");
	aKey = new Sprite;
	aKey->Initialize(aTex);

	objectData = std::make_unique<Obj3D>();
	sphereWorldTransform_ = new WorldTransform();

	sphereWorldTransform_->Create();
	sphereWorldTransform_->SetScale({ 1.0f,1.0f,1.0f });

	ModelData boxData_ = LoadObjManagement::NewLoadObjFile("resource/Sphere/", "Sphere.obj");
	objectData->Initialize(boxData_);
}




void PlayScene::AllCollisions() {
	for (auto& obj1 : LevelData->GetObjects()) {
		auto& it = obj1.second;


		if (it.fileName == "wood.obj") {
			continue;
		}


		float left = static_cast<float>(it.center.x - it.size.x / 3.2 + it.worldTransform_->GetTranslate().x);
		float right = static_cast<float>(it.center.x + it.size.x / 3.2 + it.worldTransform_->GetTranslate().x);
		float down = static_cast<float>(it.center.y - it.size.y / 3.2 + it.worldTransform_->GetTranslate().y);
		float up = static_cast<float>(it.center.y + it.size.y / 3.2 + it.worldTransform_->GetTranslate().y);
		float front = static_cast<float>(it.center.z - it.size.z / 3.2 + it.worldTransform_->GetTranslate().z);
		float back = static_cast<float>(it.center.z + it.size.z / 3.2 + it.worldTransform_->GetTranslate().z);


#ifdef _DEBUG
		ImGui::Begin("Branch");
		ImGui::InputFloat("Left", &left);
		ImGui::InputFloat("Right", &right);
		ImGui::InputFloat("Down", &down);
		ImGui::InputFloat("Up", &up);
		ImGui::InputFloat("Front", &front);
		ImGui::InputFloat("Back", &back);


		ImGui::End();
#endif // _DEBUG


#ifdef _DEBUG
		ImGui::Begin("Player");
		Vector3 playerTranslate = worldTransform->GetTranslate();
		ImGui::InputFloat3("tPos", &tPos_.x);
		ImGui::InputFloat3("Translate", &playerTranslate.x);
		ImGui::End();
#endif // _DEBUG



		down;
		up;
		//+ worldTransform->GetScale().x / 3

		//down < tPos_.y&&
			//up > tPos_.y&&

		Vector3 sphereWorldPosition = {
			sphereWorldTransform_->GetMatWorld_().m[3][0],
		sphereWorldTransform_->GetMatWorld_().m[3][1],
		sphereWorldTransform_->GetMatWorld_().m[3][2] };

		if (left < sphereWorldPosition.x &&
			right > sphereWorldPosition.x) {
			isInsideX = true;
			
		}
		else {
			isInsideX = false;
		}

		if (isInsideX == true) {
			if (front <sphereWorldPosition.z &&
				back> sphereWorldPosition.z) {
				isInsideZ = true;
				tPos_.z = 0;
				cPos.z = 0;
			}
			else {
				isInsideZ = false;
			}
		}
		

#ifdef _DEBUG
		ImGui::Begin("IsInside");
		ImGui::Checkbox("X", &isInsideX);
		ImGui::Checkbox("Z", &isInsideZ);

		ImGui::End();
#endif // _DEBUG


		if (left < tPos_.x &&
			right > tPos_.x &&
			front < tPos_.z &&
			back> tPos_.z) {
			// 衝突処理
			//tPos_.z = 0;
			//cPos.z = 0;
		}

	}
}

void PlayScene::Operation()
{

	const float ROTATE_INTERVAL = 0.01f;

	if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
		rotateTheta_ -= ROTATE_INTERVAL;
		tRot.z -= ROTATE_INTERVAL;
		//tPos_.x -= ROTATE_INTERVAL;

	}
	if (Input::GetInstance()->PushKey(DIK_LEFT)) {
		rotateTheta_ += ROTATE_INTERVAL;
		tRot.z += ROTATE_INTERVAL;
		//tPos_.x += ROTATE_INTERVAL;
	}
	if (Input::GetInstance()->PushKey(DIK_A)) {
		rotateTheta_ += ROTATE_INTERVAL;
		tRot.z += ROTATE_INTERVAL;

	}
	if (Input::GetInstance()->PushKey(DIK_D)) {
		rotateTheta_ -= ROTATE_INTERVAL;
		tRot.z -= ROTATE_INTERVAL;
	}

}

void PlayScene::Update(GameManager* gameManager)
{
	animaionTime += 2.0f / 60.0f;
	LevelData->Update(cameraData);
	cameraData->Update();
	//cameraAnime->Update();

	AllCollisions();

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



	///////////////////////Sphereで改善策を考える

	const float RADIUS = 8.0f;

	Operation();
	Vector3 sphereNewTranslate = {};

	sphereNewTranslate.x = std::cosf(rotateTheta_ + std::numbers::pi_v<float> / 2.0f) * RADIUS;
	sphereNewTranslate.y = std::sinf(rotateTheta_ + std::numbers::pi_v<float> / 2.0f) * RADIUS;
	sphereNewTranslate.z = tPos_.z;



#ifdef _DEBUG
	ImGui::Begin("Sphere");
	ImGui::InputFloat3("Translate", &sphereNewTranslate.x);
	ImGui::End();
#endif // _DEBUG



	sphereWorldTransform_->SetTranslate(sphereNewTranslate);

	cRot.z = rotateTheta_;
	/*cPos.x = sphereNewTranslate.x;
	cPos.y = sphereNewTranslate.y;*/
	const float CAMERA_OFFSET_DISTANCE = -10.0f;
	cPos.z = sphereNewTranslate.z + CAMERA_OFFSET_DISTANCE;


	worldTransform->SetTranslate(tPos_);
	worldTransform->SetRotate(tRot);
	worldTransform->UpdateMatrix(cameraData);
	////Animation
	bone->ApplyAnimation(skeleton, animatio, animaionTime);
	//Skeleton

	bone->Update(skeleton);
	//SkinCluster

	skin->SkinUpdate(skinCluster, skeleton);
	

	//ワールドトランスフォームの更新

	sphereWorldTransform_->UpdateMatrix(cameraData);



	if (worldTransform->GetTranslate().z >= 234.0f) {
		gameManager->ChangeState(new clearScene);

	}
}



void PlayScene::Draw()
{
	LevelData->Draw(cameraData);
	//player->Draw({ 1,1,1,1 }, cameraData, worldTransform);
	walk3d->Draw({ 1,1,1,1 }, cameraData, worldTransform, skinCluster);


	//objectData->Draw({ 1,1,1,1 }, cameraData, sphereWorldTransform_);


	dKey->Draw({12.8f,12.8f,0,},{0,0,0}, { 130,580,0}, {1,1,1,1});
	aKey->Draw({ 12.8f,12.8f,0, }, { 0,0,0 }, { 0,580,0 }, { 1,1,1,1 });
}

void PlayScene::ImGui()
{
}
