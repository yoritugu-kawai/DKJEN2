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
	playerPos_ = { 0.0f,0.0f,0.0f };
	playerRot = { 0,0,0 };
	speed_ = 1.0f;
	//カウントダウン
	count3 = new Sprite;
	uint32_t Tex3 = TexManager::LoadTexture("GameResource/Play/3.png");
	count3->Initialize(Tex3);
	uint32_t Tex2 = TexManager::LoadTexture("GameResource/Play/2.png");
	count2 = new Sprite;
	count2->Initialize(Tex2);
	uint32_t Tex1 = TexManager::LoadTexture("GameResource/Play/1.png");
	count1 = new Sprite;
	count1->Initialize(Tex1);

	//ダッシュ
	ran3 = new Sprite;
	uint32_t ranTex3 = TexManager::LoadTexture("GameResource/Play/ran3.png");
	ran3->Initialize(ranTex3);
	uint32_t ranTex2 = TexManager::LoadTexture("GameResource/Play/ran2.png");
	ran2 = new Sprite;
	ran2->Initialize(ranTex2);
	uint32_t ranTex1 = TexManager::LoadTexture("GameResource/Play/ran1.png");
	ran1 = new Sprite;
	ran1->Initialize(ranTex1);
	//プレイヤー
	objectData = std::make_unique<Obj3D>();
	sphereWorldTransform_ = make_unique< WorldTransform>();

	sphereWorldTransform_->Create();
	sphereWorldTransform_->SetScale({ 1.0f,1.0f,1.0f });
	color = { 1,1,1,1 };
	ModelData boxData_ = LoadObjManagement::NewLoadObjFile("resource/Sphere/", "Sphere.obj");
	objectData->Initialize(boxData_);
	// カウントダウン
	countdown = 3;
	startTime = 1.5f;
	change = 1;

	//後ろに下がる
	back = 15;
	damagCeolor = { 1,0,0,1 };
}




void PlayScene::AllCollisions() {
	// 衝突処理
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
		ImGui::InputFloat3("tPos", &playerPos_.x);
		ImGui::InputFloat3("Translate", &playerTranslate.x);
		ImGui::End();
#endif // _DEBUG



		down;
		up;
		
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
				playerPos_.z -= back;
				cPos.z -= back;
				speed_ = 0;
				startTime = 0;
				color = damagCeolor;
				change = 0;
				
			}
			else {
				isInsideZ = false;
			
				
			}
			
		}
		startTime += 0.1f;
		if (speed_<=0.91f) {
			if (startTime > 50) {

				speed_ += 0.0003f;
				
			}
		}
		if (speed_>=0.9f) {
			speed_ = 1.0f;
			color = { 1,1,1,1 };
			change = 1;
			
		}

#ifdef _DEBUG
		ImGui::Begin("IsInside");
		ImGui::Checkbox("X", &isInsideX);
		ImGui::Checkbox("Z", &isInsideZ);

		ImGui::End();
#endif // _DEBUG


		//if (left <  playerPos_.x &&
		//	right > playerPos_.x &&
		//	front < playerPos_.z &&
		//	back> playerPos_.z) {
		//	// 衝突処理
		//	//tPos_.z = 0;
		//	//cPos.z = 0;
		//}

	}
}

void PlayScene::Operation()
{

	const float ROTATE_INTERVAL = 0.01f;

	if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
		if (playerRot.z>=-0.68f) {
			rotateTheta_ -= ROTATE_INTERVAL;
			playerRot.z -= ROTATE_INTERVAL;
		}
		
		//tPos_.x -= ROTATE_INTERVAL;

	}
	if (Input::GetInstance()->PushKey(DIK_LEFT)) {
		if (playerRot.z <= 0.95f) {
			rotateTheta_ += ROTATE_INTERVAL;
			playerRot.z += ROTATE_INTERVAL;
			//tPos_.x += ROTATE_INTERVAL;
		}
	}
	if (Input::GetInstance()->PushKey(DIK_A)) {
		rotateTheta_ += ROTATE_INTERVAL;
		playerRot.z += ROTATE_INTERVAL;

	}
	if (Input::GetInstance()->PushKey(DIK_D)) {
		rotateTheta_ -= ROTATE_INTERVAL;
		playerRot.z -= ROTATE_INTERVAL;
	}

}

