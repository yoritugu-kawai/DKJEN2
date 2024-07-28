#pragma once
#include"../StateSeen/IScene.h"

#include"../../Player/Player.h"
#include"../../Block/Block.h"

#include"../../GameManager/GameManager.h"



#include"DKJEN/Management/TypeManagement.h"
#include"DKJEN/Skinning/Animation/Skinning.h"
#include"DKJEN/Skinning/Animation/Bone.h"
#include"DKJEN/JsonLoad/JsonLoad.h"
class PlaySeen:public IScene {
public:
	void Initialize()override;
	void Update(GameManager* gameManager)override;
	void Draw()override;
	void LoadBlockPopData();
	void UpdateBlockPopCommands();
	void AllCollisions();
private:
	int speed_;
	int time;
	///
	Skinning* skin;
	Bone* bone;
	LoadObjManagement* lod;

	unique_ptr<Animation3D> walk3d;
	Animation animatio;
	Skeleton skeleton;
	SkinCluster  skinCluster;
	CameraData* cameraData;
	//CameraData* cameraAnime;
	unique_ptr<JsonLoad>LevelData;
	unique_ptr<SkyBox> sky;
	unique_ptr<Obj3D>player;
	WorldTransform* worldTransform;
	Vector3 cRot;
	Vector3 cPos;
	float animaionTime;
};