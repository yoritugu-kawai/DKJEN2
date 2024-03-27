#pragma once
#include"../../DKJEN/Type/Sprite.h"
class Enemy
{
public:
	void Initialize();
	void Update();
	void Draw();
	Vector3 GetPos() { return pos_; }
private:
	Sprite* sprite_;
	Vector3 pos_;
	bool isDie_;
	int speed_;
};
