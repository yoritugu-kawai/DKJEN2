#pragma once
#include"../Base/WinApp.h"
#include"../Base/DxCommon.h"
#include"../Base/Function.h"
#include"../externals/DirectXTex/d3dx12.h"
#include"../externals/DirectXTex/DirectXTex.h"
#include"../Base/TexManager.h"
#define DESCRIPTER_MAX 64

class DescriptorManagement
{
public:

	static DescriptorManagement* GetInstance();
	static void Initialize();
	static void CreateShaderResourceView(uint32_t index,D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc, ComPtr <ID3D12Resource>textureResource);
	static void CreateShaderResourceViewForTexture2D(const uint32_t& srvIndex, ID3D12Resource* pResource, const  DXGI_FORMAT& format, const UINT& mipLevels, const bool& isCubeMap);
	static D3D12_CPU_DESCRIPTOR_HANDLE CPUDescriptorHandle( uint32_t index);
	static D3D12_GPU_DESCRIPTOR_HANDLE GPUDescriptorHandle( uint32_t index);
	static void rootParamerterCommand(UINT rootPatramerterIndex, uint32_t index);
	//static void IndexIncrement() { DescriptorManagement::GetInstance()->index++; }

	static uint32_t Allocate() { 
		uint32_t useIndex = DescriptorManagement::GetInstance()->index;
		DescriptorManagement::GetInstance()->index++;

		return useIndex;
	
	}

private:

	 uint32_t index=0;


};
