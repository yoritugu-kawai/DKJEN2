#include "CameraData.h"

void CameraData::Create()
{
	this->view_ = MakeIdentity4x4();
	this->projection_ = MakeIdentity4x4();
	buffer_ = CreateBufferResource(sizeof(CameraCBuffer));
	
}

void CameraData::Update()
{
	Matrix4x4 rx = MakeRotateXMatrix(rotate_.x);
	Matrix4x4 ry = MakeRotateYMatrix(rotate_.y);
	Matrix4x4 rz = MakeRotateZMatrix(rotate_.z);

	Matrix4x4 rxyz = Multiply(rx, Multiply(ry, rz));
	Matrix4x4 t = MakeTranslateMatrix(translate_);
	view_ = Multiply(Inverse(rxyz), Inverse(t));
	projection_ = MakePerspectiveFovMatrix(fov_, aspectRiot_, nearClip_, farClip_);
	buffer_.Get()->Map(0, nullptr, reinterpret_cast<void**>(&data_));
	data_->pos = translate_;
}


ID3D12Resource* CameraData::CreateBufferResource(size_t sizeInbyte)
{
	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();
	ID3D12Resource* RssultResource;
	//頂点リソース用のヒープの設定
	D3D12_HEAP_PROPERTIES uploadHeapProperties{};

	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD; //UploadHeapを使う

	//頂点リソースの設定
	D3D12_RESOURCE_DESC ResourceDesc{};

	//バッファリソース。テクスチャの場合はまた別の設定をする
	ResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	ResourceDesc.Width = sizeInbyte; //リソースのサイズ。今回はvector4を3頂点分

	//バッファの場合はこれらは1にする決まり
	ResourceDesc.Height = 1;
	ResourceDesc.DepthOrArraySize = 1;
	ResourceDesc.MipLevels = 1;
	ResourceDesc.SampleDesc.Count = 1;

	//バッファの場合はこれにする決まり
	ResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	HRESULT hr;
	hr = device->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE,
		&ResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&RssultResource));
	assert(SUCCEEDED(hr));

	return RssultResource;
}