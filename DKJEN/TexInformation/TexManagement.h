#pragma once
#include"../Math/Math.h"
class TexManagement
{
public:
	static TexManagement *GetInstance();
	static void Initialize();
	static void Finalize();
	static uint32_t LoadImage(const std::string& filePath);



private:

};
