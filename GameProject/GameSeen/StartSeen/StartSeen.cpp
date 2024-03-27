#include "StartSeen.h"

void StartSeen::Initialize()
{
	sprite_ = new Sprite;
	uint32_t tex = TexManager::LoadTexture("resource/space.png");
	sprite_->Initialize(tex);
	color_ = 1.0f;
	change_ = false;
}

void StartSeen::Update(GameManager* gameManager)
{
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		change_ = true;
		
	}
	if (change_) {
		color_ -= 0.01f;
	}
	if (color_ <= 0) {

 		gameManager->ChangeState(new PlaySeen);
	}
}

void StartSeen::Draw()
{
	sprite_->Draw({ 128.0f,72.0f,1 }, { 0,0,0 }, pos_, {0.0f,1.0f,1.0f,color_ });
}
