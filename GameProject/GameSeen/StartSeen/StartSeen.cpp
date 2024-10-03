#include "StartSeen.h"

void StartSeen::Initialize()
{
	//カメラ
	cameraData = new CameraData;
	cameraData->Create();
	
	cPos = { 0.04f,0.02f,-1 };

	time = 12;
	/*uint32_t tex = TexManager::LoadTexture("GameResource/title.png");
	sprite = new Sprite;
	sprite->Initialize(tex);
	color = { 1.0f,1.0f,1.0f,1.0f };*/
	uint32_t texBlack = TexManager::LoadTexture("GameResource/black.png");
	spriteBlack = new Sprite;
	spriteBlack->Initialize(texBlack);

	//モデル
	titleData_ = std::make_unique<Obj3D>();
	titleWorldTransform_ = new WorldTransform();
	titleWorldTransform_->Create();
	titleWorldTransform_->SetScale({ 0.1f,0.1f,0.1f });
	ModelData titleModel_ = LoadObjManagement::NewLoadObjFile("GameResource/Title/Obj", "Title.obj");
	titleData_->Initialize(titleModel_);
	///手裏剣
	shurikenData_ = std::make_unique<Obj3D>();
	shurikenWorldTransform_ = new WorldTransform();
	shurikenWorldTransform_->Create();
	shurikenWorldTransform_->SetScale({ 0.1f,0.1f,0.1f });
	ModelData shurikenModel_ = LoadObjManagement::NewLoadObjFile("GameResource/Title/Obj", "Shuriken.obj");
	shurikenData_->Initialize(shurikenModel_);
	shurikenPos = { -1.04f,0.09f,0.0f };
	///手裏剣2
	shurikenData2_ = std::make_unique<Obj3D>();
	shurikenWorldTransform2_ = new WorldTransform();
	shurikenWorldTransform2_->Create();
	shurikenWorldTransform2_->SetScale({ 0.1f,0.1f,0.1f });
	ModelData shurikenModel2_ = LoadObjManagement::NewLoadObjFile("GameResource/Title/Obj", "Shuriken.obj");
	shurikenData2_->Initialize(shurikenModel2_);
	shurikenPos2 = { -1.07f,0.1f,0.0f };
	//
	speed_ = 0.02;
	speed2_ = 0.02;
	stop_ = false;
}

void StartSeen::Update(GameManager* gameManager)
{
	cameraData->Update();
	titleWorldTransform_->UpdateMatrix(cameraData);
	shurikenWorldTransform_->UpdateMatrix(cameraData);
	shurikenWorldTransform2_->UpdateMatrix(cameraData);
	//color.w -= 0.01f;
#ifdef _DEBUG
	ImGui::Begin("Color");
	ImGui::DragFloat4("c", &color.x, 0.1f, -1.0f, 1.0f);
	ImGui::End();

	ImGui::Begin("camera");

	ImGui::DragFloat3("p", &cPos.x, 1.0f, -1000.0f, 100.0f);
	ImGui::End();

	ImGui::Begin("shuriken");

	ImGui::DragFloat3("p", &shurikenRot.x, 0.1f, -1000.0f, 100.0f);
	ImGui::End();
#endif // _DEBUG
	cameraData->SetTranslate(cPos);
	shurikenRot.z += 0.2;
	if (shurikenRot.z>=3.0f) {
		shurikenRot.z = 0;
	}
	shurikenWorldTransform_->SetRotate(shurikenRot);
	shurikenWorldTransform2_->SetRotate(shurikenRot);

	shurikenPos.x += speed_;
	shurikenPos2.x += speed2_;
	if (stop_ == false) {
		if (shurikenPos.x >= 0.34f) {
			speed_ = 0;
		}
		if (shurikenPos2.x >= 0.37f) {
			speed2_ = 0;
		}
	}

	shurikenWorldTransform_->SetTranslate(shurikenPos);
	shurikenWorldTransform2_->SetTranslate(shurikenPos2);


	if (speed2_ == 0) {
		if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
			stop_ = true;

		}
	}
	if (stop_ == true) {
		speed_ += 0.02;
		speed2_ += 0.02;
		next_ += 1;
		color.w += 0.03;
	}
	if (next_ >= 60) {

	gameManager->ChangeState(new SelectScene);
	}
}

void StartSeen::Draw()
{
	titleData_->Draw({ 1,1,1,1 }, cameraData, titleWorldTransform_);
	shurikenData_->Draw({ 1,1,1,1 }, cameraData, shurikenWorldTransform_);
	shurikenData2_->Draw({ 1,1,1,1 }, cameraData, shurikenWorldTransform2_);
	
	spriteBlack->Draw({ 128,72,0 }, { 0,0,0 }, { 0,0,0 }, color);
}
