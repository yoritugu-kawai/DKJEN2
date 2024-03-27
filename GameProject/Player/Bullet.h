#pragma once
#include"../../DKJEN/Type/Sprite.h"
class Bullet
{
public:
	void Initialize();
	void Update();
	void Draw();
	Vector3 GetPos() { return pos_; }
	void SetPos(Vector3 pos) { pos_ = pos; }
	bool GetIsShot() { return isShot_; }
private:
	Sprite* sprite_;
	Vector3 pos_;
	uint32_t speed_;
	bool isShot_;
};
