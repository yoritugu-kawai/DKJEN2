#pragma once
#include"DxCommon.h"
#include"../Shader/CompileShaderManager.h"

class Animation3DPSO
{
public:
	static Animation3DPSO* GetInstance();

	//PSO

	static void CreatePSO();
	static void Release();
	static PSO GetPSO() { return Animation3DPSO::GetInstance()->pso_; }
private:
	//
	static void ShapePSO();
	HRESULT hr;//

	PSO pso_;
};
