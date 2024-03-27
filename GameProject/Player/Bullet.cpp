#include "Bullet.h"

void Bullet::Initialize()
{
	sprite_ = new Sprite;
	uint32_t tex = TexManager::LoadTexture("resource/tex.png");
	sprite_->Initialize(tex);
	speed_ = 10;
	isShot_ = false;

}


void Bullet::Update()
{
	isShot_ = true;
	pos_.y -= speed_;
	if (pos_.y<=-10) {
		pos_ = pos_;
		isShot_ = false;
	}
	
}

void Bullet::Draw()
{
	sprite_->Draw({ 10.0f,10.0f,1 }, { 0,0,0 }, pos_, { 1.0f,0.0f,1.0f,1.0f });
}
