#pragma once
#include"../GameSeen/StateSeen/IScene.h"
#include"../GameSeen/StartSeen/StartSeen.h"
#include"../GameSeen/PlayScene/PlayScene.h"
#include"Project/GameScene/test.h"
#include"../../DKJEN/FirstScene/FirstScene.h"
class GameManager
{
public:
	//初期化
	void Initialize();
	//更新処理
	void Update();
	//描画
	void Draw();
	//シーン切り替え
	void ChangeState(IScene* stateSeen);
	//ステイトパターン
	IScene*iseen_ = nullptr;
};
