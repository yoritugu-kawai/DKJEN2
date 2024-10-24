#pragma once

//#include"../../GameManager/GameManager.h"
class GameManager;
class IScene {
public:
	//初期化
	virtual void Initialize() = 0;
	//更新処理
	virtual void Update(GameManager* gameManager) = 0;
	//描画
	virtual void Draw() = 0;
	//ImGui
	virtual void ImGui() = 0;
	//デストラクタ
	virtual ~IScene() {};

private:
	
};