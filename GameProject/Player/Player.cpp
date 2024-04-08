#include "Player.h"

void Player::Initialize()
{
	sprite_ = new Sprite;
	uint32_t tex = TexManager::LoadTexture("resource/tex.png");
	sprite_->Initialize(tex);
	pos_ = { 500.0f,650.0f,0.0f };

	isShot_ = false;
	
}

void Player::Input()
{

	if (Input::GetInstance()->PushKey(DIK_A)) {
		pos_.x -= 10;

	}
	if (Input::GetInstance()->PushKey(DIK_D)) {
		pos_.x += 10;
	}

}

void Player::Update()
{
	Input();

}

void Player::Draw()
{
	sprite_->Draw({ 7.0f,2.0f,1 }, { 0,0,0 }, pos_, { 1.0f,1.0f,1.0f,1.0f });
	
}
