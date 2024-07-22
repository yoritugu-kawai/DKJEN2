#pragma once
#include"DxCommon.h"
#include"../Shader/CompileShaderManager.h"

class SkyBoxPSO
{
public:
	static SkyBoxPSO* GetInstance();

	//PSO

	static void CreatePSO();
	static void Release();
	static PSO GetPSO() { return SkyBoxPSO::GetInstance()->pso_; }
private:
	//
	static void ShapePSO();
	HRESULT hr;//

	PSO pso_;
};
