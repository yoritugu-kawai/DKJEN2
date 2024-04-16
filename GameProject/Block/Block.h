#pragma once
#include"../../DKJEN/Type/Sprite.h"

class Block
{
public:
	void Initialize(Vector3 pos);
	void Update();
	void Draw();
	Vector3 GetPos() { return pos_; }
	void IsErase();
	bool GetIsErase() { return isErase_; }
private:
	Sprite* sprite_;
	Vector3 pos_;
	bool isErase_;
	
};
