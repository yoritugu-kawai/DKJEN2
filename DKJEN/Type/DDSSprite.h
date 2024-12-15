#pragma once



#include <string>
#include <format>


#include"../Math/Math.h"
#include"../Base/DxCommon.h"
#include"../Base/SpritePSO.h"
#include"../Base/TexManager.h"
#include"../Base/CreateBufferResource.h"
#include"../Management/DescriptorManagement.h"
#include"../../Base/CreateBufferResource.h"
#include"../Math/Math.h"
struct DDSMaterialData {
	Vector4 color;
	int32_t lightingKinds;
	float padding[3];
	Matrix4x4 uvTransform;
	float shininess;
	bool isEnviromentMap;
};
class DDSSprite {
public:


	DDSSprite() = default;

	static DDSSprite* Create(uint32_t textureHandle, Vector3 position);


	void Draw();


	~DDSSprite() = default;



public:
#pragma region アクセッサ

	//色
	void SetTransparency(float transparency) {
		this->color_.w = transparency;
	}
	void SetColor(Vector4 color) {
		this->color_ = color;
	}



	//拡縮
	void SetScale(Vector2 scale) {
		this->scale_ = scale;
	}
	const Vector2 GetScale() {
		return scale_;
	}



	//回転
	void SetRotate(float rotate) {
		this->rotate_ = rotate;
	}
	const float GetRotate() {
		return rotate_;
	}



	//位置
	void SetPosition(Vector3 position) {
		this->position_ = position;
	}
	const Vector3 GetPosition() {
		return position_;
	}



	//アンカーポイント
	void SetAnchorPoint(Vector2 point) {
		this->anchorPoint_ = point;
	}
	const Vector2 GetAnchorPoint() {
		return anchorPoint_;
	}



	//フリップ
	void SetFlipX(bool isFlipX) {
		this->isFlipX_ = isFlipX;
	}
	const bool GetFlipX() {
		return isFlipX_;
	}

	void SetFlipY(bool isFlipY) {
		this->isFlipY_ = isFlipY;
	}
	const bool GetFlipY() {
		return isFlipY_;
	}



	void SetInvisible(bool isInvisible) {
		this->isInvisible_ = isInvisible;
	}
	const bool GetInvisible() {
		return isInvisible_;
	}


	//UV
	void SetTextureLeftTop(Vector2 textureLeftTop) {
		this->textureLeftTop_ = textureLeftTop;
	}
	const Vector2 GetTextureLeftTop() {
		return textureLeftTop_;
	}

	void SetTextureSize(Vector2 textureSize) {
		this->textureSize_ = textureSize;
	}
	const Vector2 GetTextureSize() {
		return textureSize_;
	}

	void SetUVMode(bool isUVMode) {
		this->isUVSetting_ = isUVMode;
	}
	const bool GetUVMode() {
		return isUVSetting_;
	}



#pragma endregion



private:
	//初期化
	void Initialize(uint32_t textureHandle, Vector3 position);

	//Vertex
	void CreateVertexBufferView();
	//Index
	void CreateIndexBufferView();



private:


#pragma region リソース



	
	ComPtr<ID3D12Resource> vertexResource_ = nullptr;

	ComPtr<ID3D12Resource> materialResource_ = nullptr;
	DDSMaterialData* materialData_ = nullptr;

	ComPtr<ID3D12Resource> transformationMatrixResource_ = nullptr;
	TransformationMatrix* transformationMatrixData_ = nullptr;


	VertexData* vertexData_ = nullptr;


	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_ = {};





	ComPtr<ID3D12Resource> indexResource_ = nullptr;

	D3D12_INDEX_BUFFER_VIEW indexBufferView_{};

	uint32_t* indexData_ = nullptr;

	static const int MAX_TEXTURE_ = 20;



	ComPtr<ID3D12Resource> textureResource_ = nullptr;
	ComPtr<ID3D12Resource> resource_ = nullptr;




#pragma endregion


	enum VERTEX_POSITION {
		//左下
		LEFT_BOTTOM,

		//左上
		LEFT_TOP,

		//右下
		RIGHT_BOTTOM,

		//右上
		RIGHT_TOP,

	};


	Transform uvTransformSprite_ = {};

	int textureIndex_ = 0;

	
	
	//サイズ
	Vector2 size_ = {};

	//S
	Vector2 scale_ = { 1.0f,1.0f };
	//R
	float rotate_ = 0.0f;
	//T
	Vector2 originPosition_ = { 0.0f,0.0f };
	Vector3 position_ = { 0.0f,0.0f,0.0f };

	//アンカーポイント
	Vector2 anchorPoint_ = { 0.0f,0.0f };
	//色
	Vector4 color_ = {};

	//左右フリップ
	bool isFlipX_ = false;
	//上下フリップ
	bool isFlipY_ = false;


	//非表示
	bool isInvisible_ = false;


	//テクスチャ範囲設定
	Vector2 textureLeftTop_ = { 0.0f,0.0f };
	Vector2 textureSize_ = { 100.0f,100.0f };

	bool isUVSetting_ = false;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	Vector4 transX_ = { 10.f,0.0f,0.0f,1.0f };
	Vector4 transY_ = { 0.0f,10.0f,0.0f,1.0f };
	Vector4 transXY_ = { 10.0f,10.0f,0.0f,1.0f };
	//ブレンドモード
	uint32_t blendModeNumber_ = 1;
	Vector2 texcoord00LT = { 0.0f,0.0f };
	Vector2 texcoord10RT = { 1.0f,0.0f };
	Vector2 texcoord01LD = { 0.0f,1.0f };
	Vector2 texcoord11RD = { 1.0f,1.0f };
};

