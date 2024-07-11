#include "PostEffect.h"

void PostEffect::Initialize()
{
	Create();
}

void PostEffect::Call()
{
	ID3D12GraphicsCommandList* commandList = DxCommon::GetInstance()->GetCommandList();
	PSOProperty pso_ = RenderTextrurePSO::GetInstance()->GetPSO().Texture;

	commandList->SetGraphicsRootSignature(pso_.rootSignature);
	commandList->SetPipelineState(pso_.GraphicsPipelineState);//
	DescriptorManagement::rootParamerterCommand(2, srv_);
	commandList->DrawInstanced(3, 1, 0, 0);
}
