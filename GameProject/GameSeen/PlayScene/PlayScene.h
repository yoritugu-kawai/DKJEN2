#pragma once
#include"../StateSeen/IScene.h"
#include"../clearScene/clearScene.h"
#include"../../Player/Player.h"
#include"../../Block/Block.h"

#include"../../GameManager/GameManager.h"


///#include"../DKJEN/DKJEN/Collision/ABB/ABB.h"
#include"../../Management/TypeManagement.h"
#include"../../Skinning/Animation/Skinning.h"
#include"../../Skinning/Animation/Bone.h"
#include"../../JsonLoad/JsonLoad.h"
class PlayScene :public IScene {
public:
	void Initialize()override;
	void Update(GameManager* gameManager)override;
	void Draw()override;
	void ImGui()override;
	void Move();
private:
	void AllCollisions();
	void Operation();

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
	Vector3 playerPos_;
	Vector3 playerRot;




	unique_ptr<Obj3D> objectData;
	WorldTransform* sphereWorldTransform_;


	//デバッグ用。後で消す。
	bool isInsideX = false;
	bool isInsideZ = false;

	float rotateTheta_ = 0.0f;
	float speed_ = 0;
	///
	Sprite* count3;
	Sprite* count2;
	Sprite* count1;
	float countdown;
};