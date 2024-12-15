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
void DescriptorManagement::CreateShaderResourceViewForTexture2D(const uint32_t& srvIndex, ID3D12Resource* pResource, const  DXGI_FORMAT& format, const UINT& mipLevels, const bool& isCubeMap) {
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();
	srvDesc.Format = format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

	if (isCubeMap == true) {
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
		//unionがTextureCubeになったが、内部パラメータの意味はTexture2Dと変わらない
		srvDesc.TextureCube.MostDetailedMip = 0;
		srvDesc.TextureCube.MipLevels = UINT_MAX;
		srvDesc.TextureCube.ResourceMinLODClamp = 0.0f;
	}
	else {
		//2Dテクスチャ
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = UINT(mipLevels);

	}

	//SRVを作る
	device->CreateShaderResourceView(pResource, &srvDesc, CPUDescriptorHandle(srvIndex));

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
