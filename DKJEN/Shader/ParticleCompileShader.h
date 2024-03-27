#pragma once

#include"../Base/DxCommon.h"

class ParticleCompileShader
{
public:
	static ParticleCompileShader* GetInstance();
	static void DXC();
	static void ShaderCompile();
	static void Release();
	//
	static Shaders GetShaders() { return ParticleCompileShader::GetInstance()->shaders_; }
private:
	static IDxcBlob* CompileShaderFanc(
		const std::wstring& filePath,
		const wchar_t* profile);
	/*DIX*/
	IDxcUtils* dxcUtils;/*後々の可能性あり*/
	IDxcCompiler3* dxcCompiler;/*後々の可能性あり*/
	IDxcIncludeHandler* includeHandler;/*後々の可能性あり*/
	Shaders shaders_;
};
