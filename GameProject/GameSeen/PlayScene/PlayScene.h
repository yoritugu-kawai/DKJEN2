#pragma once
#include"../StateSeen/IScene.h"
#include"../clearScene/clearScene.h"
#include"../../Player/Player.h"
#include"../../Block/Block.h"

#include"../../GameManager/GameManager.h"


///#include"../DKJEN/DKJEN/Collision/ABB/ABB.h"
#include"../DKJEN/DKJEN/Management/TypeManagement.h"
#include"../DKJEN/DKJEN/Skinning/Animation/Skinning.h"
#include"../DKJEN/DKJEN/Skinning/Animation/Bone.h"
#include"../DKJEN/DKJEN/JsonLoad/JsonLoad.h"
class PlayScene :public IScene {
public:
	//
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;
	
	/// <summary>
	/// //更新処理
	/// </summary>
	/// <param name="gameManager"></param>
	void Update(GameManager* gameManager)override;
	
	/// <summary>
	/// //描画
	/// </summary>

	void Draw()override;
	
	/// <summary>
	/// //ImGui
	/// </summary>

	void ImGui()override;
	//プレイヤーの動き
	void Move();
private:
	//当たり判定
	void AllCollisions();
	//操作
	void Operation();
	//特殊操作
	void Gimmick();

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
	unique_ptr<WorldTransform> sphereWorldTransform_;








	//デバッグ用。後で消す。
	bool isInsideX = false;
	bool isInsideZ = false;

	float rotateTheta_ = 0.0f;
	
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
	float backDamag;
	Vector4 damagCeolor;
	float ROTATE_INTERVAL;
	//特殊ギミック用
	float standardTime;
	float normalTime;
	float actionTime;
	float standardSpeed_;
	float normalSpeed_;
	float actionSpeed_;
};