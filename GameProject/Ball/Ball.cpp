#include "Ball.h"

void Ball::Initialize()
{
	sprite_ = new Sprite;
	uint32_t tex = TexManager::LoadTexture("GameResource/ball.png");
	sprite_->Initialize(tex);
	pos_ = { 500.0f,590.0f,0.0f };
	speedx_ = 7;
	speedy_ = 7;
}

void Ball::Update()
{
	pos_.x += speedx_;
	pos_.y += speedy_;
	if (pos_.x <= 30) {
		speedx_ *= -1;
	}
	if (pos_.x >= 1240) {
		speedx_ *= -1;
	}
	if (pos_.y <= 30) {
		speedy_ *= -1;
	}
	if (pos_.y >= 720) {
		speedy_ *= -1;
	}
}

void Ball::Draw()
{
	sprite_->Draw({5,5,0},{0,0,0}, pos_,{1,1,1,1});
}
