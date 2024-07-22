#include "SkyBox.h"

void SkyBox::Initialize()
{
	HRESUT hr;
	if (fileRathW.ends_with(L".dds")) {
		hr=DirectX::LoadFromDDSFile(fileRathW.c_str(),Direct::DDS_FLAGS_NONE,nullptr,image)

	}
	else {
		hr = DirectX::LoadFromWICFile(fileRathW.c_str(), DirectX::WIC_FORCE_SRGB, nullptr, image);
	}

	////////////////////////////////

	DirectX::ScratchImge mipImages{};
	if (DirectX::IsCompressed(image.GetMetadata().format)) {
		mipImages = std::move(image);
	}
	else {
		hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadate(), DirectX::TEX_FILTER_SRGB, 4, mipImages);

	}
	//////////////////////////////////////

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	if (meradara.IsCubemap()) {
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
		srvDesc.TextureCube.MostDetailedMip = 0;
		srvDesc.TextureCubeMipLevels = UINT_MAX;
		srvDesc.TextureCube.ResourceMinLODClamp=0.0f;
	}
	else {

	}
	///////////
	vertexData[0].position = { 1.0f,1.0f,1.0f,1.0f };
	vertexData[1].position = { 1.0f,1.0f,-1.0f,1.0f };
	vertexData[2].position = { 1.0f,-1.0f,1.0f,1.0f };
	vertexData[3].position = { 1.0f,-1.0f,-1.0f,1.0f };

	vertexData[4].position = { -1.0f,1.0f,-1.0f,1.0f };
	vertexData[5].position = { -1.0f,1.0f,1.0f,1.0f };
	vertexData[6].position = { -1.0f,-1.0f,-1.0f,1.0f };
	vertexData[7].position = { -1.0f,-1.0f,1.0f,1.0f };

	vertexData[8].position = { -1.0f,1.0f,1.0f,1.0f };
	vertexData[9].position = { 1.0f,1.0f,-1.0f,1.0f };
	vertexData[10].position = { -1.0f,-1.0f,1.0f,1.0f };
	vertexData[11].position = { 1.0f,-1.0f,1.0f,1.0f };
	/////
	DepthStencilState.DepthEnable = true;
	DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
	DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
}
