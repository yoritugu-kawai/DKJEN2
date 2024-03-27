
#include"DKJEN/Base/WinApp.h"
#include"DKJEN/Base/ImageLoading.h"

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



	GameManager* gameManager_ = new GameManager;
	gameManager_->Initialize();
	/*IScene* iseen = new StartSeen;
	iseen->Initialize();*/

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
	

		/*up = 1.5f * up;
		hit_ = hit_ * up;*/

		//iseen->Update();
		
		//////
		//　ゲーム処理
		//////
		
		gameManager_->Update();
		//////
		//　　描画処理
		//////
		//iseen->Draw();
		//////
		//　　描画処理
		//////
		gameManager_->Draw();
		
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
