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

	//ここまで
	
	
	
	//更新
	while (WinApp::GetInstance()->WinMsg())
	{
		FrameManagement::BeginFrame();

		//更新
		
		///描画
		
		
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
