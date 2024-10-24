#include"Project/ProjectManager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//宣言
	ProjectManager* projectManager_=new ProjectManager;
	//メイン
	projectManager_->Gear();
	//デーリーと
	delete projectManager_;
	return 0;
}
