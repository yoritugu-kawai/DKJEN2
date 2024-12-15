#include "test.h"

void Test::Initialize()
{
	uint32_t tex = TexManager::GetInstance()->DDSLoadTexture("test.dds");
	Vector3 position = { .x = 10.0f,.y = 10.0f,.z = 10.0f };
	dds.reset(DDSSprite::Create(tex, position));
}

void Test::Update(GameManager* gameManager)
{
	gameManager;
	//dds->SetScale({ 10,10 });
}

void Test::Draw()
{
	dds->Draw();
}

void Test::ImGui()
{
}
