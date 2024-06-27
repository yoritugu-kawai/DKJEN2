#pragma once
#include"../Shader/Animation3DCompileShader.h"
#include"../Shader/PolygonCompileShader.h"
#include"../Shader/SpriteCompileShader.h"
#include"../Shader/TextureCompileShader.h"
#include"../Shader/ParticleCompileShader.h"

#include"../Base/Animation3DPSO.h"
#include"../Base/PolygonPSO.h"
#include"../Base/SpritePSO.h"
#include"../Base/TexturePSO.h"
#include"../Base/ParyiclePSO.h"

class PSOCopileManagement
{
public:
	static PSOCopileManagement* GetInstance();

	static void Set();
	static void Release();
private:

};
