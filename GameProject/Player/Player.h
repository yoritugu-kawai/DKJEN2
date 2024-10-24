#pragma once
#include"../../DKJEN/Type/Sprite.h"
#include"../../DKJEN/Utilipy/Input.h"

class Player
{
public:
	//全部変更予定
	void Initialize();
	void Input();
	void Update();
	void Draw();
	Vector3 GetPos() {return pos_;}


private:
	//全部変更予定
	Sprite* sprite_;
	Vector3 pos_;

	bool isShot_;
};
