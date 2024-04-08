#pragma once
#include"../../DKJEN/Type/Sprite.h"
class Block
{
public:
	void Initialize(Vector3 pos);
	void Update();
	void Draw();
	Vector3 GetPos() { return pos_; }
private:
	Sprite* sprite_;
	Vector3 pos_;
};
