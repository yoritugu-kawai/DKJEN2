#include"DKJEN/Base/WinApp.h"
#include"DKJEN/Base/TexManager.h"

#include"DKJEN/Math/Math.h"

#include"DKJEN/Utilipy/rektyk.h"

#include"DKJEN/WorldTransform/WorldTransform.h"
#include"DKJEN/CameraProjection/CameraProjection.h"

#include"DKJEN/Management/TypeManagement.h"
#include "DKJEN/Management/FrameManagement.h"
#include"DKJEN/Management/PSOCopileManagement.h"
#include"DKJEN/Management/LoadObjManagement.h"
#include"GameProject/GameManager/GameManager.h"

#include"DKJEN/Skinning/Animation/Skinning.h"
#include"DKJEN/Skinning/Animation/Bone.h"

const wchar_t Title[] = { L"ド根性エンジン" };


//static D3DResourceLeaker leaker;
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WinApp::Initialize(Title);
	DxCommon::Initialize();
	ImguiManager::Initialize();
	Input::Initialize();

	PSOCopileManagement::Set();


	TexManager::Initiluze();
	CameraData* cameraData = new CameraData;
	cameraData->Create();
	//walkの取り込み
	Skinning* skin = new Skinning;
	Bone* bone = new Bone;
	LoadObjManagement* lod = new LoadObjManagement;
	WorldTransform* worldTransform = new WorldTransform;
	worldTransform->Create();
	Animation3D* walk3d = new Animation3D;
	ModelData modelData_ = LoadObjManagement::NewLoadObjFile("resource/hu", "walk.gltf");

	Animation animatio = lod->LoadAnimationFile("resource/hu", "walk.gltf");
	Skeleton skeleton = bone->CreateSkeleton(modelData_.rootNode);
	SkinCluster  skinCluster = skin->CreateSkinCluster(skeleton, modelData_);
	walk3d->Initialize(modelData_);



	CameraData* cameraBox = new CameraData;
	cameraBox->Create();
	Obj3D* box_ = new Obj3D;
	ModelData boxData_ = LoadObjManagement::NewLoadObjFile("resource", "axis.obj");

	box_->Initialize(boxData_);
	WorldTransform* boxWorldTransform_ = new WorldTransform;
	boxWorldTransform_->Create();

	//uint32_t tex = TexManager::LoadTexture("GameResource/uvChecker.png");
	/*Sprite* sprite = new Sprite;
	sprite->Initialize(tex);*/
	DescriptorManagement::GetInstance();
	Vector3 cameraPos_ = { 0,0,-10 };
	Vector3 cameraBox_ = { 0,0,-10 };
	//細かい値
	Vector3 cameraRotate_ = { 0,0,0 };
	float k = 0;
	Vector3 pos_ = { -2,-2,0 };
	Vector3 pos2_ = { 3,-2,0 };
	Vector3 rotate = { 0,-11,0 };
	float  animaionTime = 0;
	float  animaionTime2 = 0;
	float X = 0;
	float speed = 0.01f;
	Matrix4x4 mtrix = {};
	//座標

	////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////


	//　メインループ
	MSG msg{};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		FrameManagement::BeginFrame();

		//最初

		//////
		//　ゲーム処理
		//////
		cameraData->Update();
		cameraBox->Update();
		animaionTime += 1.0f / 60.0f;
		animaionTime2 += 3.0f / 60.0f;
		/*mtrix=LoadObjManagement::AnimationUpdate(obj3d->GetModelData(),animatio);
		worldTransform->AnimationUpdateMatrix(cameraData, mtrix);*/

		//Animation
		bone->ApplyAnimation(skeleton, animatio, animaionTime);
		//Skeleton

		bone->Update(skeleton);
		//SkinCluster

		skin->SkinUpdate(skinCluster, skeleton);

		///////Sneak
		//boneSneak->ApplyAnimation(skeletonSneak, animatioSneak, animaionTime);
		//////Skeleton

		//boneSneak->Update(skeletonSneak);
		//////SkinCluster

		//sneak->SkinUpdate(skinClusterSneak, skeletonSneak);

		worldTransform->SetScale({ 1, 1, 1, });
		if (Input::GetInstance()->PushKey(DIK_A)) {
			pos_.x -= 0.01f;
			rotate.y = 11;

		}
		if (Input::GetInstance()->PushKey(DIK_D)) {
			pos_.x += 0.01f;
			rotate.y = -11;
		}
		pos_.x += speed;
		worldTransform->SetTranslate(pos_);

		worldTransform->SetRotate(rotate);

		boxWorldTransform_->SetTranslate({ -2,0,0 });
		//更新

		worldTransform->UpdateMatrix(cameraData);
		boxWorldTransform_->UpdateMatrix(cameraBox);

		if (worldTransform->GetTranslate().x >= 3) {

			speed = 0;
			//animaionTime = 0;
		}
		//cameraPos_.x += 0.01f;
		cameraBox_.x += speed;
		cameraData->SetTranslate(cameraPos_);
		cameraBox->SetTranslate(cameraBox_);
		cameraData->SetRotate(cameraRotate_);
		X = worldTransform->GetTranslate().x;
		ImGui::Begin("pos");
		ImGui::SliderFloat3("camera", &X, 10, -500);
		ImGui::SliderFloat3("cameraRotate", &cameraRotate_.x, 3, -3);

		ImGui::End();
		//////
		//　ゲーム処理
		//////


		//////
		//　　描画処理
		//////

		//sprite->Draw({200.0f,100.0f,10.0f},{0,0,0},{0,0,0},{1,1,1,1});
		walk3d->Draw({ 1,1,1,1 }, cameraData, worldTransform, skinCluster);
		box_->Draw({ 1,1,1,1 }, cameraBox, boxWorldTransform_);


		//////
		//　　描画処理
		//////


		//終わり
		FrameManagement::EndFrame();
	}

	/*
	*************************
	*********   解放  *******
	*************************
	*/



	PSOCopileManagement::Release();

	ImguiManager::Release();
	DxCommon::Release();


	return 0;
}
