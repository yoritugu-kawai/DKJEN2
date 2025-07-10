#include "PlayScene.h"

void PlayScene::Initialize()
{

}



//#ifdef _DEBUG
//	ImGui::Begin("Sphere");
//	ImGui::InputFloat3("Translate", &sphereNewTranslate.x);
//	ImGui::End();
//#endif // _DEBUG


void PlayScene::Update(GameManager* gameManager)
{
	//次の更新処理


	
	if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
		gameManager->ChangeState(new clearScene);

	}
}



void PlayScene::Draw()
{
}

void PlayScene::ImGui()
{
//#ifdef _DEBUG
//
//	ImGui::Begin("camera");
//	ImGui::DragFloat3("c", &cRot.x, 0.1f, -100.0f, 100.0f);
//	ImGui::DragFloat3("p", &cPos.x, 1.0f, -1000.0f, 100.0f);
//	ImGui::End();
//
//	ImGui::Begin("Speed");
//	ImGui::DragFloat("c", &standardSpeed_, 1.0f, -100.0f, 100.0f);
//
//	ImGui::End();
//
//	ImGui::Begin("pos");
//	ImGui::DragFloat3("p", &playerPos_.x, 0.1f, -100.0f, 100.0f);
//	ImGui::DragFloat3("r", &playerRot.x, 0.1f, -100.0f, 100.0f);
//	ImGui::End();
//
//#endif // _DEBUG
}

