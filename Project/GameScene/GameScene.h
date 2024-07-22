#pragma once

#include"DKJEN/Management/TypeManagement.h"
#include"DKJEN/Skinning/Animation/Skinning.h"
#include"DKJEN/Skinning/Animation/Bone.h"
#include"DKJEN/JsonLoad/JsonLoad.h"
class GameScene
{
public:
	void Initialize();

	void Update();

	void Draw();

private:

	CameraData* cameraData;
	unique_ptr<JsonLoad>LevelData;
	unique_ptr<SkyBox> sky;
	WorldTransform* worldTransform;
};

