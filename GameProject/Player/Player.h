#pragma once
#include"../../DKJEN/Type/Sprite.h"
#include"../../DKJEN/Utilipy/Input.h"
#include"Bullet.h"
class Player
{
public:
	void Initialize();
	void Input();
	void Update();
	void Draw();
	Vector3 GetBulletPos() {return bulletPos_;}


private:
	Bullet* bullet_;
	Sprite* sprite_;
	Vector3 pos_;
	Vector3 bulletPos_;
	bool isShot_;
};
