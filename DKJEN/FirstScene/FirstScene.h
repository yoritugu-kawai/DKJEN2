#pragma once
#include"../../GameProject/GameSeen/StateSeen/IScene.h"
#include"../../GameProject/GameSeen/StartSeen/StartSeen.h"

#include"../../../DKJEN/Type/Sprite.h"
#include"../../GameProject/GameManager/GameManager.h"
#include"../../../DKJEN/Camera/CameraData.h"
#include"../../../DKJEN/Type/Obj3D.h"
#include"../../../DKJEN/Type/Particle.h"
class FirstScene :public IScene {
public:
	//初期化
	void Initialize()override;
	//更新
	void Update(GameManager* gameManager)override;
	//描画
	void Draw()override;
	//ui
	void ImGui()override;
private:


	int time;
	Vector4 color;
	Sprite* spriteDKJEN;
	Sprite* spriteBlack;
};