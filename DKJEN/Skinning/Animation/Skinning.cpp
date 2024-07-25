#include "Skinning.h"

SkinCluster Skinning::CreateSkinCluster(const Skeleton& skeleton, const ModelData& modelData)
{
	SkinCluster skinCluster;
	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();


	DescriptorManagement::GetInstance();
	
	uint32_t index = DescriptorManagement::Allocate();

	skinCluster.paletteResource = CreateBufferResource(sizeof(WellForGPU) * skeleton.joints.size());
	WellForGPU* mappedPalette = nullptr;
	skinCluster.paletteResource->Map(0, nullptr, reinterpret_cast<void**>(&mappedPalette));
	skinCluster.mappedPalette = { mappedPalette,skeleton.joints.size() };
	skinCluster.paletteSrvHandle.first = DescriptorManagement::CPUDescriptorHandle( index);
	skinCluster.paletteSrvHandle.second = DescriptorManagement::GPUDescriptorHandle(index);
	


	D3D12_SHADER_RESOURCE_VIEW_DESC paletteSrvDesc{};
	paletteSrvDesc.Format = DXGI_FORMAT_UNKNOWN;
	paletteSrvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	paletteSrvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	paletteSrvDesc.Buffer.FirstElement = 0;
	paletteSrvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
	paletteSrvDesc.Buffer.NumElements = UINT(skeleton.joints.size());
	paletteSrvDesc.Buffer.StructureByteStride = sizeof(WellForGPU);
	DescriptorManagement::CreateShaderResourceView(index, paletteSrvDesc, skinCluster.paletteResource);
	
	skinCluster.influenceResource = CreateBufferResource(sizeof(VertexInfluence) * modelData.vertices.size());
	VertexInfluence* mappedInfluence = nullptr;
	skinCluster.influenceResource->Map(0, nullptr, reinterpret_cast<void**>(&mappedInfluence));
	std::memset(mappedInfluence, 0, sizeof(VertexInfluence) * modelData.vertices.size());
	skinCluster.mappedInfluence = { mappedInfluence,modelData.vertices.size() };

	skinCluster.influenceBufferView.BufferLocation = skinCluster.influenceResource->GetGPUVirtualAddress();
	skinCluster.influenceBufferView.SizeInBytes = UINT(sizeof(VertexInfluence) * modelData.vertices.size());
	skinCluster.influenceBufferView.StrideInBytes = sizeof(VertexInfluence);

	skinCluster.inverseBindPoseMatrices.resize(skeleton.joints.size());
	std::generate(skinCluster.inverseBindPoseMatrices.begin(), skinCluster.inverseBindPoseMatrices.end(), MakeIdentity4x4);


	for (const auto& jointWeight : modelData.skinClusterData) {

		auto it = skeleton.jointMap.find(jointWeight.first);
		if (it == skeleton.jointMap.end()) {

			continue;
		}

		skinCluster.inverseBindPoseMatrices[(*it).second] = jointWeight.second.inverseBindPoseMatrix;
		for (const auto& vertexWeight : jointWeight.second.vertexWeights) {

			auto& currentInfluence = skinCluster.mappedInfluence[vertexWeight.vertexIndex];


			for (uint32_t index = 0; index < NUM_MAX_INFLUENCE; ++index) {

				if (currentInfluence.weights[index] == 0.0f) {
					currentInfluence.weights[index] = vertexWeight.weight;
					currentInfluence.jointIndices[index] = (*it).second;
					break;
				}

			}
		}


	}


	return skinCluster;
}

void Skinning::SkinUpdate(SkinCluster& skinCluster, const Skeleton& skeleton)
{
	
	//skeletonSpacematrixの値が違う件
	for (size_t jointIndex = 0; jointIndex < skeleton.joints.size(); ++jointIndex)
	{
		assert(jointIndex < skinCluster.inverseBindPoseMatrices.size());

		Matrix4x4 inverseBindMatrix = skinCluster.inverseBindPoseMatrices[jointIndex];

		//2番目のSaceMatrixの値が変
		Matrix4x4 skeletonSpaceMatrix = skeleton.joints[jointIndex].skeletonSpaceMatrix;


		skinCluster.mappedPalette[jointIndex].skeletonSpaceMatrix =
			Multiply(skinCluster.inverseBindPoseMatrices[jointIndex],
				skeleton.joints[jointIndex].skeletonSpaceMatrix);

		skinCluster.mappedPalette[jointIndex].skeletonSpaceIncerseTransposeMatrix =
			MakeTransposeMatrix(Inverse(skinCluster.mappedPalette[jointIndex].skeletonSpaceMatrix));

	}
}
