#pragma once
#include"../StateSeen/IScene.h"
#include"../../Enemy/Enemy.h"
#include"../../Player/Player.h"
#include"../../GameManager/GameManager.h"
class PlaySeen:public IScene {
public:
	void Initialize()override;
	void Update(GameManager* gameManager)override;
	void Draw()override;
private:
	Sprite* uv;
	Sprite* ball;
	int time;
};