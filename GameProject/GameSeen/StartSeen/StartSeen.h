#pragma once
#include"../StateSeen/IScene.h"
#include"../SelectScene/SelectScene.h"
#include"../PlayScene/PlayScene.h"
#include"../../../DKJEN/Type/Sprite.h"
#include"../../GameManager/GameManager.h"
#include"../../../DKJEN/Camera/CameraData.h"
#include"../../../DKJEN/Type/Obj3D.h"
#include"../../../DKJEN/Type/Particle.h"
class StartSeen:public IScene {
public:
	//初期化
	void Initialize()override;
	//更新処理
	void Update(GameManager* gameManager)override;
	//描画
	void Draw()override;
	//ImGui
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
	unique_ptr<Obj3D> shurikenData2_;
	WorldTransform* shurikenWorldTransform2_;
	Vector3 shurikenPos2;
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
	
	
	//変数
	Vector3 shurikenRot;
	float speed_;
	float speed2_;
	bool stop_;
	int next_;

};