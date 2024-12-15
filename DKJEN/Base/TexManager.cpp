#include"TexManager.h"

static uint32_t LoadCount;
TexManager* TexManager::GetInstance()
{
	static TexManager instance;

	return &instance;
}

void TexManager::Initiluze()
{
	uint32_t descriptorSizeSRV = TexManager::GetInstance()->descriptorSizeSRV;
	uint32_t descriptorSizeRTV = TexManager::GetInstance()->descriptorSizeRTV;
	uint32_t descriptorSizeDSV = TexManager::GetInstance()->descriptorSizeDSV;
	CoInitializeEx(0, COINIT_MULTITHREADED);
	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();
	descriptorSizeSRV = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	descriptorSizeRTV = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	descriptorSizeDSV = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	LoadCount = 0;
	TexManager::GetInstance()->descriptorSizeSRV = descriptorSizeSRV;
	TexManager::GetInstance()->descriptorSizeRTV = descriptorSizeRTV;
	TexManager::GetInstance()->descriptorSizeDSV = descriptorSizeDSV;

}

DirectX::ScratchImage TexManager::LoadTextureData(const std::string& filePath)
{

	//テクスチャファイルを読み込んでプログラムで扱えるようにする
	DirectX::ScratchImage image{};
	std::wstring filePathW = ConvertString(filePath);
	HRESULT hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);

	assert(SUCCEEDED(hr));
	//ミニマップの作成
	DirectX::ScratchImage mipImage{};
	hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImage);
	assert(SUCCEEDED(hr));

	//ミニマップ付きのデータを返す
	return mipImage;

}


ID3D12Resource* TexManager::CreateTexResource(const DirectX::TexMetadata& metadata)
{
	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();

	//1.metadataを基にResourceの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Width = UINT(metadata.width);
	resourceDesc.Height = UINT(metadata.height);
	resourceDesc.MipLevels = UINT16(metadata.mipLevels);
	resourceDesc.DepthOrArraySize = UINT16(metadata.arraySize);
	resourceDesc.Format = metadata.format;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension);

	//2.利用するHeapの設定。非常に特殊な運用。02_04exで一般的なケース版がある
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_CUSTOM;
	heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;


	//3.Resourceを生成する
	ID3D12Resource* resource = nullptr;
	[[maybe_unused]]  HRESULT hr = device->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&resource));

	assert(SUCCEEDED(hr));
	return resource;
}


ID3D12Resource* TexManager::DDSCreateTexResource(const DirectX::TexMetadata& metadata)
{
	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();
	//1.metadataを基にResourceの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Width = UINT(metadata.width);
	resourceDesc.Height = UINT(metadata.height);
	resourceDesc.MipLevels = UINT16(metadata.mipLevels);
	resourceDesc.DepthOrArraySize = UINT16(metadata.arraySize);
	resourceDesc.Format = metadata.format;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension);

	//2.利用するHeapの設定。非常に特殊な運用。02_04exで一般的なケース版がある
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;

	//3.Resourceを生成する
	ID3D12Resource* resource = nullptr;
	[[maybe_unused]] HRESULT hr = device->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(&resource));

	assert(SUCCEEDED(hr));
	return resource;
}



void TexManager::UploadTexData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages)
{
	//Meta情報を取得
	const DirectX::TexMetadata& metadata = mipImages.GetMetadata();

	//全MipMapについて
	for (size_t mipLevel = 0; mipLevel < metadata.mipLevels; ++mipLevel)
	{
		//MipMapLevelを指定して各Imagesを取得
		const DirectX::Image* img = mipImages.GetImage(mipLevel, 0, 0);

		//Textureに転送
		[[maybe_unused]]  HRESULT hr = texture->WriteToSubresource(
			UINT(mipLevel),
			nullptr, //全領域へコピー
			img->pixels, //元データアドレス
			UINT(img->rowPitch), //1ラインサイズ
			UINT(img->slicePitch) //1枚サイズ
		);

		assert(SUCCEEDED(hr));
	}

}

ID3D12Resource* TexManager::DDSUploadTexData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages)
{
	ID3D12GraphicsCommandList* commandList = DxCommon::GetInstance()->GetCommandList();
	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();

	std::vector<D3D12_SUBRESOURCE_DATA> subresources;
	DirectX::PrepareUpload(device, mipImages.GetImages(), mipImages.GetImageCount(), mipImages.GetMetadata(), subresources);
	uint64_t intermediateSize = GetRequiredIntermediateSize(texture, 0, UINT(subresources.size()));
	ID3D12Resource* intermediateResource = CreateBufferResource(intermediateSize);
	UpdateSubresources(commandList, texture, intermediateResource, 0, 0, UINT(subresources.size()), subresources.data());

	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = texture;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;
	commandList->ResourceBarrier(1, &barrier);
	return intermediateResource;

}

