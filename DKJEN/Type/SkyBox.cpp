#include "SkyBox.h"

void SkyBox::Initialize(uint32_t textureHandle)
{

	SURFACE_AMOUNT = 6;

	vertexResource_ = CreateBufferResource(sizeof(VertexData) * SURFACE_VERTEX_ * SURFACE_AMOUNT);


	vertexBufferViewSphere_.BufferLocation = vertexResource_->GetGPUVirtualAddress();

	vertexBufferViewSphere_.SizeInBytes = sizeof(VertexData) * SURFACE_VERTEX_ * SURFACE_AMOUNT;

	vertexBufferViewSphere_.StrideInBytes = sizeof(VertexData);


	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));



	vertexData_[0].position = { 1.0f,1.0f,1.0f,1.0f };
	vertexData_[1].position = { 1.0f,1.0f,-1.0f,1.0f };
	vertexData_[2].position = { 1.0f,-1.0f,1.0f,1.0f };



	vertexData_[3].position = { 1.0f,-1.0f,1.0f,1.0f };
	vertexData_[4].position = { 1.0f,1.0f,-1.0f,1.0f };
	vertexData_[5].position = { 1.0f,-1.0f,-1.0f,1.0f };




	vertexData_[6].position = { -1.0f,1.0f,-1.0f,1.0f };
	vertexData_[7].position = { -1.0f,1.0f,1.0f,1.0f };
	vertexData_[8].position = { -1.0f,-1.0f,-1.0f,1.0f };

	vertexData_[9].position = { -1.0f,-1.0f,1.0f,1.0f };
	vertexData_[10].position = { -1.0f,-1.0f,-1.0f,1.0f };
	vertexData_[11].position = { -1.0f,1.0f,1.0f,1.0f };




	vertexData_[12].position = { -1.0f,1.0f,1.0f,1.0f };
	vertexData_[13].position = { 1.0f,1.0f,1.0f,1.0f };
	vertexData_[14].position = { -1.0f,-1.0f,1.0f,1.0f };

	vertexData_[15].position = { 1.0f,-1.0f,1.0f,1.0f };
	vertexData_[16].position = { -1.0f,-1.0f,1.0f,1.0f };
	vertexData_[17].position = { 1.0f,1.0f,1.0f,1.0f };





	vertexData_[18].position = { 1.0f,1.0f,-1.0f,1.0f };
	vertexData_[19].position = { -1.0f,1.0f,-1.0f,1.0f };
	vertexData_[20].position = { -1.0f,-1.0f,-1.0f,1.0f };



	vertexData_[21].position = { 1.0f,1.0f,-1.0f,1.0f };
	vertexData_[22].position = { -1.0f,-1.0f,-1.0f,1.0f };
	vertexData_[23].position = { 1.0f,-1.0f,-1.0f,1.0f };






	vertexData_[24].position = { 1.0f,1.0f,1.0f,1.0f };
	vertexData_[25].position = { -1.0f,1.0f,1.0f,1.0f };
	vertexData_[26].position = { -1.0f,1.0f,-1.0f,1.0f };



	vertexData_[27].position = { 1.0f,1.0f,1.0f,1.0f };
	vertexData_[28].position = { -1.0f,1.0f,-1.0f,1.0f };
	vertexData_[29].position = { 1.0f,1.0f,-1.0f,1.0f };




	vertexData_[30].position = { -1.0f,-1.0f,1.0f,1.0f };
	vertexData_[31].position = { 1.0f,-1.0f,1.0f,1.0f };
	vertexData_[32].position = { 1.0f,-1.0f,-1.0f,1.0f };



	vertexData_[33].position = { -1.0f,-1.0f,1.0f,1.0f };
	vertexData_[34].position = { 1.0f,-1.0f,-1.0f,1.0f };
	vertexData_[35].position = { -1.0f,-1.0f,-1.0f,1.0f };


	vertexResource_->Unmap(0, nullptr);

	materialResource_ = CreateBufferResource(sizeof(SkyBoxMaterial));

	textureHandle_ = textureHandle;
}

void SkyBox::Draw(CameraData* cameraData, WorldTransform* worldTransform)
{

	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));
	materialData_->color = { 1.0f,1.0f,1.0f,1.0f };
	materialData_->uvTransform = MakeIdentity4x4();
	materialResource_->Unmap(0, nullptr);


	ID3D12GraphicsCommandList* commandList = DxCommon::GetInstance()->GetCommandList();
	PSOProperty pso_ = SkyBoxPSO::GetInstance()->GetPSO().Texture;

	commandList->SetGraphicsRootSignature(pso_.rootSignature);
	commandList->SetPipelineState(pso_.GraphicsPipelineState);

	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	commandList->IASetVertexBuffers(0, 1, &vertexBufferViewSphere_);

	commandList->SetGraphicsRootConstantBufferView(0, worldTransform -> GetColl()->GetGPUVirtualAddress());
	commandList->SetGraphicsRootConstantBufferView(1, cameraData -> GetColl()->GetGPUVirtualAddress());

	if (textureHandle_ != 0) {
		DescriptorManagement::rootParamerterCommand(2, textureHandle_);
	}

	
	commandList->SetGraphicsRootConstantBufferView(3, materialResource_->GetGPUVirtualAddress());

	commandList->DrawInstanced(SURFACE_VERTEX_ * SURFACE_AMOUNT, 1, 0, 0);

}
