#include "GameManager.h"

void GameManager::Initialize()
{
	iseen_ = new StartSeen;
	iseen_->Initialize();
}

void GameManager::Update()
{
	iseen_->Update(this);
	iseen_->ImGui();
}

void GameManager::Draw()
{
	iseen_->Draw();
}

void GameManager::ChangeState(IScene* stateSeen)
{
	//delete iseen_;
	iseen_ = stateSeen;
	iseen_->Initialize();
	iseen_->Update(this);
	iseen_->Draw();
	return;
}
