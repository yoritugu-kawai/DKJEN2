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
	//初期化
	void Initialize()override;
	//更新処理
	void Update(GameManager* gameManager)override;
	//描画
	void Draw()override;
	//ImGui
	void ImGui()override;
private:
	//全部変更予定

	int time;
	float speed;
	Sprite* sprite;
	Vector4 color;
	Sprite* spriteSelect;
};