#pragma once
#include"../StateSeen/IScene.h"
#include"../PlayScene/PlayScene.h"
#include"../../../DKJEN/Type/Sprite.h"
#include"../../GameManager/GameManager.h"
#include"../../../DKJEN/Camera/CameraData.h"
#include"../../../DKJEN/Type/Obj3D.h"
#include"../../../DKJEN/Type/Particle.h"


#include"../../Management/TypeManagement.h"
#include"../../Skinning/Animation/Skinning.h"
#include"../../Skinning/Animation/Bone.h"
#include"../../JsonLoad/JsonLoad.h"
class clearScene :public IScene {
public:
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
private:

	/// <summary>
	/// ジャンプ
	/// </summary>
	Skinning* skin;
	Bone* bone;
	LoadObjManagement* lod;
	Animation animatio;
	Skeleton skeleton;
	SkinCluster  skinCluster;
	/// <summary>
	/// /あほどうり
	/// </summary>
	Skinning* skinSilly;
	Bone* boneSilly;
	LoadObjManagement* lodSilly;
	Animation animatioSilly;
	Skeleton skeletonSilly;
	SkinCluster  skinClusterSilly;
	/// <summary>
	/// /HipHop
	/// </summary>
	Skinning* skinHipHop;
	Bone* boneHipHop;
	LoadObjManagement* lodHipHop;
	Animation animatioHipHop;
	Skeleton skeletonHipHop;
	SkinCluster  skinClusterHipHop;
	/// <summary>
	/// /Rumba
	/// </summary>
	Skinning* skinRumba;
	Bone* boneRumba;
	LoadObjManagement* lodRumba;
	Animation animatioRumba;
	Skeleton  skeletonRumba;
	SkinCluster skinClusterRumba;
	/// <summary>
	/// /プレイヤー
	/// </summary>
	unique_ptr<Animation3D> walk3d;
	float speed;
	float animaionTime;
	Vector3 playerPos_;
	Vector3 playerRot;
	Vector4 color;
	WorldTransform* worldTransform;
	/// <summary>
	/// /プレイヤーの踊り
	/// </summary>
	unique_ptr<Animation3D> walk3d2;
	Vector3 playerPos2_;
	WorldTransform* worldTransform2;
	//
	/////プレイヤーの踊り
	unique_ptr<Animation3D> walk3d3;
	Vector3 playerPos3_;
	WorldTransform* worldTransform3;
	//カメラ
	CameraData* cameraData;
	Vector3 cRot;
	Vector3 cPos;

	//
	unique_ptr<Obj3D> treeData_;
	WorldTransform* treeWorldTransform_;
	Vector3 treePos;
	Vector3 treeSize;
	///
	Sprite* sprite;
	
};