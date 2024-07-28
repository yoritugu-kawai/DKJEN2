#pragma once
#include"../StateSeen/IScene.h"

#include"../../Player/Player.h"
#include"../../Block/Block.h"

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
	
	std::list<Block*>blocks_;
	std::stringstream blockPopCommands;
};