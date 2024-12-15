#include "GameManager.h"

void GameManager::Initialize()
{
	//初期化
	iseen_ = new Test;
	iseen_->Initialize();
}

void GameManager::Update()
{
	//更新
	iseen_->Update(this);
	iseen_->ImGui();
}

void GameManager::Draw()
{
	//描画
	iseen_->Draw();
}

void GameManager::ChangeState(IScene* stateSeen)
{
	//シーン切り替え
	delete iseen_;
	iseen_ = stateSeen;
	iseen_->Initialize();
	iseen_->Update(this);
	iseen_->Draw();
	return;
}
