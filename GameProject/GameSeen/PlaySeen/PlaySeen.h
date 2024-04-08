#pragma once
#include"../StateSeen/IScene.h"
#include"../../Enemy/Enemy.h"
#include"../../Player/Player.h"
#include"../../Block/Block.h"
#include"../../GameManager/GameManager.h"
class PlaySeen:public IScene {
public:
	void Initialize()override;
	void Update(GameManager* gameManager)override;
	void Draw()override;
private:
	
	int time;
	Player* player_;
	Block* block_[];
};