#pragma once
#include"../StateSeen/IScene.h"
#include"../SelectScene/SelectScene.h"
#include"../PlayScene/PlayScene.h"
#include"../../../DKJEN/Type/Sprite.h"
#include"../../GameManager/GameManager.h"
#include"../../../DKJEN/Camera/CameraData.h"
#include"../../../DKJEN/Type/Obj3D.h"
#include"../../../DKJEN/Type/Particle.h"


#include"../StateSeen/IScene.h"
#include"../clearScene/clearScene.h"
#include"../../Player/Player.h"
#include"../../Block/Block.h"
#include"../DKJEN/DKJEN/Management/TypeManagement.h"
#include"../DKJEN/DKJEN/Skinning/Animation/Skinning.h"
#include"../DKJEN/DKJEN/Skinning/Animation/Bone.h"
#include"../DKJEN/DKJEN/JsonLoad/JsonLoad.h"
class StartSeen:public IScene {
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
	
	void UpdateMatrix();
	//セッター
	void Set();
	
private:
	/// <summary>
	/// カメラ
	/// </summary>
	CameraData* cameraData;
	Vector3 cPos;

	int time;
	Vector4 color;
	Sprite* sprite;
	//暗転
	Sprite* spriteBlack;
	Vector3 posBlack;
	//モデル
	unique_ptr<Obj3D> titleData_;
	WorldTransform* titleWorldTransform_;
	///手裏剣
	unique_ptr<Obj3D> shurikenData_;
	WorldTransform* shurikenWorldTransform_;
	Vector3 shurikenPos;
	///手裏剣2
	unique_ptr<Obj3D> shurikenDataNext_;
	WorldTransform* shurikenWorldTransformNext_;
	Vector3 shurikenPosNext;
	//スペース
	unique_ptr<Obj3D> Space;
	WorldTransform* SpaceWorldTransform_;
	Vector3 SpacePos;
	bool come;
	///ド
	unique_ptr<Obj3D> doData_;
	WorldTransform* doWorldTransform_;
	Vector3 doPos;
	//ン
	unique_ptr<Obj3D> nData_;
	WorldTransform* nWorldTransform_;
	Vector3 nPos;
	//床
	unique_ptr<Obj3D> floorData_;
	WorldTransform* floorWorldTransform_;
	Vector3 floorPos;
	Vector3 floorSize;
	//木
	unique_ptr<Obj3D> treeData_;
	WorldTransform* treeWorldTransform_;
	Vector3 treePos;
	Vector3 treeSize;
	//木
	unique_ptr<Obj3D> treeData2_;
	WorldTransform* treeWorldTransform2_;
	Vector3 treePos2;
	Vector3 treeSize2;
	//木
	unique_ptr<Obj3D> treeData3_;
	WorldTransform* treeWorldTransform3_;
	Vector3 treePos3;
	Vector3 treeSize3;
	//木
	unique_ptr<Obj3D> treeData4_;
	WorldTransform* treeWorldTransform4_;
	Vector3 treePos4;
	Vector3 treeSize4;
	
	//変数
	Vector3 shurikenRot;
	float speed_;
	float nextSpeed_;
	bool stop_;
	int next_;
	///
	Skinning* skin;
	Bone* bone;
	LoadObjManagement* lod;
	unique_ptr<Animation3D> walk3d;
	Animation animatio;
	Skeleton skeleton;
	SkinCluster  skinCluster;
	float animaionTime;
	WorldTransform* worldTransform;
	Vector3 playerPos_;
};
