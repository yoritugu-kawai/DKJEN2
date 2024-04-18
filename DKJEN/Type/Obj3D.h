#pragma once
#include"../Base/CreateBufferResource.h"
#include"../Math/Math.h"
#include"../Base/DxCommon.h"
#include"../Base/SpritePSO.h"
#include"../Base/TexturePSO.h"
#include"../Base/LightPSO.h"

#include"../CameraProjection/CameraProjection.h"
#include"../Camera/CameraData.h"
#include"../WorldTransform/WorldTransform.h"
#include"../Utilipy/Pch.h"

#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

struct MaterialData {
	std::string textureFilePath;
};

struct ModelData
{
	std::vector<VertexData>vertices;
	MaterialData material;
};


class Obj3D {
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="tex"></param>
	void Initialize( const std::string& directoryPath,const std::string& filename);
	/// <summary>
	/// 参考数値↓
	/// </summary>
	/// <param name="Vector3 scale={ 0.5f, 0.5f, 0.5f }"></param>
	/// <param name="Vector3 rotate = { 0.0f, 0.0f, 0.0f }"></param>
	/// <param name="Vector3 translate = { 0.0f, 0.0f, 0.0f }"></param>
	/// <param name="Vector4 color = { 1.0f,1.0f,1.0f,1.0f }"></param>
	void Draw( Vector4 Color, CameraData* cameraData, WorldTransform* worldTransform);
	
	ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);

	ModelData NewLoadObjFile(const std::string& directoryPath, const std::string& filename);

	MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);
private:
	ComPtr<ID3D12Resource> vetexResource;
	ComPtr<ID3D12Resource> materialResource;

	ComPtr<ID3D12Resource> lightResource;
	


	D3D12_VERTEX_BUFFER_VIEW vertxBufferView{};
	ModelData modelData;
	Matrix4x4 matrix;
	//TexProeerty  tex_;
	
	Vector3 direction_ = { 0.0f,1.0f,0.0f };

	Vector3 pos;
	uint32_t tex_;
};

