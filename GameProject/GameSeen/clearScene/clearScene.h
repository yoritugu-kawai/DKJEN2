#pragma once
#include"../StateSeen/IScene.h"
#include"../PlayScene/PlayScene.h"
#include"../../../DKJEN/Type/Sprite.h"
#include"../../GameManager/GameManager.h"
#include"../../../DKJEN/Camera/CameraData.h"
#include"../../../DKJEN/Type/Obj3D.h"

class clearScene :public IScene {
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
private:

	
};