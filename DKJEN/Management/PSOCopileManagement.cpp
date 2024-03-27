#include"PSOCopileManagement.h"

//PSOCopileManagement PSOCopileManagement::GetInstance()
//{
//	static PSOCopileManagement instance;
//
//	return &instance;
//}

PSOCopileManagement* PSOCopileManagement::GetInstance()
{
	static PSOCopileManagement instance;
	return &instance;
}

void PSOCopileManagement::Set()
{
	TextureCompileShader::DXC();
	PolygonCompileShader::DXC();
	SpriteCompileShader::DXC();
	LightCompileShader::DXC();
	ParticleCompileShader::DXC();

	TextureCompileShader::ShaderCompile();
	PolygonCompileShader::ShaderCompile();
	SpriteCompileShader::ShaderCompile();
	LightCompileShader::ShaderCompile();
	ParticleCompileShader::ShaderCompile();

	TexturePSO::CreatePSO();
	PolygonPSO::CreatePSO();
	SpritePSO::CreatePSO();
	LightPSO::CreatePSO();
	ParticlePSO::CreatePSO();


}

void PSOCopileManagement::Release()
{
	TextureCompileShader::Release();
	PolygonCompileShader::Release();
	SpriteCompileShader::Release();
	LightCompileShader::Release();
	ParticleCompileShader::Release();

	TexturePSO::Release();
	PolygonPSO::Release();
	SpritePSO::Release();
	LightPSO::Release();
	ParticlePSO::Release();

}
