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
}

void StartSeen::Update(GameManager* gameManager)
{
	cameraData->Update();
	titleWorldTransform_->UpdateMatrix(cameraData);
	
	color.w -= 0.01f;
#ifdef _DEBUG
	ImGui::Begin("Color");
	ImGui::DragFloat4("c", &color.x, 0.1f, -1.0f, 1.0f);

	ImGui::Begin("camera");
	
	ImGui::DragFloat3("p", &cPos.x, 1.0f, -1000.0f, 100.0f);
	ImGui::End();
	ImGui::End();
#endif // _DEBUG
	cameraData->SetTranslate(cPos);
	if (color.w < 0) {
		if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
			gameManager->ChangeState(new SelectScene);

		}
	}

}

void StartSeen::Draw()
{
	titleData_->Draw({ 1,1,1,1 }, cameraData, titleWorldTransform_);
	/*sprite->Draw({128,72,0},{0,0,0},{0,0,0},{1.0f,1.0f,1.0f,1.0f});*/
	spriteBlack->Draw({ 128,72,0 }, { 0,0,0 }, { 0,0,0 }, color);
}
