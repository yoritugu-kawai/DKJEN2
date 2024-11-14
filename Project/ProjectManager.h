#pragma once
#include"../../Base/WinApp.h"
#include"../../Base/TexManager.h"

#include"../../Math/Math.h"

#include"../../Utilipy/D3DResourceLeaker.h"

#include"../../WorldTransform/WorldTransform.h"
#include"../../CameraProjection/CameraProjection.h"

#include"../../Management/TypeManagement.h"
#pragma once
#include "../../Management/FrameManagement.h"
#include"../../Management/PSOCopileManagement.h"
#include"../../Management/LoadObjManagement.h"
const wchar_t Title[] = { L"ド根性エンジン" };
#include"../Project/GameScene/GameScene.h"
class ProjectManager
{
public:
	
	//更新処理
	void Gear();

private:
	GameScene* game;
};
