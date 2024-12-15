//#include "DDS.h"
//#include "SrvManager.h"
//
//
//#include <vector>
//
//uint32_t DDS::index_ = 0u;
//
//
//DDS* DDS::GetInstance() {
//
//	static DDS instance;
//	return &instance;
//}
//
//
//
//
//const D3D12_RESOURCE_DESC DDS::GetResourceDesc(uint32_t textureHandle) {
//
//	auto it = handleToFilePathMap_.find(textureHandle);
//	if (it != handleToFilePathMap_.end()) {
//		const std::string& filePath = it->second;
//		return textureInformation_[filePath].resource_->GetDesc();
//	}
//
//	
//	return D3D12_RESOURCE_DESC{};
//}
//
//
//
//
//uint32_t DDS::LoadTexture(const std::string& filePath) {
//
//	DDS* textureManager = DDS::GetInstance();
//
//
//	auto it = DDS::GetInstance()->textureInformation_.find(filePath);
//	if (it != DDS::GetInstance()->textureInformation_.end()) {
//		return it->second.handle_;
//	}
//
//
//
//
//	index_ = SrvManager::GetInstance()->Allocate();
//
//
//
//	TextureInformation textureInfo;
//	textureInfo.handle_ = index_;
//	textureInfo.name_ = filePath;
//
//
//	textureInfo.handle_ = index_;
//
//	textureInfo.name_ = filePath;
//
//
//	textureInfo.mipImages_ = LoadTextureData(filePath);
//
//	const DirectX::TexMetadata& metadata = textureInfo.mipImages_.GetMetadata();
//
//	textureInfo.resource_ = CreateTextureResource(metadata);
//	textureInfo.internegiateResource_ = UploadTextureData(
//		textureInfo.resource_.Get(), textureInfo.mipImages_).Get();
//
//
//
//
//
//	SrvManager::GetInstance()->CreateSRVForTexture2D(
//		textureInfo.handle_,
//		textureInfo.resource_.Get(),
//		metadata.format, UINT(metadata.mipLevels), metadata.IsCubemap());
//
//
//	
//	textureManager->GetTextureInformation()[filePath] = std::move(textureInfo);
//
//	DDS::GetInstance()->handleToFilePathMap_[index_] = filePath;
//
//	return textureInfo.handle_;
//}
//
//
//
//
//DirectX::ScratchImage DDS::LoadTextureData(const std::string& filePath) {
//
//	HRESULT hr = {};
//
//	DirectX::ScratchImage image{};
//	std::wstring filePathW = ConvertString(filePath);
//
//	if (filePathW.ends_with(L".dds")) {
//		hr = DirectX::LoadFromDDSFile(filePathW.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, image);
//		assert(SUCCEEDED(hr));
//	}
//
//	else {
//		hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
//		assert(SUCCEEDED(hr));
//
//	}
//
//	
//	DirectX::ScratchImage mipImages{};
//	
//	if (DirectX::IsCompressed(image.GetMetadata().format)) {
//	
//		mipImages = std::move(image);
//	}
//	else {
//		hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 4, mipImages);
//		assert(SUCCEEDED(hr));
//
//	}
//
//	return mipImages;
//}
//
//
//ComPtr<ID3D12Resource> DDS::CreateTextureResource(const DirectX::TexMetadata& metadata) {
//	ComPtr<ID3D12Resource> resource = nullptr;
//
//	
//
//	D3D12_RESOURCE_DESC resourceDesc{};
//
//	resourceDesc.Width = UINT(metadata.width);
//	
//	resourceDesc.Height = UINT(metadata.height);
//
//	resourceDesc.MipLevels = UINT16(metadata.mipLevels);
//
//	resourceDesc.DepthOrArraySize = UINT16(metadata.arraySize);
//
//	resourceDesc.Format = metadata.format;
//
//	resourceDesc.SampleDesc.Count = 1;
//
//	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension);
//
//
//	D3D12_HEAP_PROPERTIES heapProperties{};
//
//	heapProperties.Type = D3D12_HEAP_TYPE_CUSTOM;
//
//	heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
//
//	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
//
//
//
//	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();
//	//3.Resourceを生成する
//
//	HRESULT hr = device->CreateCommittedResource(
//		&heapProperties,					
//		D3D12_HEAP_FLAG_NONE,				
//		&resourceDesc,						
//		D3D12_RESOURCE_STATE_COPY_DEST,		
//		nullptr,							
//		IID_PPV_ARGS(&resource));			
//	assert(SUCCEEDED(hr));
//
//	return resource;
//
//
//}
//
//
//[[nodiscard]]
//ComPtr<ID3D12Resource> DDS::UploadTextureData(ComPtr<ID3D12Resource> texture, const DirectX::ScratchImage& mipImages) {
//
//	ID3D12GraphicsCommandList* commandList = DxCommon::GetInstance()->GetCommandList();
//	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();
//
//	std::vector<D3D12_SUBRESOURCE_DATA> subresources;
//	DirectX::PrepareUpload(device, mipImages.GetImages(), mipImages.GetImageCount(), mipImages.GetMetadata(), subresources);
//	uint64_t intermidiateSize = GetRequiredIntermediateSize(texture.Get(), 0, UINT(subresources.size()));
//	ComPtr<ID3D12Resource> intermediateSizeResource = CreateBufferResource(intermidiateSize);
//	UpdateSubresources(commandList, texture.Get(), intermediateSizeResource.Get(), 0, 0, UINT(subresources.size()), subresources.data());
//
//	//Textureへの転送後は利用できるよう、D312_RESOURCE_STATE_COPY_DESTから
//	//D3D12_RESOURCE_STATE_GENERIC_READへResourceStateを変更する
//	D3D12_RESOURCE_BARRIER barrier{};
//	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
//	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
//	barrier.Transition.pResource = texture.Get();
//	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
//	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
//	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;
//	commandList->ResourceBarrier(1, &barrier);
//
//
//	return intermediateSizeResource;
//}
//
//
//
//#pragma endregion
//
//
//
//#pragma endregion
//
//
//void DDS::GraphicsCommand(uint32_t rootParameter, uint32_t texHandle) {
//	SrvManager::GetInstance()->SetGraphicsRootDescriptorTable(rootParameter, texHandle);
//}
//
