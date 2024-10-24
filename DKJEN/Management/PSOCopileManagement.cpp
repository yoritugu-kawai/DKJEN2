#include"PSOCopileManagement.h"


PSOCopileManagement* PSOCopileManagement::GetInstance()
{
	static PSOCopileManagement instance;
	return &instance;
}

void PSOCopileManagement::Set()
{

	CompileShaderManager::DXC();


	CompileShaderManager::ShaderCompile();
	

	TexturePSO::CreatePSO();
	//PolygonPSO::CreatePSO();
	SpritePSO::CreatePSO();
	Animation3DPSO::CreatePSO();
	ParticlePSO::CreatePSO();
	LightPSO::CreatePSO();
	SkyBoxPSO::CreatePSO();


}

void PSOCopileManagement::Release()
{
	CompileShaderManager::Release();
	

	TexturePSO::Release();
	///PolygonPSO::Release();
	SpritePSO::Release();
	Animation3DPSO::Release();
	ParticlePSO::Release();
	LightPSO::Release();
	SkyBoxPSO::Release();

}
