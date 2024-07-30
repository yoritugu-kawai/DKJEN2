#include "Obj3D.h"

void Obj3D::Initialize(ModelData modelData)
{
	
	modelData_ = modelData;/*NewLoadObjFile( directoryPath,filename);*/

	vetexResource = CreateBufferResource(sizeof(VertexData) * modelData_.vertices.size());
	materialResource = CreateBufferResource(sizeof(Vector4));
	
	lightResource = CreateBufferResource(sizeof(DirectionalLight));
	indexResource = CreateBufferResource(sizeof(uint32_t) * modelData_.indices.size());
	
	vertxBufferView.BufferLocation = vetexResource.Get()->GetGPUVirtualAddress();
	vertxBufferView.SizeInBytes = UINT(sizeof(VertexData) * modelData_.vertices.size());
	vertxBufferView.StrideInBytes = sizeof(VertexData);

	indexBufferViewSprite.BufferLocation = indexResource->GetGPUVirtualAddress();
	indexBufferViewSprite.SizeInBytes = sizeof(uint32_t) * modelData_.indices.size();
	indexBufferViewSprite.Format = DXGI_FORMAT_R32_UINT;
    matrix = MakeIdentity4x4();

	pos = { 0.0f,0.0f,5.0f };
	
}

void Obj3D::Draw( Vector4 Color,CameraData*cameraData, WorldTransform* worldTransform)
{
	
	
	
	//
	VertexData* vertexData = nullptr;
	Vector4* materialData = nullptr;
	TransformationMatrix* matrixData = nullptr;
	DirectionalLight* lightData = nullptr;
	uint32_t* indexData = nullptr;

	vetexResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	materialResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&materialData));	
	lightResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&lightData));
	indexResource->Map(0, nullptr, reinterpret_cast<void**>(&indexData));
	std::memcpy(vertexData, modelData_.vertices.data(), sizeof(VertexData)*modelData_.vertices.size());
	std::memcpy(indexData, modelData_.indices.data(), sizeof(uint32_t) * modelData_.indices.size());
	//
	// 
	Matrix4x4 ProjectionMatrix = MakePerspectiveFovMatrix(0.45f, float(1280.0f / 720.0f), 0.1f, 100.0f);

	Matrix4x4 CameraMatrix = MakeIdentity4x4();

	*materialData = Color;
	//lightData->direction = { 0.0f,1.0f,0.0f };
	lightData->color = { 1.0f,1.0f,1.0f,1.0f };
	lightData->intensity = 1.0f;
	/*ImGui::Begin("direction");
	ImGui::SliderFloat3("t", &direction_.x, -1.0f, 1.0f);
	ImGui::End();*/
	lightData->direction = direction_;
	
	//
	ID3D12GraphicsCommandList* commandList = DxCommon::GetInstance()->GetCommandList();
	PSOProperty pso_ = LightPSO::GetInstance()->GetPSO().Texture;
	commandList->SetGraphicsRootSignature(pso_.rootSignature);
	commandList->SetPipelineState(pso_.GraphicsPipelineState);//


	commandList->IASetVertexBuffers(0, 1, &vertxBufferView);
	commandList->IASetIndexBuffer(&indexBufferViewSprite);

	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	commandList->SetGraphicsRootConstantBufferView(0, materialResource.Get()->GetGPUVirtualAddress());
	commandList->SetGraphicsRootConstantBufferView(1, worldTransform->GetColl()->GetGPUVirtualAddress());
	commandList->SetGraphicsRootConstantBufferView(3, lightResource.Get()->GetGPUVirtualAddress());
	commandList->SetGraphicsRootConstantBufferView(4, cameraData->GetColl()->GetGPUVirtualAddress());

	DescriptorManagement::rootParamerterCommand(2, modelData_.tex);
	commandList->DrawIndexedInstanced(UINT(modelData_.indices.size()), 1, 0, 0, 0);
	
}

