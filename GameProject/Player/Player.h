#pragma once
#include"../../DKJEN/Type/Sprite.h"
#include"../../DKJEN/Utilipy/Input.h"

class Player
{
public:
	void Initialize();
	void Input();
	void Update();
	void Draw();
	Vector3 GetPos() {return pos_;}


private:
	
	Sprite* sprite_;
	Vector3 pos_;

	bool isShot_;
};
