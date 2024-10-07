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
	void Initialize()override;
	void Update(GameManager* gameManager)override;
	void Draw()override;
	void ImGui()override;
private:


	int time;
	Vector4 color;
	Sprite* spriteDKJEN;
	Sprite* spriteBlack;
};