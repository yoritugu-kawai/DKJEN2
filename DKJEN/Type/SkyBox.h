#pragma once
#include"DKJEN/Math/Math.h"
#include"../Base/CreateBufferResource.h"
#include"../Math/Math.h"
#include"../Base/DxCommon.h"

#include"../Base/SkyBoxPSO.h"

#include"../CameraProjection/CameraProjection.h"
#include"../Camera/CameraData.h"
#include"../WorldTransform/WorldTransform.h"
#include"../Utilipy/Pch.h"


#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include"Animation3D.h"


struct SkyBoxMaterial {
	Vector4 color;
	Matrix4x4 uvTransform;
};

enum VERTEX_POSITION {
	TOP_RIGHT_BACK,

	TOP_RIGHT_FRONT,

	BOTTOM_RIGHT_BACK,
	
	BOTTOM_RIGHT_FRONT,
};
class SkyBox
{
public:
	void Initialize(uint32_t textureHandle);
	void Draw(CameraData* cameraData, WorldTransform* worldTransform);

private:
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSphere_;

	ComPtr<ID3D12Resource> vertexResource_ = nullptr;
	VertexData* vertexData_ = nullptr;
	const int32_t  SURFACE_VERTEX_ = 6;
	uint32_t SURFACE_AMOUNT = 6;


	ComPtr<ID3D12Resource> indexResource_ = nullptr;

	D3D12_INDEX_BUFFER_VIEW indexBufferView_{};

	uint32_t* indexData_ = nullptr;

	ComPtr<ID3D12Resource> materialResource_ = nullptr;
	SkyBoxMaterial* materialData_ = nullptr;


	uint32_t textureHandle_ = 0;

};
