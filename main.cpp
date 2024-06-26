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
	WorldTransform* worldTransform = new WorldTransform;
	worldTransform->Create();
	Obj3D* walk3d = new Obj3D;
	ModelData modelData_ = LoadObjManagement::NewLoadObjFile("resource/hu", "walk.gltf");
	Animation animatio = LoadObjManagement::LoadAnimationFile("resource/hu", "walk.gltf");
	Skeleton skeleton = bone->CreateSkeleton(modelData_.rootNode);
	SkinCluster  skinCluster = skin->CreateSkinCluster(skeleton, modelData_);
	walk3d->Initialize(modelData_);
	uint32_t tex = TexManager::LoadTexture("GameResource/uvChecker.png");
	//AnimatedCube
	Skinning* skinSimple = new Skinning;
	Bone* boneSimple = new Bone;
	WorldTransform* worldTransformSimple = new WorldTransform;
	worldTransformSimple->Create();
	Obj3D* animatedSimple3d = new Obj3D;
	ModelData animatedSimpleData_ = LoadObjManagement::NewLoadObjFile("resource", "simpleSkin.gltf");
	Animation animatioSimple = LoadObjManagement::LoadAnimationFile("resource", "simpleSkin.gltf");
	Skeleton skeletonSimple = boneSimple->CreateSkeleton(animatedSimpleData_.rootNode);
	SkinCluster  skinClusterSimple = skinSimple->CreateSkinCluster(skeletonSimple, animatedSimpleData_);
	animatedSimple3d->Initialize(animatedSimpleData_);
	//
	Obj3D* box_ = new Obj3D;
	ModelData boxData_ = LoadObjManagement::NewLoadObjFile("resource", "AnimatedCube.gltf");
	box_->Initialize(boxData_);
	WorldTransform* boxWorldTransform_ = new WorldTransform;
	boxWorldTransform_->Create();

	//
	Sprite* sprite = new Sprite;
	Vector3 cameraPos_ = { 0,0,-10 };

	Vector3 cameraRotate_ = { 0,0,0 };
	sprite->Initialize(tex);

	float k = 0;
	Vector3 pos_ = { 0,-2,0 };
	Vector3 pos2_ = { 3,-2,0 };
	Vector3 rotate = { 0,11,0 };
	float  animaionTime = 0;
	Matrix4x4 mtrix = {};
	//座標


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
		animaionTime += 1.0f / 60.0f;

		/*mtrix=LoadObjManagement::AnimationUpdate(obj3d->GetModelData(),animatio);
		worldTransform->AnimationUpdateMatrix(cameraData, mtrix);*/

		//Animation
		bone->ApplyAnimation(skeleton, animatio, animaionTime);
		//Skeleton

		bone->Update(skeleton);
		//SkinCluster

		skin->SkinUpdate(skinCluster, skeleton);

		///
		boneSimple->ApplyAnimation(skeletonSimple, animatioSimple, animaionTime);
		//Skeleton

		boneSimple->Update(skeletonSimple);
		//SkinCluster

		skinSimple->SkinUpdate(skinClusterSimple, skeletonSimple);


		worldTransform->SetScale({ 1, 1, 1, });
		if (Input::GetInstance()->PushKey(DIK_A)) {
			pos_.x -= 0.01f;
			rotate.y = 11;

		}
		if (Input::GetInstance()->PushKey(DIK_D)) {
			pos_.x += 0.01f;
			rotate.y = -11;
		}
		worldTransform->SetTranslate(pos_);
		worldTransformSimple->SetTranslate(pos2_ );
		worldTransform->SetRotate(rotate);
		worldTransformSimple->SetRotate({0,2.5,0});

		boxWorldTransform_->SetTranslate({-2,0,0});
		//更新
		//worldTransform->AnimationUpdateMatrix(cameraData, mtrix);
		worldTransform->UpdateMatrix(cameraData);
		worldTransformSimple->UpdateMatrix(cameraData);
		boxWorldTransform_->UpdateMatrix(cameraData);
		/*skeleton.joints[1].skeletonSpaceMatrix;
		worldTransformCubemodel->UpdateMatrix*/
		ImGui::Begin("pos");
		ImGui::SliderFloat3("camera", &cameraPos_.x, 10, -500);
		ImGui::SliderFloat3("cameraRotate", &cameraRotate_.x, 3, -3);

		ImGui::End();
		cameraData->SetTranslate(cameraPos_);
		cameraData->SetRotate(cameraRotate_);

		//////
		//　ゲーム処理
		//////


		//////
		//　　描画処理
		//////

		//sprite->Draw({200.0f,100.0f,10.0f},{0,0,0},{0,0,0},{1,1,1,1});
		box_->Draw({ 1,1,1,1 }, cameraData, boxWorldTransform_);
		walk3d->AnimationDraw({ 1,1,1,1 }, cameraData, worldTransform, skinCluster);
		animatedSimple3d->AnimationDraw({ 1,1,1,1 }, cameraData, worldTransformSimple, skinClusterSimple);
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
