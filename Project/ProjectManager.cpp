#include "ProjectManager.h"


void ProjectManager::Gear()
{
	//はじめ
	WinApp::Initialize(Title);
	DxCommon::Initialize();
	ImguiManager::Initialize();
	Input::Initialize();
	PSOCopileManagement::Set();
	TexManager::Initiluze();


	game = new GameScene;

	game->Initialize();
	//更新
	while (WinApp::GetInstance()->WinMsg())
	{
		FrameManagement::BeginFrame();

		game->Update();
		game->Draw();
		
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
