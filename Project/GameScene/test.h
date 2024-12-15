#pragma once
#include"../../GameProject/GameSeen/StateSeen/IScene.h"
#include"../../../DKJEN/Type/DDSSprite.h"
#include"../../../DKJEN/Type/Sprite.h"
#include"../../GameProject/GameManager/GameManager.h"
#include"../../../DKJEN/Camera/CameraData.h"
#include"../../../DKJEN/Type/Obj3D.h"
#include"../../../DKJEN/Type/Particle.h"
class Test :public IScene {
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
	/// <summary>
	/// カメラ
	/// </summary>
	CameraData* cameraData;
	std::unique_ptr<DDSSprite>dds = nullptr;

};