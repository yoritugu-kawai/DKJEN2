#pragma once

#include"../Base/CreateBufferResource.h"
#include"../Math/Math.h"
#include"../Base/DxCommon.h"
//#include"../Base/SpritePSO.h"
//#include"../Base/TexturePSO.h"
#include"../Base/LightPSO.h"

#include"../CameraProjection/CameraProjection.h"
#include"../Camera/CameraData.h"
#include"../WorldTransform/WorldTransform.h"
#include"../Utilipy/Pch.h"
//#include"../Skinning/Animation/Animation.h"
#include"../Utilipy/jjj.h"
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

struct  Node
{
	QuaternionTransform transform;
	Matrix4x4 localMatrix;
	std::string name;
	std::vector<Node> chidren;
};

struct MaterialData {
	std::string textureFilePath;
};
struct VetexWeinghtData {
	float weight;
	uint32_t vertexIndex;
};
struct JointWeightData
{
	Matrix4x4 inversBindPoseMatrix;
	std::vector<VetexWeinghtData> vertexWeights;

};
struct ModelData
{
	std::map<std::string, JointWeightData> skinClusterData;
	std::vector<VertexData>vertices;
	std::vector<uint32_t>indices;
	MaterialData material;
	Node rootNode;
	uint32_t tex;
};


class Obj3D {
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="tex"></param>
	void Initialize(ModelData modelData_);
	/// <summary>
	/// 参考数値↓
	/// </summary>
	/// <param name="Vector3 scale={ 0.5f, 0.5f, 0.5f }"></param>
	/// <param name="Vector3 rotate = { 0.0f, 0.0f, 0.0f }"></param>
	/// <param name="Vector3 translate = { 0.0f, 0.0f, 0.0f }"></param>
	/// <param name="Vector4 color = { 1.0f,1.0f,1.0f,1.0f }"></param>
	void Draw( Vector4 Color, CameraData* cameraData, WorldTransform* worldTransform, SkinCluster& skinCluster);
	
	/*ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);

	*/
	ModelData GetModelData() {return modelData_;}
	//ModelData NewLoadObjFile(const std::string& directoryPath, const std::string& filename);
	//Node ReadNode(aiNode* node);
	//アニメーション
	
private:
	ComPtr<ID3D12Resource> vetexResource;
	ComPtr<ID3D12Resource> materialResource;

	ComPtr<ID3D12Resource> lightResource;
	ComPtr<ID3D12Resource> indexResource;


	D3D12_VERTEX_BUFFER_VIEW vertxBufferView{};
	D3D12_INDEX_BUFFER_VIEW indexBufferViewSprite;
	ModelData modelData_;
	Matrix4x4 matrix;
	//TexProeerty  tex_;
	
	Vector3 direction_ = { 0.0f,1.0f,0.0f };

	Vector3 pos;
	
	
};

