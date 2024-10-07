#pragma once
#include"../StateSeen/IScene.h"
#include"../PlayScene/PlayScene.h"
#include"../../../DKJEN/Type/Sprite.h"
#include"../../GameManager/GameManager.h"
#include"../../../DKJEN/Camera/CameraData.h"
#include"../../../DKJEN/Type/Obj3D.h"
#include"../../../DKJEN/Type/Particle.h"
class SelectScene :public IScene {
public:
	void Initialize()override;
	void Update(GameManager* gameManager)override;
	void Draw()override;
	void ImGui()override;
private:


	int time;
	float speed;
	Sprite* sprite;
	Vector4 color;
	Sprite* spriteSelect;
};