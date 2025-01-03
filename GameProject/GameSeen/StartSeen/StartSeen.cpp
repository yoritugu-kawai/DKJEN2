#include "StartSeen.h"

void StartSeen::Initialize()
{
	/////カメラ処理	
	cameraData = new CameraData;
	cameraData->Create();
	cPos = { 0.04f,0.02f,-1 };
	time = 12;

	//暗転
	uint32_t texBlack = TexManager::LoadTexture("GameResource/black.png");
	spriteBlack = new Sprite;
	spriteBlack->Initialize(texBlack);
	
	//タイトルのモデル
		/*
	宣言
	画像読み込み
	初期化
	座標
	以下
	値渡し
	*/
	titleData_ = std::make_unique<Obj3D>();
	titleWorldTransform_ = new WorldTransform();
	titleWorldTransform_->Create();
	titleWorldTransform_->SetScale({ 0.1f,0.1f,0.1f });
	ModelData titleModel_ = LoadObjManagement::NewLoadObjFile("GameResource/Title/Obj", "Title.obj");
	titleData_->Initialize(titleModel_);


	///手裏剣
		/*
	宣言
	画像読み込み
	初期化
	座標
	以下
	値渡し
	*/
	shurikenData_ = std::make_unique<Obj3D>();
	shurikenWorldTransform_ = new WorldTransform();
	shurikenWorldTransform_->Create();
	shurikenWorldTransform_->SetScale({ 0.1f,0.1f,0.1f });
	ModelData shurikenModel_ = LoadObjManagement::NewLoadObjFile("GameResource/Title/Obj", "Shuriken.obj");
	shurikenData_->Initialize(shurikenModel_);
	shurikenPos = { -1.04f,0.09f,0.0f };

	///手裏剣2
		/*
	宣言
	画像読み込み
	初期化
	座標
	以下
	値渡し
	*/
	shurikenDataNext_ = std::make_unique<Obj3D>();
	shurikenWorldTransformNext_ = new WorldTransform();
	shurikenWorldTransformNext_->Create();
	shurikenWorldTransformNext_->SetScale({ 0.1f,0.1f,0.1f });
	ModelData shurikenModel2_ = LoadObjManagement::NewLoadObjFile("GameResource/Title/Obj", "Shuriken.obj");
	shurikenDataNext_->Initialize(shurikenModel2_);
	shurikenPosNext = { -1.07f,0.1f,0.0f };

	///スペース
		/*
	宣言
	画像読み込み
	初期化
	座標
	以下
	値渡し
	*/
	Space = std::make_unique<Obj3D>();
	SpaceWorldTransform_ = new WorldTransform();
	SpaceWorldTransform_->Create();
	SpaceWorldTransform_->SetScale({ 0.1f,0.1f,0.1f });
	ModelData SpaceModel_ = LoadObjManagement::NewLoadObjFile("GameResource/Title/Obj", "Space.obj");
	Space->Initialize(SpaceModel_);
	SpacePos = { 0.0f,-0.6f,3.7f };
	come = false;


    ///ドのモデル
	/*
	宣言
	画像読み込み
	初期化
	座標
	以下
	値渡し
	*/
	doData_ = std::make_unique<Obj3D>();
	ModelData doModel_ = LoadObjManagement::NewLoadObjFile("GameResource/Title/Obj", "do.obj");
	doData_->Initialize(doModel_);
	doWorldTransform_ = new WorldTransform();
	doWorldTransform_->Create();
	doWorldTransform_->SetScale({ 0.1f,0.1f,0.1f });
	doPos = { 0.2f,-0.4f,2.3f };

	///ン
		/*
	宣言
	画像読み込み
	初期化
	座標
	以下
	値渡し
	*/
	nData_ = std::make_unique<Obj3D>();
	ModelData nModel_ = LoadObjManagement::NewLoadObjFile("GameResource/Title/Obj", "nn.obj");
	nData_->Initialize(nModel_);
	nWorldTransform_ = new WorldTransform();
	nWorldTransform_->Create();
	nWorldTransform_->SetScale({ 0.1f,0.1f,0.1f });
    nPos = { -0.1f,-0.4f,2.3f };

	//床
		/*
	宣言
	画像読み込み
	初期化
	座標
	以下
	値渡し
	*/
	floorData_ = std::make_unique<Obj3D>();
	ModelData floorModel_ = LoadObjManagement::NewLoadObjFile("GameResource/Title/Obj", "ground.obj");
	floorData_->Initialize(floorModel_);
	floorWorldTransform_ = new WorldTransform();
	floorWorldTransform_->Create();
	floorSize = { 0.9f,0.1f,0.9f };
	floorPos = {0.0f,-1.1f,14.1f};
	floorWorldTransform_->SetScale(floorSize);

	//木
		/*
	宣言
	画像読み込み
	初期化
	座標
	以下
	値渡し
	*/
	treeData_ = std::make_unique<Obj3D>();
	ModelData treeModel_ = LoadObjManagement::NewLoadObjFile("GameResource/Title/Obj", "wood.obj");
	treeData_->Initialize(treeModel_);
	treeWorldTransform_ = new WorldTransform();
	treeWorldTransform_->Create();
	treeSize = { 0.1f,0.1f,0.1f };
	treePos = { -5.0f,-1.5f,14.0f };


	//
	speed_ = 0.02f;
	nextSpeed_ = 0.02f;
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
	shurikenWorldTransformNext_->SetRotate(shurikenRot);
	///スタートの動き
	shurikenPos.x += speed_;
	shurikenPosNext.x += nextSpeed_;
	if (stop_ == false) {
		if (shurikenPos.x >= 0.34f) {
			speed_ = 0;
		}
		if (shurikenPosNext.x >= 0.37f) {
			nextSpeed_ = 0;
			
			come = true;
		}
	}
	
	//シーン移行
	if (nextSpeed_ == 0) {
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
		nextSpeed_ += 0.02f;
		next_ += 1;
		color.w += 0.03f;
	}
	if (next_ >= 60) {

	gameManager->ChangeState(new PlayScene);
	}
}

