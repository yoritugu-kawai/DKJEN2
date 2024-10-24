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
	;*/
	//暗転
	uint32_t texBlack = TexManager::LoadTexture("GameResource/black.png");
	spriteBlack = new Sprite;
	spriteBlack->Initialize(texBlack);
	//posBlack = { -2280,0,0 };
	//color = { 1.0f,1.0f,1.0f,1.0f };

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

	///スペース
	
	Space = std::make_unique<Obj3D>();
	SpaceWorldTransform_ = new WorldTransform();
	SpaceWorldTransform_->Create();
	SpaceWorldTransform_->SetScale({ 0.1f,0.1f,0.1f });
	ModelData SpaceModel_ = LoadObjManagement::NewLoadObjFile("GameResource/Title/Obj", "Space.obj");
	Space->Initialize(SpaceModel_);
	SpacePos = { 0.0f,-0.6f,3.7f };
	come = false;
    ///ド
	doData_ = std::make_unique<Obj3D>();
	
	ModelData doModel_ = LoadObjManagement::NewLoadObjFile("GameResource/Title/Obj", "do.obj");
	doData_->Initialize(doModel_);
	doWorldTransform_ = new WorldTransform();
	doWorldTransform_->Create();
	doWorldTransform_->SetScale({ 0.1f,0.1f,0.1f });
	doPos = { 0.2f,-0.4f,2.3f };
	///ン
	nData_ = std::make_unique<Obj3D>();
	ModelData nModel_ = LoadObjManagement::NewLoadObjFile("GameResource/Title/Obj", "nn.obj");
	nData_->Initialize(nModel_);
	nWorldTransform_ = new WorldTransform();
	nWorldTransform_->Create();
	nWorldTransform_->SetScale({ 0.1f,0.1f,0.1f });
    nPos = { -0.1f,-0.4f,2.3f };
	//床
	floorData_ = std::make_unique<Obj3D>();
	ModelData floorModel_ = LoadObjManagement::NewLoadObjFile("GameResource/Title/Obj", "ground.obj");
	floorData_->Initialize(floorModel_);
	floorWorldTransform_ = new WorldTransform();
	floorWorldTransform_->Create();
	floorSize = { 0.9f,0.1f,0.9f };
	floorPos = {0.0f,-1.1f,14.1f};
	floorWorldTransform_->SetScale(floorSize);
	//木
	treeData_ = std::make_unique<Obj3D>();
	ModelData treeModel_ = LoadObjManagement::NewLoadObjFile("GameResource/Title/Obj", "wood.obj");
	treeData_->Initialize(treeModel_);
	treeWorldTransform_ = new WorldTransform();
	treeWorldTransform_->Create();
	treeSize = { 0.1f,0.1f,0.1f };
	treePos = { -5.0f,-1.5f,14.0f };
	//
	speed_ = 0.02f;
	speed2_ = 0.02f;
	stop_ = false;
}

void StartSeen::Update(GameManager* gameManager)
{
	UpdateMatrix();
	Set();
	

	//手裏剣の回転
	shurikenRot.z += 0.2f;
	if (shurikenRot.z>=3.0f) {
		shurikenRot.z = 0;
	}
	shurikenWorldTransform_->SetRotate(shurikenRot);
	shurikenWorldTransform2_->SetRotate(shurikenRot);
	///スタートの動き
	shurikenPos.x += speed_;
	shurikenPos2.x += speed2_;
	if (stop_ == false) {
		if (shurikenPos.x >= 0.34f) {
			speed_ = 0;
		}
		if (shurikenPos2.x >= 0.37f) {
			speed2_ = 0;
			
			come = true;
		}
	}
	
	//シーン移行
	if (speed2_ == 0) {
		if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
			stop_ = true;

		}
	}
	if (stop_ == true) {
		//暗転座標
		//posBlack.x +=30;
		doPos.z -= 0.1f;
		nPos.z -= 0.1f;
		speed_ += 0.02f;
		speed2_ += 0.02f;
		next_ += 1;
		color.w += 0.03f;
	}
	if (next_ >= 60) {

	gameManager->ChangeState(new PlayScene);
	}
}

void StartSeen::Draw()
{
	//モデル
	treeData_->Draw({ 1,1,1,1 }, cameraData, treeWorldTransform_);
	floorData_->Draw({ 1,1,1,1 }, cameraData, floorWorldTransform_);
	titleData_->Draw({ 1,1,1,1 }, cameraData, titleWorldTransform_);
	shurikenData_->Draw({ 1,1,1,1 }, cameraData, shurikenWorldTransform_);
	shurikenData2_->Draw({ 1,1,1,1 }, cameraData, shurikenWorldTransform2_);
	//ドンとスペース
	if (come==true) {
	doData_->Draw({ 1,1,1,1 }, cameraData, doWorldTransform_);
	nData_->Draw({ 1,1,1,1 }, cameraData, nWorldTransform_);
	Space->Draw({ 1,1,1,1 }, cameraData, SpaceWorldTransform_);

	}
	//暗転
	spriteBlack->Draw({ 256,72,0 }, { 0,0,0 }, posBlack, color);
}

void StartSeen::ImGui()
{
#ifdef _DEBUG
	ImGui::Begin("Color");
	ImGui::DragFloat4("c", &color.x, 0.1f, -1.0f, 1.0f);
	ImGui::End();

	ImGui::Begin("camera");

	ImGui::DragFloat3("p", &cPos.x, 1.0f, -1000.0f, 100.0f);
	ImGui::End();

	ImGui::Begin("shuriken");
	ImGui::DragFloat3("s", &treeSize.x, 0.1f, -1000.0f, 100.0f);
	ImGui::DragFloat3("p", &treePos.x, 0.1f, -1000.0f, 100.0f);
	ImGui::End();
#endif // _DEBUG
}

void StartSeen::UpdateMatrix()
{
	cameraData->Update();
	titleWorldTransform_->UpdateMatrix(cameraData);
	shurikenWorldTransform_->UpdateMatrix(cameraData);
	shurikenWorldTransform2_->UpdateMatrix(cameraData);
	SpaceWorldTransform_->UpdateMatrix(cameraData);
	doWorldTransform_->UpdateMatrix(cameraData);
	nWorldTransform_->UpdateMatrix(cameraData);
	floorWorldTransform_->UpdateMatrix(cameraData);
	treeWorldTransform_->UpdateMatrix(cameraData);
	
	cameraData->SetTranslate(cPos);

}

void StartSeen::Set()
{
	///座標
	shurikenWorldTransform_->SetTranslate(shurikenPos);
	shurikenWorldTransform2_->SetTranslate(shurikenPos2);
	SpaceWorldTransform_->SetTranslate(SpacePos);
	doWorldTransform_->SetTranslate(doPos);
	nWorldTransform_->SetTranslate(nPos);
	floorWorldTransform_->SetTranslate(floorPos);
	treeWorldTransform_->SetTranslate(treePos);
	//
	floorWorldTransform_->SetScale(floorSize);
}
