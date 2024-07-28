#include "PlaySeen.h"

void PlaySeen::Initialize()
{
	
	
	player_ = new Player;
	player_->Initialize();
	time = 12;

	LoadBlockPopData();
}

void PlaySeen::LoadBlockPopData() {

	std::ifstream file;
	file.open("GameResource/block.csv");
	assert(file.is_open());
	blockPopCommands << file.rdbuf();
	file.close();
}

void PlaySeen::UpdateBlockPopCommands() {

	std::string line;
	// コマンドループ
	while (std::getline(blockPopCommands, line)) {
		std::istringstream line_stream(line);
		std::string word;

		std::getline(line_stream, word, ',');
		//"//"から始まるコメント
		if (word.find("//") == 0) {
			continue;
		}
		// PoPコマンド
		if (word.find("POP") == 0) {
			// X座標
			std::getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());
			// Y座標
			std::getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());
			// Z座標
			std::getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());
			// 敵発生

			block_ = new Block;
			block_->Initialize(Vector3(x, y, z));
			blocks_.push_back(block_);

		}

	}
}

void PlaySeen::AllCollisions() {
	blocks_.remove_if([](Block* block) {
		if (block->GetIsErase()) {
			delete block;
			return true;
		}

		return false;
		});
	speed_ = ball_->GetSpeedY();
	if (player_->GetPos().x <= ball_->GetPos().x + 40 &&
		ball_->GetPos().x <= player_->GetPos().x + 40 &&
		player_->GetPos().y <= ball_->GetPos().y + 40 &&
		ball_->GetPos().y <= player_->GetPos().y + 40) {
		speed_ *= -1;
		ball_->SetSpeedY(speed_);
	}
	for (Block* block_ : blocks_) {
		if (block_->GetPos().x <= ball_->GetPos().x + 50 &&
			ball_->GetPos().x <= block_->GetPos().x + 50 &&
			block_->GetPos().y <= ball_->GetPos().y + 50 &&
			ball_->GetPos().y <= block_->GetPos().y + 50) {
			speed_ *= -1;
			ball_->SetSpeedY(speed_);
			block_->IsErase();
		}
	}
}
void PlaySeen::Update(GameManager* gameManager)
{
	UpdateBlockPopCommands();
	player_->Update();
	time -= 1;
	ball_->Update();
	block_->Update();
	AllCollisions();
		
		
	if (ball_->GetPos().y >= 720) {
		gameManager->ChangeState(new StartSeen);

	}
}

void PlaySeen::Draw()
{
	ball_->Draw();
	player_->Draw();
	for (Block* block_ : blocks_) {
		block_->Draw();
	}
}
