#include "clearScene.h"

void clearScene::Initialize()
{

}

void clearScene::Update(GameManager* gameManager)
{
	
		if (Input::GetInstance()->PushKeyPressed(DIK_S)) {
			gameManager->ChangeState(new StartSeen);

		}
	
}

void clearScene::Draw()
{
}

void clearScene::ImGui()
{
#ifdef _DEBUG
	ImGui::Begin("Color");
	ImGui::DragFloat4("c", &animaionTime, 0.1f, -1.0f, 1.0f);
	ImGui::DragFloat4("s", &playerPos_.x, 0.1f, -500.0f, 1000.0f);
	ImGui::DragFloat3("p", &cPos.x, 1.0f, -1000.0f, 100.0f);
	
	float flame = ImGui::GetIO().Framerate;
	if (ImGui::TreeNode("System"))
	{


		ImGui::Text("FPS::%f", flame);
		ImGui::TreePop();
	}
	ImGui::End();

#endif // _DEBUG
}
