
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
	WorldTransform* worldTransform = new WorldTransform;

	worldTransform->Create();
	Obj3D* obj3d = new Obj3D;
	ModelData modelData_ =LoadObjManagement::NewLoadObjFile("resource/hu", "sneakWalk.gltf");
	//Animation animatio = LoadObjManagement::LoadAnimationFile("resource/hu", "walk.gltf");
	Skeleton skeleton = LoadObjManagement::CreateSkeleton(modelData_.rootNode);
	obj3d->Initialize( modelData_);
	uint32_t tex = TexManager::LoadTexture("GameResource/uvChecker.png");
	Sprite* sprite = new Sprite;
	sprite->Initialize(tex);
	Vector3 cameraPos_ = { 0,0,0 };
	float k = 0;
	Matrix4x4 mtrix;
	float  animaionTime=0;
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
		animaionTime += 0.1f;
		worldTransform->UpdateMatrix(cameraData, mtrix);
	/*	mtrix=LoadObjManagement::AnimationUpdate(obj3d->GetModelData(),animatio);
		worldTransform->UpdateMatrix(cameraData, mtrix);
		LoadObjManagement::ApplyAnimation(skeleton, animatio, animaionTime);
		LoadObjManagement::Update(skeleton);*/
		worldTransform->SetTranslate({ 0,0,-100 });
		worldTransform->SetScale({1, 1, 1,});
		
		worldTransform->SetRotate({ 0,10.0f,0 });
		ImGui::Begin("pos");
		ImGui::SliderFloat3("camera", &cameraPos_.x, 10, -100);
		ImGui::End();
		cameraData->SetTranslate({ 0,0,-150 });
		cameraData->SetRotate(cameraPos_);
		//////
		//　ゲーム処理
		//////
		
	
		//////
		//　　描画処理
		//////
		
		//sprite->Draw({200.0f,100.0f,10.0f},{0,0,0},{0,0,0},{1,1,1,1});
		obj3d->Draw({1,1,1,1}, cameraData, worldTransform);

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
