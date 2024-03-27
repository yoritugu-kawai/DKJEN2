#include "StartSeen.h"

void StartSeen::Initialize()
{
	cameraData_ = new CameraData;
	cameraData_->Create();
	//3Dモデル
	ball_ = new Obj3D;
	ball_->Initialize("resource", "ball.obj");

	axis_ = new Obj3D;
	axis_->Initialize("resource", "axis.obj");
	worldTransform = new WorldTransform;

	worldTransform->Create();
	//パーティクル
	uint32_t tex = TexManager::LoadTexture("resource/monsterBall.png");
	uint32_t tex2 = TexManager::LoadTexture("resource/space.png");
	particle = new Particle;

	particle->Initialize(tex2);

	particle2 = new Particle;

	particle2->Initialize(tex);
	//
	time = 12;
	ballPos = { 1,1,4.0f };
	particlePos_.scale = { 1.0f,1.0f,1.0f };
	particlePos_.rotate = { 0.0f,0.0f,0.0f };
	particlePos_.translate = { 0.0f,0.0f,0.0f };
	particlePos_.color = { 1.0f,1.0f,1.0f,1.0f };
}

void StartSeen::Update(GameManager* gameManager)
{
	cameraData_->Update();
	worldTransform->UpdateMatrix(cameraData_);
	cameraData_->SetTranslate(cameraPos);
	cameraData_->SetRotate(cameraRot);
	if (Input::GetInstance()->PushKey(DIK_D)) {
		cameraPos.x -= 0.1f;

	}
	if (Input::GetInstance()->PushKey(DIK_A)) {
		cameraPos.x += 0.1f;

	}

	if (Input::GetInstance()->PushKey(DIK_W)) {
		cameraPos.y -= 0.1f;

	}
	if (Input::GetInstance()->PushKey(DIK_S)) {
		cameraPos.y += 0.1f;

	}

	if (Input::GetInstance()->PushKey(DIK_UP)) {
		cameraRot.x += 0.1f;

	}
	if (Input::GetInstance()->PushKey(DIK_DOWN)) {
		cameraRot.x -= 0.1f;

	}

	worldTransform->SetTranslate(ballPos);
	time -= 1;
	if (time < 0) {
		if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
			gameManager->ChangeState(new PlaySeen);

		}
	}

}

void StartSeen::Draw()
{
	//
	ball_->Draw({ 1,1,1,1 }, cameraData_, worldTransform);
	axis_->Draw({ 1,1,1,1 }, cameraData_, worldTransform);
	//
	particle->Darw(particlePos_.scale, particlePos_.rotate, { 0.0f,0.0f,0.0f }, particlePos_.color);
	particle2->Darw(particlePos_.scale, particlePos_.rotate, { 3.0f,0.0f,0.0f }, particlePos_.color);
}
