#pragma once
#pragma once
#include"DxCommon.h"
#include"../Shader/RenderTextrureCompileShader.h"

class RenderTextrurePSO
{
public:
	static RenderTextrurePSO* GetInstance();

	//PSO

	static void CreatePSO();
	static void Release();
	static PSO GetPSO() { return RenderTextrurePSO::GetInstance()->pso_; }
private:
	//
	static void ShapePSO();
	HRESULT hr;//

	PSO pso_;
};
