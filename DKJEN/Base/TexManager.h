#pragma once
#include<map>
#include<memory>
#include"../Base/WinApp.h"
#include"../Base/DxCommon.h"
#include"../Base/Function.h"
#include"../externals/DirectXTex/d3dx12.h"
#include"../externals/DirectXTex/DirectXTex.h"
#include"../Management/DescriptorManagement.h"
#include"../TexDeta/Image/ImageData.h"
struct VertexData {
	Vector4 position;
	Vector2 texcoord;
	Vector3 normal;
};
struct TexProeerty {
	D3D12_GPU_DESCRIPTOR_HANDLE SrvHandleGPU;

	ID3D12Resource* Resource;


};
struct Material {

	Vector4 color;
	int32_t enableLighting;
	
};
struct TransformationMatrix {
	Matrix4x4 WVP;
	Matrix4x4 World;
	Vector4 color = { 1,1,1,1 };
	Matrix4x4 uvTransform_ = MakeIdentity4x4();
};

struct DirectionalLight {
	Vector4 color;
	Vector3 direction;
	float intensity;


};

struct CameraCBuffer {
	Vector3 pos;
};

struct UVMaterial {

	Vector4 color;
	Matrix4x4 uvTransform;

};

class TexManager
{
public:
	static TexManager* GetInstance();

	static void Initiluze();
	static uint32_t LoadTexture(const std::string& filePath);
	//void Draw();
	static void End();
	static DirectX::ScratchImage LoadTextureData(const std::string& filePath);
	static ID3D12Resource* CreateTexResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);
	static void UploadTexData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);
	static void ShaderResourceView();
	static uint32_t GetDescriptorSizeSRV(){return TexManager::GetInstance()->descriptorSizeSRV;}
	
private:
	DxCommon dxcommon_;

	uint32_t descriptorSizeSRV;
	uint32_t descriptorSizeRTV;
	uint32_t descriptorSizeDSV;
	
	std::map<string, std::unique_ptr<ImageData>>imageDatas;
	static bool CheckImageData(string filePath);
};
