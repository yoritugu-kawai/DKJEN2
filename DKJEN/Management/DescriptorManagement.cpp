#include "DescriptorManagement.h"

DescriptorManagement* DescriptorManagement::GetInstance()
{
	static DescriptorManagement instance;

	return &instance;
}

void DescriptorManagement::Initialize()
{
}

void DescriptorManagement::CreateShaderResourceView(uint32_t index,D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc, ComPtr<ID3D12Resource> textureResource)
{
	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();
	device->CreateShaderResourceView(textureResource.Get(), &srvDesc,CPUDescriptorHandle(index));
}

D3D12_CPU_DESCRIPTOR_HANDLE DescriptorManagement::CPUDescriptorHandle(uint32_t index)
{
	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();

	ID3D12DescriptorHeap* srvDescriptorHeap = DxCommon::GetInstance()->GetsrvDescriptorHeap();

	D3D12_CPU_DESCRIPTOR_HANDLE srvHandleCPU = srvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();


	srvHandleCPU.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)*index;
	
	return  srvHandleCPU;
}

D3D12_GPU_DESCRIPTOR_HANDLE DescriptorManagement::GPUDescriptorHandle(uint32_t index)
{
	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();

	ID3D12DescriptorHeap* srvDescriptorHeap = DxCommon::GetInstance()->GetsrvDescriptorHeap();

	D3D12_GPU_DESCRIPTOR_HANDLE srvHandleGPU = srvDescriptorHeap->GetGPUDescriptorHandleForHeapStart();


	srvHandleGPU.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) * index;

	return  srvHandleGPU;
	
}

void DescriptorManagement::rootParamerterCommand(UINT rootPatramerterIndex, uint32_t index)
{
	ID3D12GraphicsCommandList* commandList = DxCommon::GetInstance()->GetCommandList();

	commandList->SetGraphicsRootDescriptorTable(
		rootPatramerterIndex,
		GPUDescriptorHandle(index)
	);
}
