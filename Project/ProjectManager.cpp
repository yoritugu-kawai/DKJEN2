#include "ProjectManager.h"


void ProjectManager::Gear()
{
	//宣言
	WinApp::Initialize(Title);
	DxCommon::Initialize();
	ImguiManager::Initialize();
	Input::Initialize();
	PSOCopileManagement::Set();
	TexManager::Initiluze();
	game = new GameScene;
	game->Initialize();
	//ここまで
	
	
	
	//更新
	while (WinApp::GetInstance()->WinMsg())
	{
		FrameManagement::BeginFrame();

		//更新
		game->Update();
		///描画
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
