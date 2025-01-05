#pragma once
#include"../DKJEN/DKJEN/Base/WinApp.h"
#include"../DKJEN/DKJEN/Base/TexManager.h"
#include"../DKJEN/DKJEN/Math/Math.h"
#include"../DKJEN/DKJEN/Utilipy/D3DResourceLeaker.h"
#include"../DKJEN/DKJEN/WorldTransform/WorldTransform.h"
#include"../DKJEN/DKJEN/CameraProjection/CameraProjection.h"
#include"../DKJEN/DKJEN/Management/TypeManagement.h"
#pragma once
#include"../DKJEN/DKJEN/Management/FrameManagement.h"
#include"../DKJEN/DKJEN/Management/PSOCopileManagement.h"
#include"../DKJEN/DKJEN/Management/LoadObjManagement.h"
const wchar_t Title[] = { L"ド根性エンジン" };
#include"../Project/GameScene/GameScene.h"
class ProjectManager
{
public:
	
	//更新処理
	void Gear();

private:
	//宣言
	GameScene* game;
};
