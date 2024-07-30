#pragma once


#include"../../GameProject/GameManager/GameManager.h"
class GameScene
{
public:
	void Initialize();

	void Update();

	void Draw();

private:
	
	/// <summary>
	/// 
	/// </summary>
	GameManager* gameManager_;
};

