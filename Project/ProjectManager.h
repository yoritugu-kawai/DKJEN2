#pragma once
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
#include"DKJEN/JsonLoad/JsonLoad.h"
const wchar_t Title[] = { L"ド根性エンジン" };

class ProjectManager
{
public:
	void Initialize();
	void Gear();

private:
	CameraData* cameraData;
	unique_ptr<JsonLoad>LevelData;
};
