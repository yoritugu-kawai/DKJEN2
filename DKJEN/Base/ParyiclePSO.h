#pragma once
#include"DxCommon.h"
#include"../Shader/CompileShaderManager.h"

class ParticlePSO
{
public:
	static ParticlePSO* GetInstance();

	//PSO

	static void CreatePSO();
	static void Release();
	static PSO GetPSO() { return ParticlePSO::GetInstance()->pso_; }
private:
	//
	static void ShapePSO();
	HRESULT hr;//

	PSO pso_;
};
