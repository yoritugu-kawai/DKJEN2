#pragma once
#include"../StateSeen/IScene.h"
#include"../PlaySeen/PlaySeen.h"
#include"../../../DKJEN/Type/Sprite.h"
#include"../../GameManager/GameManager.h"
class StartSeen:public IScene {
public:
	void Initialize()override;
	void Update(GameManager* gameManager)override;
	void Draw()override;
private:
	Sprite* sprite_;
	Vector3 pos_ = { 0,0,0 };
	float color_;
	bool change_;
};