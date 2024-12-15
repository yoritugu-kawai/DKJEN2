#pragma once
#include<map>
#include<vector>
#include<memory>
#include"../Base/WinApp.h"
#include"../Base/DxCommon.h"
#include"../Base/Function.h"
#include"../externals/DirectXTex/d3dx12.h"
#include"../externals/DirectXTex/DirectXTex.h"
#include"../Management/DescriptorManagement.h"
#include"../TexDeta/Image/ImageData.h"
#include"../Base/CreateBufferResource.h"

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
	Matrix4x4 WorldInverseTranspose;
	Vector4 color = { 1,1,1,1 };
	Matrix4x4 uvTransform_ = MakeIdentity4x4();
};

struct DirectionalLight {
	Vector4 color;
	Vector3 direction;
	float intensity;


};
struct CameraMatrixData {
	
	Matrix4x4 viewMatrix_;
	//射影行列
	Matrix4x4 projectionMatrix_;
	//正射影行列
	Matrix4x4 orthographicMatrix_;
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
     const D3D12_RESOURCE_DESC GetResourceDesc(uint32_t textureHandle);

	static void Initiluze();
	static uint32_t LoadTexture(const std::string& filePath);
	static uint32_t DDSLoadTexture(const std::string& filePath);
	//void Draw();
	static void End();
	static DirectX::ScratchImage LoadTextureData(const std::string& filePath);
	static DirectX::ScratchImage DDSLoadTextureData(const std::string& filePath);
	static ID3D12Resource* CreateTexResource(const DirectX::TexMetadata& metadata);
	static ID3D12Resource* DDSCreateTexResource(const DirectX::TexMetadata& metadata);
	
	static void UploadTexData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);
	
	static ID3D12Resource* DDSUploadTexData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

	static void ShaderResourceView();
	static uint32_t GetDescriptorSizeSRV(){return TexManager::GetInstance()->descriptorSizeSRV;}



private:
	struct TextureInformation {

		//リソース
		ComPtr<ID3D12Resource> resource_ = nullptr;
		ComPtr<ID3D12Resource> internegiateResource_ = nullptr;

		DirectX::ScratchImage mipImages_ = {};
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc_ = {};


		//読み込んだテクスチャの名前
		std::string name_ = {};

		//テクスチャハンドル
		uint32_t handle_ = 0;
	};
	DxCommon dxcommon_;

	uint32_t descriptorSizeSRV;
	uint32_t descriptorSizeRTV;
	uint32_t descriptorSizeDSV;
	std::map<std::string, TextureInformation> textureInformation_{};
	std::map<string, std::unique_ptr<ImageData>>imageDatas;
	static bool CheckImageData(string filePath);
	std::map<uint32_t, std::string> handleToFilePathMap_{};
	///
	
};
