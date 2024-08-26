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

	
	int time;
	Vector4 color;
	Sprite* sprite;
	Sprite* spriteBlack;
};