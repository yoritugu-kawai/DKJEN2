#include "PlayScene.h"

void PlayScene::Initialize()
{

	time = 12;
	/////カメラ
	/*
	初期化
	更新
	セッター回転
	セッター座標
	*/
	cameraData = new CameraData;
	cameraData->Create();
	cameraData->Update();
	cameraData->SetRotate({ 0,0,0 });
	cameraData->SetTranslate({ 0,0,-20 });
	worldTransform =  WorldTransform;
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
	ROTATE_INTERVAL = 0.01f;
	///2D画像
	uint32_t texA = TexManager::LoadTexture("GameResource/Play/ki/A.png");
	spriteA = make_unique <Sprite>();
	spriteA->Initialize(texA);

	uint32_t texAKi = TexManager::LoadTexture("GameResource/Play/ki/Aki.png");
	spriteAKi = make_unique <Sprite>();
	spriteAKi->Initialize(texAKi);

	uint32_t texD = TexManager::LoadTexture("GameResource/Play/ki/D.png");
	spriteD = make_unique <Sprite>();
	spriteD->Initialize(texD);
	
	uint32_t texBKi = TexManager::LoadTexture("GameResource/Play/ki/Dki.png");
	spriteDKi = make_unique <Sprite>();
	spriteDKi->Initialize(texBKi);

	uint32_t texSPACE = TexManager::LoadTexture("GameResource/Play/ki/Space.png");
	spriteSPACE = make_unique <Sprite>();
	spriteSPACE->Initialize(texSPACE);
	
	uint32_t texSPACEKi = TexManager::LoadTexture("GameResource/Play/ki/Spaceki.png");
	spriteSPACEKi = make_unique <Sprite>();
	spriteSPACEKi->Initialize(texSPACEKi);


	// カウントダウン
	countdown = 3;
	startTime = 1.5f;
	change = 1;

	//後ろに下がる
	backDamag = 15;
	damagCeolor = { 1,0,0,1 };
	//そうさ　
	normalTime = 2.0f / 50.0f;
	actionTime = 2.0f / 200.0f;
	standardTime = 0;
	standardSpeed_ = 0.0f;
	normalSpeed_ = 1.0f;
	actionSpeed_ = 0.1f;
	///
	countdownBox = 1.0f / 60;
	ranTimeBox = 1.0f / 10;
	clear = 1400.0f;
}




void PlayScene::AllCollisions() {
	// 衝突処理
	for (auto& obj1 : LevelData->GetObjects()) {
		auto& it = obj1.second;



		//当たるオブジェクトの指定
		if (it.fileName == "wood.obj") {
			continue;
		}

		//それぞれの座標
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


		//デバック用
		down;
		up;
		//座標のまとめ
		Vector3 sphereWorldPosition = {
			sphereWorldTransform_->GetMatWorld_().m[3][0],
		sphereWorldTransform_->GetMatWorld_().m[3][1],
		sphereWorldTransform_->GetMatWorld_().m[3][2] };
		//条件式
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
				playerPos_.z -= backDamag;
				cPos.z -= backDamag;
				standardSpeed_ = 0;
				startTime = 0;
				color = damagCeolor;
				change = 0;
				
			}
			else {
				isInsideZ = false;
			
				
			}
			
		}

		//当たった時の後ろに下がる処理
		if (change == 0) {
			startTime += 0.1f;
			if (standardSpeed_ <= 0.91f) {
				if (startTime > 50) {

					standardSpeed_ += 0.0003f;

				}
			}
		}
		if (standardSpeed_ >=0.9f) {
			standardSpeed_ = 1.0f;
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
	//操作
	

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
		if (playerRot.z <= 0.95f) {
		
			rotateTheta_ += ROTATE_INTERVAL;
			playerRot.z += ROTATE_INTERVAL;
		}

	}
	if (Input::GetInstance()->PushKey(DIK_D)) {
		if (playerRot.z >= -0.68f) {
			rotateTheta_ -= ROTATE_INTERVAL;
			playerRot.z -= ROTATE_INTERVAL;
		}

	}

}

