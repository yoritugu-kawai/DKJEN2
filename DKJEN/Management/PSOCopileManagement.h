#pragma once
#include"../Shader/CompileShaderManager.h"


#include"../Base/Animation3DPSO.h"
//#include"../Base/PolygonPSO.h"
#include"../Base/SpritePSO.h"
#include"../Base/TexturePSO.h"
#include"../Base/ParyiclePSO.h"
#include"../Base/LightPSO.h"
#include"../Base/SkyBoxPSO.h"

class PSOCopileManagement
{
public:
	static PSOCopileManagement* GetInstance();

	static void Set();
	static void Release();
private:

};
