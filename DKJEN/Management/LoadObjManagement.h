#pragma once
#include"../Type/Obj3D.h"
#include"../Skinning/Animation/Animation.h"
#include"../Utilipy/Pch.h"
#include"../Utilipy/Sc.h"
struct Joint {
	QuaternionTransform transform;
	Matrix4x4 localMatrix;
	Matrix4x4 skeletonSpaceMatrix;
	std::string name;
	std::vector<int32_t> children;
	int32_t index;
	optional<int32_t> parent;

};

struct Skeleton
{
	int32_t root;
	map<std::string, int32_t> jointMap;
	std::vector<Joint> joints;

};

class LoadObjManagement
{
public:
	static LoadObjManagement* GetInstance();
	static ModelData NewLoadObjFile(const std::string& directoryPath, const std::string& filename);
	static MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);
	static Node ReadNode(aiNode* node);
	static Animation LoadAnimationFile(const std::string& directoryPath, const std::string& filename);
	static Vector3 Calculatevalue(const std::vector<KeyframeVector3>& keyframes, float time);
	static Quaternion QCalculatevalue(const std::vector<KeyframeQuaternion>& keyframes, float time);
	//static Matrix4x4 AnimationUpdate(ModelData modelData, Animation animation);
	/*static Skeleton CreateSkeleton(const Node& rootNode);
	static int32_t CreateJoint(const Node& node, const optional<int32_t>& parent, vector<Joint>& joints);
	static void Update(Skeleton& skeleton);
	static void ApplyAnimation(Skeleton& skeleton, const Animation& animation, float animatiionTime);
	static SkinCluster CreateSkinCluster(const Skeleton& skeleton, const ModelData& modelData);
	static void SkinUpdate(SkinCluster& skinCluster, const Skeleton& skeleton);*/

private:
	float animaionTime = 0.0f;
	TransformationMatrix* data_;

	Animation animation;
	std::vector<Matrix4x4> inverseBindPoseMatrices;


	ComPtr<ID3D12Resource> influenceResource_;
	D3D12_VERTEX_BUFFER_VIEW influenceBufferView_;
	std::span<VertexInfluence>mappedInfluence_;

	ComPtr<ID3D12Resource>paletteResource_;
	std::span<WellForGPU> mappedPalette_;
	std::pair<D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_GPU_DESCRIPTOR_HANDLE> paletteSrvHandle_;
	uint32_t srvIndex_;


};