void PlayScene::Gimmick()
{
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		
		standardTime= actionTime;
		if (change == 1) {
			standardSpeed_ = actionSpeed_;
		}
	}
	else {
		
		standardTime= normalTime;
		if (change == 1) {
			standardSpeed_ = normalSpeed_;
		}
	}

}


void PlayScene::Move()
{
	Gimmick();
	//0.96,-0.7
	//アニメーション
	animaionTime += standardTime;
	LevelData->Update(cameraData);
	cameraData->Update();
	//cameraAnime->Update();
	
	//当たり判定
	AllCollisions();


	///座標
	cameraData->SetTranslate(cPos);
	cameraData->SetRotate(cRot);

	cRot = cameraData->GetRotate();
	cPos = cameraData->GetTranslate();

	//プレイヤーの動き
	playerPos_.z += standardSpeed_;
	cPos.z += standardSpeed_;



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
	//次の更新処理
	countdown -= countdownBox;
	ranTime += ranTimeBox;

	if (ranTime <= 3 && ranTime >= 2) {
		
		ranTime = 0;
	}
	
	//if (countdown<=0) {
		Move();
		
	//}
	if (worldTransform->GetTranslate().z >= clear) {
		gameManager->ChangeState(new clearScene);

	}
}



void PlayScene::Draw()
{
	Draw2D();
	//json
	LevelData->Draw(cameraData);
	//プレイヤー
	//player->Draw({ 1,1,1,1 }, cameraData, worldTransform);
	walk3d->Draw(color, cameraData, worldTransform, skinCluster);

	////UI
	spriteA->Draw({ 5.0f,5.0f,0, }, { 0,0,0 }, { 450,500,0 }, { 1,1,1,1 });
	spriteAKi->Draw({ 5.0f,5.0f,0, }, { 0,0,0 }, { 450,450,0 }, { 1,1,1,1 });
	spriteD->Draw({ 5.0f,5.0f,0, }, { 0,0,0 }, { 800,500,0 }, { 1,1,1,1 });
	spriteDKi->Draw({ 5.0f,5.0f,0, }, { 0,0,0 }, { 800,450,0 }, { 1,1,1,1 });

	spriteSPACE->Draw({ 5.0f,5.0f,0, }, { 0,0,0 }, { 630,250,0 }, { 1,1,1,1 });
	spriteSPACEKi->Draw({ 5.0f,5.0f,0, }, { 0,0,0 }, { 630,200,0 }, { 1,1,1,1 });


	//objectData->Draw({ 1,1,1,1 }, cameraData, sphereWorldTransform_);
	//カウントダウン
	if (countdown <= 3 && countdown >= 2) {
		count3->Draw({ 32.0f,32.0f,0, }, { 0,0,0 }, { 480,260,0 }, { 1,1,1,1 });
	}
	if (countdown <= 2 && countdown >= 1) {
		count2->Draw({ 32.0f,32.0f,0, }, { 0,0,0 }, { 480,260,0 }, { 1,1,1,1 });
	}
	if (countdown <= 1 && countdown >= 0) {
		count1->Draw({ 32.0f,32.0f,0, }, { 0,0,0 }, { 480,260,0 }, { 1,1,1,1 });
	}
	//ダッシュ
	if (change == 1) {

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
void PlayScene::Draw2D()
{
	
}

void PlayScene::ImGui()
{
#ifdef _DEBUG

	ImGui::Begin("camera");
	ImGui::DragFloat3("c", &cRot.x, 0.1f, -100.0f, 100.0f);
	ImGui::DragFloat3("p", &cPos.x, 1.0f, -1000.0f, 100.0f);
	ImGui::End();

	ImGui::Begin("Speed");
	ImGui::DragFloat("c", &standardSpeed_, 1.0f, -100.0f, 100.0f);

	ImGui::End();

	ImGui::Begin("pos");
	ImGui::DragFloat3("p", &playerPos_.x, 0.1f, -100.0f, 100.0f);
	ImGui::DragFloat3("r", &playerRot.x, 0.1f, -100.0f, 100.0f);
	ImGui::End();

#endif // _DEBUG
}

