#include "StartSeen.h"

void StartSeen::Initialize()
{

}

void StartSeen::Update(GameManager* gameManager)
{
	
	
	//シーン移行

		if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
	
	gameManager->ChangeState(new PlayScene);
	}
}

void StartSeen::Draw()
{
	
}

void StartSeen::ImGui()
{
}
