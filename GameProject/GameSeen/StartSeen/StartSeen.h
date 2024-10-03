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
	void Initialize()override;
	void Update(GameManager* gameManager)override;
	void Draw()override;
private:
	/// <summary>
	/// カメラ
	/// </summary>
	CameraData* cameraData;
	Vector3 cPos;

	int time;
	Vector4 color;
	Sprite* sprite;
	Sprite* spriteBlack;
	//
	unique_ptr<Obj3D> titleData_;
	WorldTransform* titleWorldTransform_;

};