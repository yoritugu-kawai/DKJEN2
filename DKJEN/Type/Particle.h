#pragma once
#include"../Math/Math.h"
#include"../Base/DxCommon.h"
#include"../Base/ParyiclePSO.h"
#include"../Base/ImageLoading.h"
#include"../Type/Obj3D.h"
#include"../Base/CreateBufferResource.h"
#include<fstream>
#include<sstream>
#include<random>
class Particle
{
public:
	void Initialize(uint32_t  tex);
	void Vertex(Vector4 pos);
	void Darw(Vector3 scale, Vector3 rotate, Vector3 translate, Vector4 Color);
	//void Release();
	void SRV();
	
private:

	//
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSprite{};
	D3D12_INDEX_BUFFER_VIEW indexBufferViewSprite{};

	VertexData* VertexDataSprite = nullptr;
	ComPtr<ID3D12Resource> vertexResourceSprite;
	//ComPtr<ID3D12Resource> transformationMatrixResourceSprote;
	ComPtr<ID3D12Resource> materialResource;
	ComPtr<ID3D12Resource> indexResourceSprite;

	//Matrix4x4* transformationMatrixDataSprite = nullptr;
	Transform transformSprite{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	D3D12_GPU_DESCRIPTOR_HANDLE instancingSrvHandleGPU;
	ComPtr<ID3D12Resource>instancingResource;

	
	Transform uvTranformSprite{
	 {1.0f,1.0f,1.0f},
	 {0.0f,0.0f,0.0f},
	 {0.0f,0.0f,0.0f}
	};
	Matrix4x4 matrix;
	ModelData model;
	VertexData v;
	const uint32_t kNumInstance = 10;
	ParticleTransform particles_[10];
	uint32_t  tex_;
	uint32_t  tex2_;
	uint32_t instancingIndex_ = 0;
	
	std::random_device seedGenerator;
	
};