void StartSeen::Draw()
{
	//木のモデル
	treeData_->Draw({ 1,1,1,1 }, cameraData, treeWorldTransform_);
	//地面のモデル
	floorData_->Draw({ 1,1,1,1 }, cameraData, floorWorldTransform_);
	//タイトルのモデル
	titleData_->Draw({ 1,1,1,1 }, cameraData, titleWorldTransform_);
	//手裏剣１のモデル
	shurikenData_->Draw({ 1,1,1,1 }, cameraData, shurikenWorldTransform_);
	//手裏剣2のモデル
	shurikenDataNext_->Draw({ 1,1,1,1 }, cameraData, shurikenWorldTransformNext_);
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
	//カメラのアップデート
	cameraData->Update();
	//タイトル座標のアップデート
	titleWorldTransform_->UpdateMatrix(cameraData);
	//手裏剣座標のアップデート
	shurikenWorldTransform_->UpdateMatrix(cameraData);
	//手裏剣座標のアップデート
	shurikenWorldTransformNext_->UpdateMatrix(cameraData);
	//ボタン座標のアップデート
	SpaceWorldTransform_->UpdateMatrix(cameraData);
	//ど座標のアップデート
	doWorldTransform_->UpdateMatrix(cameraData);
	//ン座標のアップデート
	nWorldTransform_->UpdateMatrix(cameraData);
	//地面座標のアップデート
	floorWorldTransform_->UpdateMatrix(cameraData);
	//木座標のアップデート
	treeWorldTransform_->UpdateMatrix(cameraData);
	
	cameraData->SetTranslate(cPos);

}

void StartSeen::Set()
{
	///手裏剣座標の読み込み
	shurikenWorldTransform_->SetTranslate(shurikenPos);
	///手裏剣座標の読み込み
	shurikenWorldTransformNext_->SetTranslate(shurikenPosNext);
	///スペース座標の読み込み
	SpaceWorldTransform_->SetTranslate(SpacePos);
	///ど座標の読み込み
	doWorldTransform_->SetTranslate(doPos);
	///ん座標の読み込み
	nWorldTransform_->SetTranslate(nPos);
	///地面座標の読み込み
	floorWorldTransform_->SetTranslate(floorPos);
	///木座標の読み込み
	treeWorldTransform_->SetTranslate(treePos);
	//地面大きさの読み込み
	floorWorldTransform_->SetScale(floorSize);
	//カメラ座標の読み込み
	cameraData->SetTranslate(cPos);
}
