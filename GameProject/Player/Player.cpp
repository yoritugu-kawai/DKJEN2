#include "Player.h"

void Player::Initialize()
{
	sprite_ = new Sprite;
	uint32_t tex = TexManager::LoadTexture("resource/tex.png");
	sprite_->Initialize(tex);
	pos_ = { 500.0f,360.0f,0.0f };
	bullet_ = new Bullet;
	bullet_->Initialize();
	isShot_ = false;
	
}

void Player::Input()
{

	if (Input::GetInstance()->PushKey(DIK_A)) {
		pos_.x -= 5;

	}
	if (Input::GetInstance()->PushKey(DIK_D)) {
		pos_.x += 5;
	}

	if (Input::GetInstance()->PushKey(DIK_W)) {
		pos_.y -= 5;
	}
	if (Input::GetInstance()->PushKey(DIK_S)) {
		pos_.y += 5;
	}
}

void Player::Update()
{
	Input();

	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		isShot_ = true;
	}
	
	if (!isShot_) 
	bullet_->SetPos(pos_);

	if (isShot_)
	bullet_->Update();

	isShot_ = bullet_->GetIsShot();
	bulletPos_ = bullet_->GetPos();

}

void Player::Draw()
{
	sprite_->Draw({ 10.0f,10.0f,1 }, { 0,0,0 }, pos_, { 1.0f,1.0f,1.0f,1.0f });
	if (isShot_) bullet_->Draw();
	
}
