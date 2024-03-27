#include "Enemy.h"

void Enemy::Initialize()
{
 	sprite_ = new Sprite;
	uint32_t tex = TexManager::LoadTexture("resource/tex.png");
	sprite_->Initialize(tex);
	pos_ = { 500.0f,100.0f,0.0f };
	speed_ = 5;
}

void Enemy::Update()
{
	pos_.x = pos_.x + speed_;
	if (pos_.x == 1200) {
		speed_ = speed_ * -1;
	}
	if (pos_.x == 10) {
		speed_ = speed_ * -1;
	}
}

void Enemy::Draw()
{
	sprite_->Draw({ 10.0f,10.0f,1 }, { 0,0,0 }, pos_, { 1.0f,0.0f,0.0f,1.0f });

}
