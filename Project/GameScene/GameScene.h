#pragma once


#include"../../GameProject/GameManager/GameManager.h"
class GameScene
{
public:
	//初期化
	void Initialize();
	//更新処理
	void Update();
	//描画
	void Draw();

private:
	
	/// <summary>
	/// ゲームまとめ
	/// </summary>
	GameManager* gameManager_;
};

