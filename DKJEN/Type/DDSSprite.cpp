#include "DDSSprite.h"

#include "TextureManager.h"


//動的配列
#include <vector>



//Vertex
void DDSSprite::CreateVertexBufferView() {
	//リソースの先頭のアドレスから使う
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	//使用するリソースのサイズは頂点３つ分のサイズ
	vertexBufferView_.SizeInBytes = sizeof(VertexData) * 4;
	//１頂点あたりのサイズ
	vertexBufferView_.StrideInBytes = sizeof(VertexData);
}

//Index
void DDSSprite::CreateIndexBufferView() {

	//リsp－スの先頭のアドレスから使う
	indexBufferView_.BufferLocation = indexResource_->GetGPUVirtualAddress();
	//使用するリソースのサイズはインデックス6つ分のサイズ
	indexBufferView_.SizeInBytes = sizeof(uint32_t) * 6;
	//インデックスはuint32_tとする
	indexBufferView_.Format = DXGI_FORMAT_R32_UINT;

}





void DDSSprite::Initialize(uint32_t textureHandle, Vector3 position) {
	this->textureHandle_ = textureHandle;
	this->position_ = position;
	color_ = { 1.0f,1.0f,1.0f,1.0f };


	resourceDesc_ = TextureManager::GetInstance()->GetResourceDesc(textureHandle_);
	size_ = { float(resourceDesc_.Width),float(resourceDesc_.Height) };



	vertexResource_ = CreateBufferResource(sizeof(VertexData) * 6);
	
	indexResource_ = CreateBufferResource(sizeof(uint32_t) * 6);

	materialResource_ = CreateBufferResource(sizeof(MaterialData));

	transformationMatrixResource_ = CreateBufferResource(sizeof(TransformationMatrix));


	//頂点バッファビューを作成する
	CreateVertexBufferView();

	//Indexを利用
	CreateIndexBufferView();


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

	float left = (0.0f - anchorPoint_.x) * size_.x;
	float right = (1.0f - anchorPoint_.x) * size_.x;
	float top = (0.0f - anchorPoint_.y) * size_.y;
	float bottom = (1.0f - anchorPoint_.y) * size_.y;


	float texLeft = 0.0f;
	float texRight = 1.0f;
	float texTop = 0.0f;
	float texBottom = 1.0f;


	if (isUVSetting_ == true) {
		//uv
		texLeft = textureLeftTop_.x / resourceDesc_.Width;
		texRight = (textureLeftTop_.x + textureSize_.x) / resourceDesc_.Width;
		texTop = textureLeftTop_.y / resourceDesc_.Height;
		texBottom = (textureLeftTop_.y + textureSize_.y) / resourceDesc_.Height;
	}




	//左右反転
	if (isFlipX_ == true) {
		left = -left;
		right = -right;
	}
	//上下反転
	if (isFlipY_ == true) {
		top = -top;
		bottom = -bottom;
	}


	//1枚目の三角形
	//左下
	vertexData_[LEFT_BOTTOM].position = { left,bottom,0.0f,1.0f };
	vertexData_[LEFT_BOTTOM].texcoord = { texLeft,texBottom };

	//左上
	vertexData_[LEFT_TOP].position = { left,top,0.0f,1.0f };
	vertexData_[LEFT_TOP].texcoord = { texLeft,texTop };

	//右下
	vertexData_[RIGHT_BOTTOM].position = { right,bottom,0.0f,1.0f };
	vertexData_[RIGHT_BOTTOM].texcoord = { texRight,texBottom };


	//右上
	vertexData_[RIGHT_TOP].position = { right,top,0.0f,1.0f };
	vertexData_[RIGHT_TOP].texcoord = { texRight,texTop };



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

	Matrix4x4 projectionMatrix = MakeOrthographicMatrix(0.0f, 0.0f, float(WindowsSetup::GetInstance()->GetClientWidth()), float(WindowsSetup::GetInstance()->GetClientHeight()), 0.0f, 100.0f);

	//WVP行列を作成
	Matrix4x4 worldViewProjectionMatrixSprite = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));

	transformationMatrixData_->WVP = worldViewProjectionMatrixSprite;
	transformationMatrixData_->World = MakeIdentity4x4();

	transformationMatrixResource_->Unmap(0, nullptr);


	//マテリアルにデータを書き込む
	//書き込むためのアドレスを取得
	//reinterpret_cast...char* から int* へ、One_class* から Unrelated_class* へなどの変換に使用
	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));
	materialData_->color = color_;
	//ライティングしない
	materialData_->lightingKinds = 0;
	materialData_->shininess = 0.0f;

	Matrix4x4 uvTransformMatrix = Matrix4x4Calculation::MakeScaleMatrix(uvTransformSprite_.scale);
	uvTransformMatrix = Matrix4x4Calculation::Multiply(uvTransformMatrix, Matrix4x4Calculation::MakeRotateZMatrix(uvTransformSprite_.rotate.z));
	uvTransformMatrix = Matrix4x4Calculation::Multiply(uvTransformMatrix, Matrix4x4Calculation::MakeTranslateMatrix(uvTransformSprite_.translate));
	materialData_->uvTransform = uvTransformMatrix;


	//コマンドを積む
	DirectXSetup::GetInstance()->GetCommandList()->SetGraphicsRootSignature(PipelineManager::GetInstance()->GetSpriteRootSignature().Get());
	DirectXSetup::GetInstance()->GetCommandList()->SetPipelineState(PipelineManager::GetInstance()->GetSpriteGraphicsPipelineState().Get());


	//RootSignatureを設定。PSOに設定しているけど別途設定が必要
	DirectXSetup::GetInstance()->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView_);
	//IBVを設定
	DirectXSetup::GetInstance()->GetCommandList()->IASetIndexBuffer(&indexBufferView_);

	//形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えよう
	DirectXSetup::GetInstance()->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//CBVを設定する
	DirectXSetup::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());
	DirectXSetup::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(1, transformationMatrixResource_->GetGPUVirtualAddress());


	if (textureHandle_ != 0) {
		TextureManager::GraphicsCommand(2, textureHandle_);

	}

	//今度はこっちでドローコールをするよ
	//描画(DrawCall)6個のインデックスを使用し1つのインスタンスを描画。
	DirectXSetup::GetInstance()->GetCommandList()->DrawIndexedInstanced(6, 1, 0, 0, 0);


}
