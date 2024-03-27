#pragma once
#include"../StateSeen/IScene.h"
#include"../PlaySeen/PlaySeen.h"
#include"../../../DKJEN/Type/Sprite.h"
#include"../../GameManager/GameManager.h"
#include"../../../DKJEN/Camera/CameraData.h"
#include"../../../DKJEN/Type/Obj3D.h"
#include"../../../DKJEN/Type/Particle.h"
class StartSeen:public IScene {
public:
	void Initialize()override;
	void Update(GameManager* gameManager)override;
	void Draw()override;
private:

	//カメラ
	CameraData* cameraData_;
	Vector3 cameraPos = { 0.0f,0.0f,-10.0f };
	Vector3 cameraRot = {0,0,0};
	//3Dモデル
	Obj3D* ball_;
	Obj3D* axis_;
	WorldTransform* worldTransform;
	Vector3 ballPos;
	//パーティクル
	Particle* particle;
	Particle* particle2;
	//
	int time;
	Coordinate particlePos_;
};