#include "ProjectManager.h"

void ProjectManager::Initialize()
{
	
}

void ProjectManager::Gear()
{
	WinApp::Initialize(Title);
	DxCommon::Initialize();
	ImguiManager::Initialize();
	Input::Initialize();

	PSOCopileManagement::Set();


	TexManager::Initiluze();
	cameraData = new CameraData;
	cameraData->Create();

	LevelData = make_unique<JsonLoad>();
	LevelData->Load("resource/json/", "test.json");

	cameraData->SetTranslate(Vector3(0.0f, 2.0f, -32.0f));
	cameraData->Update();
	while (WinApp::GetInstance()->WinMsg())
	{
		FrameManagement::BeginFrame();


		LevelData->Update(cameraData);
		cameraData->Update();

		//////
		//　　描画処理
		//////
		LevelData->Draw(cameraData);

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
}
