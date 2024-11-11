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
	//初期化
	void Initialize()override;
	//更新処理
	void Update(GameManager* gameManager)override;
	//描画
	void Draw()override;
	//ImGui
	void ImGui()override;
	//プレイヤーの動き
	void Move();
private:
	//当たり判定
	void AllCollisions();
	//操作
	void Operation();

	
	
	///プレイヤーのアニメーション
	Skinning* skin;
	Bone* bone;
	LoadObjManagement* lod;
	unique_ptr<Animation3D> walk3d;
	Animation animatio;
	Skeleton skeleton;
	SkinCluster  skinCluster;
	float animaionTime;
	Vector3 playerPos_;
	Vector3 playerRot;
	int time;
	Vector4 color;

	//カメラ
	CameraData* cameraData;
	Vector3 cRot;
	Vector3 cPos;
	//CameraData* cameraAnime;
	
	//json
	unique_ptr<JsonLoad>LevelData;
	
	//スカイボックス
	unique_ptr<SkyBox> sky;

	//プレイヤーの当たり判定
	unique_ptr<Obj3D>player;
	WorldTransform* worldTransform;
	unique_ptr<Obj3D> objectData;
	WorldTransform* sphereWorldTransform_;





	


	//デバッグ用。後で消す。
	bool isInsideX = false;
	bool isInsideZ = false;

	float rotateTheta_ = 0.0f;
	float speed_ = 0;
	///カウントダウン
	Sprite* count3;
	Sprite* count2;
	Sprite* count1;
	float countdown;
	float startTime;
	///ダッシュ
	Sprite* ran3;
	Sprite* ran2;
	Sprite* ran1;
	float change;
	float ranTime;
};