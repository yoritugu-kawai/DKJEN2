#pragma once
#include"../StateSeen/IScene.h"
#include"../../Enemy/Enemy.h"
#include"../../Player/Player.h"
#include"../../Block/Block.h"
#include"../../Ball/Ball.h"
#include"../../GameManager/GameManager.h"
class PlaySeen:public IScene {
public:
	void Initialize()override;
	void Update(GameManager* gameManager)override;
	void Draw()override;
	void LoadBlockPopData();
	void UpdateBlockPopCommands();
	void AllCollisions();
private:
	int speed_;
	int time;
	Player* player_;
	Block* block_;
	Ball* ball_;
	std::list<Block*>blocks_;
	std::stringstream blockPopCommands;
};