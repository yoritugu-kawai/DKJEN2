#include "DDSSprite.h"

#include <vector>





void DDSSprite::Initialize(uint32_t textureHandle, Vector3 position) {
	this->textureHandle_ = textureHandle;
	this->position_ = position;
	color_ = { 1.0f,1.0f,1.0f,1.0f };

	//テクスチャの情報を取得
	resourceDesc_ = TexManager::GetInstance()->GetResourceDesc(textureHandle_);
	size_ = { float(resourceDesc_.Width),float(resourceDesc_.Height) };



	vertexResource_ = CreateBufferResource(sizeof(VertexData) * 6);

	indexResource_ = CreateBufferResource(sizeof(uint32_t) * 6);

	materialResource_ = CreateBufferResource(sizeof(DDSMaterialData));

	transformationMatrixResource_ = CreateBufferResource(sizeof(TransformationMatrix));



	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	vertexBufferView_.SizeInBytes = sizeof(VertexData) * 4;
	vertexBufferView_.StrideInBytes = sizeof(VertexData);

	indexBufferView_.BufferLocation = indexResource_->GetGPUVirtualAddress();
	indexBufferView_.SizeInBytes = sizeof(uint32_t) * 6;
	indexBufferView_.Format = DXGI_FORMAT_R32_UINT;


	uvTransformSprite_ = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};



}

DDSSprite* DDSSprite::Create(uint32_t textureHandle, Vector3 position) {
	DDSSprite* sprite = new DDSSprite();
	sprite->Initialize(textureHandle, position);
	return sprite;

}

void DDSSprite::Draw() {

	if (isInvisible_ == true) {
		return;
	}

	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));







	//1枚目の三角形
	//左下
	vertexData_[LEFT_BOTTOM].position = { transX_ };
	vertexData_[LEFT_BOTTOM].texcoord = { textureLeftTop_.x / resourceDesc_.Width,(textureLeftTop_.y + textureSize_.y) / resourceDesc_.Height };

	//左上
	vertexData_[LEFT_TOP].position = { 0.0f,0.0f,0.0f,1.0f };
	vertexData_[LEFT_TOP].texcoord = { textureLeftTop_.x / resourceDesc_.Width,textureLeftTop_.y / resourceDesc_.Height };

	//右下
	vertexData_[RIGHT_BOTTOM].position = { transXY_ };
	vertexData_[RIGHT_BOTTOM].texcoord = { (textureLeftTop_.x + textureSize_.x) / resourceDesc_.Width,(textureLeftTop_.y + textureSize_.y) / resourceDesc_.Height };


	//右上
	vertexData_[RIGHT_TOP].position = { transY_ };
	vertexData_[RIGHT_TOP].texcoord = { (textureLeftTop_.x + textureSize_.x) / resourceDesc_.Width,textureLeftTop_.y / resourceDesc_.Height };



	indexResource_->Map(0, nullptr, reinterpret_cast<void**>(&indexData_));
	indexData_[0] = 0;
	indexData_[1] = 1;
	indexData_[2] = 2;
	indexData_[3] = 1;
	indexData_[4] = 3;
	indexData_[5] = 2;




	transformationMatrixResource_->Map(0, nullptr, reinterpret_cast<void**>(&transformationMatrixData_));



	Matrix4x4 worldMatrix = MakeAffineMatrix({ scale_.x,scale_.y,1.0f }, { 0.0f,0.0f,rotate_ }, position_);
	//遠視投影行列
	Matrix4x4 viewMatrix = MakeIdentity4x4();

	Matrix4x4 projectionMatrix = MakeOrthographicMatrix(0.0f, 0.0f, float(WinApp::GetInstance()->Width()), float(WinApp::GetInstance()->Height()), 0.0f, 100.0f);

	//WVP行列を作成
	Matrix4x4 worldViewProjectionMatrixSprite = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));

	transformationMatrixData_->WVP = worldViewProjectionMatrixSprite;
	transformationMatrixData_->World = MakeIdentity4x4();

	transformationMatrixResource_->Unmap(0, nullptr);

	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));
	materialData_->color = color_;
	//ライティングしない
	materialData_->lightingKinds = 0;
	materialData_->shininess = 0.0f;

	Matrix4x4 uvTransformMatrix = MakeScaleMatrix(uvTransformSprite_.scale);
	uvTransformMatrix = Multiply(uvTransformMatrix, MakeRotateZMatrix(uvTransformSprite_.rotate.z));
	uvTransformMatrix = Multiply(uvTransformMatrix, MakeTranslateMatrix(uvTransformSprite_.translate));
	materialData_->uvTransform = uvTransformMatrix;
	PSOProperty pso_ = SpritePSO::GetInstance()->GetPSO().Texture;
	ID3D12GraphicsCommandList* commandList = DxCommon::GetInstance()->GetCommandList();
	//コマンドを積む
	commandList->SetGraphicsRootSignature(pso_.rootSignature);
	commandList->SetPipelineState(pso_.GraphicsPipelineState);

	commandList->IASetVertexBuffers(0, 1, &vertexBufferView_);
	commandList->IASetIndexBuffer(&indexBufferView_);
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	commandList->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());
	commandList->SetGraphicsRootConstantBufferView(1, transformationMatrixResource_->GetGPUVirtualAddress());


	if (textureHandle_ != 0) {
		DescriptorManagement::rootParamerterCommand(2, textureHandle_);

	}


	commandList->DrawIndexedInstanced(6, 1, 0, 0, 0);


}