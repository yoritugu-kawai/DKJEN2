#include "DescriptorManagement.h"

DescriptorManagement* DescriptorManagement::GetInstance()
{
	static DescriptorManagement instance;

	return &instance;
}

void DescriptorManagement::Initialize()
{
}

D3D12_CPU_DESCRIPTOR_HANDLE DescriptorManagement::CPUDescriptorHandle( uint32_t descriptorSizeSRV, D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc, ComPtr <ID3D12Resource>textureResource)
{
	uint32_t index =DescriptorManagement::GetInstance()->index;

	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();
	ID3D12DescriptorHeap* srvDescriptorHeap = DxCommon::GetInstance()->GetsrvDescriptorHeap();
	DescriptorManagement::GetInstance()->SrvHandleCPU[index] =
		GetCPUDescriptorHandle(
			srvDescriptorHeap, descriptorSizeSRV, GetIndex());
	DescriptorManagement::GetInstance()->SrvHandleCPU[index].ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)*index;
	device->CreateShaderResourceView(textureResource.Get(), &srvDesc, DescriptorManagement::GetInstance()->SrvHandleCPU[index]);
	return  DescriptorManagement::GetInstance()->SrvHandleCPU[index];
}

D3D12_GPU_DESCRIPTOR_HANDLE DescriptorManagement::GPUDescriptorHandle(uint32_t descriptorSizeSRV)
{
	uint32_t index = DescriptorManagement::GetInstance()->index;
	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();
	ID3D12DescriptorHeap* srvDescriptorHeap = DxCommon::GetInstance()->GetsrvDescriptorHeap();

	DescriptorManagement::GetInstance()->SrvHandleGPU[index] =
		GetGPUDescriptorHandle(
			srvDescriptorHeap, descriptorSizeSRV, GetIndex());
	DescriptorManagement::GetInstance()->SrvHandleGPU[index].ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) * index;
	return DescriptorManagement::GetInstance()->SrvHandleGPU[index];
	
}

void DescriptorManagement::rootParamerterCommand(UINT rootPatramerterIndex, uint32_t texhandle)
{
	ID3D12GraphicsCommandList* commandList = DxCommon::GetInstance()->GetCommandList();

	commandList->SetGraphicsRootDescriptorTable(
		rootPatramerterIndex,
		DescriptorManagement::GetInstance()->SrvHandleGPU[texhandle]
	);
}
