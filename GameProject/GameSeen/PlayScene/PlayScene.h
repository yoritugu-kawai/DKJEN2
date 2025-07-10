#pragma once
#include"../StateSeen/IScene.h"
#include"../clearScene/clearScene.h"
#include"../../Player/Player.h"


#include"../../GameManager/GameManager.h"

class PlayScene :public IScene {
public:

private:
	
	void Initialize();

	void Update(GameManager* gameManager);

	void Draw();
	void ImGui();
};