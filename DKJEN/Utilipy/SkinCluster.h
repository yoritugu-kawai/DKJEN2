#pragma once
#include"AdditionInclude.h"
struct WellForGPU {

	Matrix4x4 skeletonSpaceMatrix;

	Matrix4x4 skeletonSpaceIncerseTransposeMatrix;
};
const uint32_t NUM_MAX_INFLUENCE = 4;
struct VertexInfluence {
	std::array<float, NUM_MAX_INFLUENCE> weights;
	std::array<int32_t, NUM_MAX_INFLUENCE> jointIndices;
};
struct SkinCluster {

	std::vector<Matrix4x4> inverseBindPoseMatrices;
	ComPtr<ID3D12Resource> influenceResource;
	D3D12_VERTEX_BUFFER_VIEW influenceBufferView;
	std::span<VertexInfluence>mappedInfluence;

	ComPtr<ID3D12Resource>paletteResource;
	std::span<WellForGPU> mappedPalette;
	std::pair<D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_GPU_DESCRIPTOR_HANDLE> paletteSrvHandle;


};
