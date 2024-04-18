#pragma once
#include"../Math/Math.h"
#include"../Base/DxCommon.h"
#include"../Base/SpritePSO.h"
#include"../Base/TexManager.h"
#include"../Base/CreateBufferResource.h"
#include"../Management/DescriptorManagement.h"
class  Sprite
{
public:

	void Initialize(uint32_t  tex);
	void Vertex();
	void Draw(Vector3 scale, Vector3 rotate, Vector3 translate, Vector4 Color);
	// void Release();
	void SetTexcoord00LT(Vector2 texcoord) { texcoord00LT = texcoord; }
	void SetTexcoord10RT(Vector2 texcoord) { texcoord10RT = texcoord; }
	void SetTexcoord01LD(Vector2 texcoord) { texcoord01LD = texcoord; }
	void SetTexcoord11RD(Vector2 texcoord) { texcoord11RD = texcoord; }

	
private:

	//
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSprite{};
	D3D12_INDEX_BUFFER_VIEW indexBufferViewSprite{};

	VertexData* VertexDataSprite = nullptr;
	ComPtr<ID3D12Resource> vertexResourceSprite;
	ComPtr<ID3D12Resource>transformationMatrixResourceSprote;
	ComPtr<ID3D12Resource> materialResource;
	ComPtr<ID3D12Resource> indexResourceSprite;

	Matrix4x4* transformationMatrixDataSprite = nullptr;
	Transform transformSprite{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };


	uint32_t  tex_;
	Vector4 transX_ = { 10.f,0.0f,0.0f,1.0f };
	Vector4 transY_ = { 0.0f,10.0f,0.0f,1.0f };
	Vector4 transXY_ = { 10.0f,10.0f,0.0f,1.0f };
	Transform uvTranformSprite{
	 {1.0f,1.0f,1.0f},
	 {0.0f,0.0f,0.0f},
	 {0.0f,0.0f,0.0f}
	};
	Matrix4x4 matrix;
	Vector2 texcoord00LT = { 0.0f,0.0f };
	Vector2 texcoord10RT = { 1.0f,0.0f };
	Vector2 texcoord01LD = { 0.0f,1.0f };
	Vector2 texcoord11RD = { 1.0f,1.0f };
};


