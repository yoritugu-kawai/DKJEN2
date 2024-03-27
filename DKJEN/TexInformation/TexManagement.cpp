#include "TexManagement.h"

TexManagement* TexManagement::GetInstance()
{
	static TexManagement instance;

	return &instance;
}

void TexManagement::Initialize()
{
}
