
#include"DKJEN/Base/WinApp.h"
#include"DKJEN/Base/TexManager.h"

#include"DKJEN/Math/Math.h"

#include"DKJEN/Utilipy/rektyk.h"

#include"DKJEN/WorldTransform/WorldTransform.h"
#include"DKJEN/CameraProjection/CameraProjection.h"

#include"DKJEN/Management/TypeManagement.h"
#include "DKJEN/Management/FrameManagement.h"
#include"DKJEN/Management/PSOCopileManagement.h"


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
	obj3d->Initialize("resource","plane.gltf");
	uint32_t tex = TexManager::LoadTexture("GameResource/uvChecker.png");
	Sprite* sprite = new Sprite;
	sprite->Initialize(tex);
	Vector3 cameraPos_ = { 0,0,0 };
	

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
		worldTransform->UpdateMatrix(cameraData);

		worldTransform->SetTranslate({ 0,0,0 });
		worldTransform->SetScale({1, 1, 1,});
		ImGui::Begin("pos");
		ImGui::SliderFloat3("camera", &cameraPos_.x, 10, -100);
		ImGui::End();
		cameraData->SetTranslate({ 0,0,-20 });
		cameraData->SetRotate(cameraPos_);
		//////
		//　ゲーム処理
		//////
		
	
		//////
		//　　描画処理
		//////
		
		obj3d->Draw({1,1,1,1}, cameraData, worldTransform);
		sprite->Draw({200.0f,100.0f,10.0f},{0,0,0},{0,0,0},{1,1,1,1});

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
