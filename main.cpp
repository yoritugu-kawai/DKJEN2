#include"Project/ProjectManager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ProjectManager* projectManager_=new ProjectManager;
	projectManager_->Gear();
	delete projectManager_;
	return 0;
}