void PlayScene::Move()
{
	//0.96,-0.7
	animaionTime += 2.0f / 50.0f;
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
	ImGui::DragFloat3("p", &playerPos_.x, 0.1f, -100.0f, 100.0f);
	ImGui::DragFloat3("r", &playerRot.x, 0.1f, -100.0f, 100.0f);
	ImGui::End();

#endif // _DEBUG

	cameraData->SetTranslate(cPos);
	cameraData->SetRotate(cRot);

	cRot = cameraData->GetRotate();
	cPos = cameraData->GetTranslate();


	playerPos_.z += speed_;
	cPos.z += speed_;



	///////////////////////Sphereで改善策を考える

	const float RADIUS = 8.0f;

	Operation();
	Vector3 sphereNewTranslate = {};

	sphereNewTranslate.x = std::cosf(rotateTheta_ + std::numbers::pi_v<float> / 2.0f) * RADIUS;
	sphereNewTranslate.y = std::sinf(rotateTheta_ + std::numbers::pi_v<float> / 2.0f) * RADIUS;
	sphereNewTranslate.z = playerPos_.z;



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


	worldTransform->SetTranslate(playerPos_);
	worldTransform->SetRotate(playerRot);
	worldTransform->UpdateMatrix(cameraData);
	////Animation
	bone->ApplyAnimation(skeleton, animatio, animaionTime);
	//Skeleton

	bone->Update(skeleton);
	//SkinCluster

	skin->SkinUpdate(skinCluster, skeleton);


	//ワールドトランスフォームの更新

	sphereWorldTransform_->UpdateMatrix(cameraData);




}

void PlayScene::Update(GameManager* gameManager)
{
	countdown -= 1.0f/60;
	ranTime += 1.0f / 10;

	if (ranTime <= 3 && ranTime >= 2) {
		
		ranTime = 0;
	}
	
	//if (countdown<=0) {
		Move();
		
	//}
	if (worldTransform->GetTranslate().z >= 1400.0f) {
		gameManager->ChangeState(new clearScene);

	}
}



void PlayScene::Draw()
{
	//json
	LevelData->Draw(cameraData);
	//プレイヤー
	//player->Draw({ 1,1,1,1 }, cameraData, worldTransform);
	walk3d->Draw(color, cameraData, worldTransform, skinCluster);

	
	//objectData->Draw({ 1,1,1,1 }, cameraData, sphereWorldTransform_);
	//カウントダウン
	if (countdown <= 3&& countdown >= 2) {
		count3->Draw({32.0f,32.0f,0, }, { 0,0,0 }, { 480,260,0 }, { 1,1,1,1 });
	}
	if (countdown <= 2 && countdown >= 1) {
		count2->Draw({ 32.0f,32.0f,0, }, { 0,0,0 }, { 480,260,0 }, { 1,1,1,1 });
	}
	if (countdown <= 1 && countdown >= 0) {
		count1->Draw({ 32.0f,32.0f,0, }, { 0,0,0 }, { 480,260,0 }, { 1,1,1,1 });
	}
	//ダッシュ
	if (change==1) {

	if (ranTime <= 3 && ranTime >= 2) {
		ran3->Draw({ 128.0f,72.0f,0, }, { 0,0,0 }, { 0,0,0 }, { 1,1,1,1 });
	}
	if (ranTime <= 2 && ranTime >= 1) {
		ran2->Draw({ 128.0f,72.0f,0, }, { 0,0,0 }, { 0,0,0 }, { 1,1,1,1 });
	}
	if (ranTime <= 1 && ranTime >= 0) {
		ran1->Draw({ 128.0f,72.0f,0, }, { 0,0,0 }, { 0,0,0 }, { 1,1,1,1 });
	}
	}

}

void PlayScene::ImGui()
{
}

