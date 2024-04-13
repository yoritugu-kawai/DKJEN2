#pragma once
#include"../../DKJEN/Type/Sprite.h"
class Ball
{
public:
	void Initialize();
	void Update();
	void Draw();
	Vector3 GetPos() { return pos_; }
	int GetSpeedY() { return speedy_; }
	void SetSpeedY(int speedy) {speedy_ = speedy;}
private:
	Sprite* sprite_;
	Vector3 pos_;
	int speedx_;
	int speedy_;
};
