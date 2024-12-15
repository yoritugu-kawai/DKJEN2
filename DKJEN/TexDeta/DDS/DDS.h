#pragma once
#include <d3d12.h>
#include <string>
#include <array>
#include"../DKJEN/DKJEN/Utilipy/AdditionInclude.h"
#include"../../Base/CreateBufferResource.h"
#include"../DKJEN/DKJEN/externals/DirectXTex/DirectXTex.h"
#include <map>
#include"../../externals/DirectXTex/d3dx12.h"
#include"../../Base/DxCommon.h"
#include "../../Base/Log.h"

class DDS {
private:

	DDS() = default;


	~DDS() = default;

public:
	static DDS* GetInstance();


	DDS(const DDS& textureManager) = delete;


	DDS& operator=(const DDS& textureManager) = delete;


public:

	
	static uint32_t LoadTexture(const std::string& filePath);
	static void GraphicsCommand(uint32_t rootParameter, uint32_t texHandle);
	const D3D12_RESOURCE_DESC GetResourceDesc(uint32_t textureHandle);

private:



	static DirectX::ScratchImage LoadTextureData(const std::string& filePath);


	static ComPtr<ID3D12Resource> CreateTextureResource(const DirectX::TexMetadata& metadata);
	static ComPtr<ID3D12Resource> UploadTextureData(ComPtr<ID3D12Resource> texture, const DirectX::ScratchImage& mipImages);


public:


	struct TextureInformation {

		ComPtr<ID3D12Resource> resource_ = nullptr;
		ComPtr<ID3D12Resource> internegiateResource_ = nullptr;

		DirectX::ScratchImage mipImages_ = {};
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc_ = {};


	
		std::string name_ = {};

		uint32_t handle_ = 0;
	};

	inline std::map<std::string, TextureInformation>& GetTextureInformation() {
		return textureInformation_;
	}

private:

	static uint32_t index_;


	std::map<std::string, TextureInformation> textureInformation_{};
	std::map<uint32_t, std::string> handleToFilePathMap_{};

};