#include "Block.h"

void Block::Initialize(Vector3 pos)
{
	sprite_ = new Sprite;
	uint32_t tex = TexManager::LoadTexture("GameResource/block.png");
	sprite_->Initialize(tex);
	pos_=pos;
}

void Block::Update()
{

}

void Block::Draw()
{
	sprite_->Draw({10.0f,5.0f,10.0f},{0.0f,0.0f,0.0f},{pos_},{1.0f,0.0f,1.0f,1.0f});
}
