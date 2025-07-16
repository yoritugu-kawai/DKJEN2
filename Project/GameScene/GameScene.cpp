#include "GameScene.h"

void GameScene::Initialize()
{
	//初期化
	
	Count_ = 0;
	time_ = 10;
}

void GameScene::Update()
{


	
	////更新
	if(time_>0){
		time_ -= 1 / 60.0f; //1秒間に60回更新されると仮定して、1フレームあたりの時間を減少させる
		if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
			//スペースキーが押されたらカウントアップ
			Count_++;

		}
	}
	
	if(Input::GetInstance()->PushKeyPressed(DIK_R)){
		//時間が0になったらカウントをリセット
		Count_ = 0;
		time_ = 10; //再度10秒にリセット
	}
}

void GameScene::Draw()
{
	
	//////描画
 #ifdef _DEBUG

	ImGui::Begin("UI");
	//ImGui::DragFloat3("c", &., 0.1f, -100.0f, 100.0f);
	ImGui::Text("How many buttons can you press in 10 seconds?");
	ImGui::Text("time: %0.f", time_);
	ImGui::Text("Count: %d", Count_);
	ImGui::End();


#endif // _DEBUG

}
