#pragma once
#include"../GameSeen/StateSeen/IScene.h"
#include"../GameSeen/StartSeen/StartSeen.h"
#include"../GameSeen/PlayScene/PlayScene.h"
#include"DKJEN/FirstScene/FirstScene.h"
class GameManager
{
public:
	void Initialize();
	void Update();
	void Draw();
	void ChangeState(IScene* stateSeen);
	IScene*iseen_ = nullptr;
};