void TexManager::ShaderResourceView()
{


}

bool TexManager::CheckImageData(string filePath)
{
	if (TexManager::GetInstance()->imageDatas.find(filePath) == TexManager::GetInstance()->imageDatas.end()) {
		return true;
	}
	return false;
}


uint32_t TexManager::LoadTexture(const std::string& filePath)
{
	if (CheckImageData(filePath)) {
		SImageData texData;



		//ID3D12DescriptorHeap* srvDescriptorHeap = DxCommon::GetInstance()->GetsrvDescriptorHeap();

		//Textureを読んで転送する
		DirectX::ScratchImage mipImages = LoadTextureData(filePath);
		const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
		texData.size.x = static_cast<float>(metadata.width);
		texData.size.y = static_cast<float>(metadata.height);
		texData.resource = CreateTexResource(metadata);
		UploadTexData(texData.resource.Get(), mipImages);

		//テキストのシェダ－
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
		srvDesc.Format = metadata.format;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = UINT(metadata.mipLevels);
		texData.index = DescriptorManagement::Allocate();

		DescriptorManagement::CreateShaderResourceView(texData.index, srvDesc, texData.resource);




		TexManager::GetInstance()->imageDatas[filePath] =
			std::make_unique<ImageData>(filePath, texData);
	}
	//TexManager* texManager = TexManager::GetInstance();
	return TexManager::GetInstance()->imageDatas[filePath]->GetImageIndex();
}
const D3D12_RESOURCE_DESC TexManager::GetResourceDesc(uint32_t textureHandle) {
	
	auto it = handleToFilePathMap_.find(textureHandle);
	if (it != handleToFilePathMap_.end()) {
		const std::string& filePath = it->second;
		return textureInformation_[filePath].resource_->GetDesc();
	}

	// エラーハンドリング: 見つからなかった場合の空のリソース記述子を返す
	return D3D12_RESOURCE_DESC{};
}

DirectX::ScratchImage TexManager::DDSLoadTextureData(const std::string& filePath) {

	HRESULT hr = {};

	//テクスチャファイルを読んでプログラムで扱えるようにする
	DirectX::ScratchImage image{};
	std::wstring filePathW = ConvertString(filePath);
	//dssファイルの場合
	if (filePathW.ends_with(L".dds")) {
		hr = DirectX::LoadFromDDSFile(filePathW.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, image);
		assert(SUCCEEDED(hr));
	}
	//その他のpngやjpegなど
	else {
		hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
		assert(SUCCEEDED(hr));

	}


	//ミップマップ...元画像より小さなテクスチャ群
	DirectX::ScratchImage mipImages{};
	//圧縮フォーマットかどうかを調べる
	if (DirectX::IsCompressed(image.GetMetadata().format)) {
		//圧縮フォーマットならそのまま使う
		mipImages = std::move(image);
	}
	else {
		hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 4, mipImages);
		assert(SUCCEEDED(hr));

	}


	//ミップマップ月のデータを返す
	return mipImages;
}


uint32_t TexManager::DDSLoadTexture(const std::string& filePath) {

	if (CheckImageData(filePath)) {
		SImageData texData;

		//Textureを読んで転送する
		DirectX::ScratchImage mipImages = DDSLoadTextureData(filePath);
		const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
		texData.size.x = static_cast<float>(metadata.width);
		texData.size.y = static_cast<float>(metadata.height);
		texData.resource = DDSCreateTexResource(metadata);
		DDSUploadTexData(texData.resource.Get(), mipImages);

		//テキストのシェダ－
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
		srvDesc.Format = metadata.format;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
		srvDesc.Texture2D.MipLevels = UINT(metadata.mipLevels);
		texData.index = DescriptorManagement::Allocate();

		DescriptorManagement::CreateShaderResourceView(texData.index, srvDesc, texData.resource);



		TexManager::GetInstance()->imageDatas[filePath] =
			std::make_unique<ImageData>(filePath, texData);
	}
	return TexManager::GetInstance()->imageDatas[filePath]->GetImageIndex();
}

void TexManager::End()
{
	CoUninitialize();
}
