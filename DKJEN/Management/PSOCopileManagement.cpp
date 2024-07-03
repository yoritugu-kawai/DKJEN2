#include"PSOCopileManagement.h"


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
	Animation3DCompileShader::DXC();
	ParticleCompileShader::DXC();
	LightCompileShader::DXC();

	TextureCompileShader::ShaderCompile();
	PolygonCompileShader::ShaderCompile();
	SpriteCompileShader::ShaderCompile();
	Animation3DCompileShader::ShaderCompile();
	ParticleCompileShader::ShaderCompile();
	LightCompileShader::ShaderCompile();

	TexturePSO::CreatePSO();
	PolygonPSO::CreatePSO();
	SpritePSO::CreatePSO();
	Animation3DPSO::CreatePSO();
	ParticlePSO::CreatePSO();
	LightPSO::CreatePSO();



}

void PSOCopileManagement::Release()
{
	TextureCompileShader::Release();
	PolygonCompileShader::Release();
	SpriteCompileShader::Release();
	Animation3DCompileShader::Release();
	ParticleCompileShader::Release();

	TexturePSO::Release();
	PolygonPSO::Release();
	SpritePSO::Release();
	Animation3DPSO::Release();
	ParticlePSO::Release();
	LightPSO::Release();

}
