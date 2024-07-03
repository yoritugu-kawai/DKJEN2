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
	static D3D12_CPU_DESCRIPTOR_HANDLE CPUDescriptorHandle( uint32_t descriptorSizeSRV, D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc, ComPtr <ID3D12Resource>textureResource);
	static D3D12_GPU_DESCRIPTOR_HANDLE GPUDescriptorHandle( uint32_t descriptorSizeSRV);
	static void rootParamerterCommand(UINT rootPatramerterIndex, uint32_t texhandle);
	static void IndexIncrement() { DescriptorManagement::GetInstance()->index++; }
	static uint32_t GetIndex() { return DescriptorManagement::GetInstance()->index; }
#pragma region Get
	static D3D12_CPU_DESCRIPTOR_HANDLE GetSRVHCPU(int index) { return DescriptorManagement::GetInstance()->SrvHandleCPU[index]; }
	static D3D12_GPU_DESCRIPTOR_HANDLE GetSRVHGPU(int index) { return DescriptorManagement::GetInstance()->SrvHandleGPU[index]; }

#pragma endregion

#pragma region Set
	static void SetSRVHCPU(D3D12_CPU_DESCRIPTOR_HANDLE SrvHCPU, int index) { DescriptorManagement::GetInstance()->SrvHandleCPU[index] = SrvHCPU; }
	static void SetSRVHGPU(D3D12_GPU_DESCRIPTOR_HANDLE SrvHGPU, int index) { DescriptorManagement::GetInstance()->SrvHandleGPU[index] = SrvHGPU; }
#pragma endregion
private:
	D3D12_CPU_DESCRIPTOR_HANDLE SrvHandleCPU[DESCRIPTER_MAX]{};
	D3D12_GPU_DESCRIPTOR_HANDLE SrvHandleGPU[DESCRIPTER_MAX]{};

	 uint32_t index=0;

};
