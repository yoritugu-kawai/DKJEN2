#include "RenderTextrure.h"

void RenderTextrure::RTV()
{
    const Vector4 kRenderTargetClearValue{ 1.0f,0.0f,0.0f,1.0f };
    //auto renderTextureResource = CreateRenderTextrureResource();
}

ComPtr<ID3D12Resource> RenderTextrure::CreateRenderTextrureResource(uint32_t width, uint32_t height, DXGI_FORMAT format, const Vector4& clearClolor)
{
    ID3D12Device* device = DxCommon::GetInstance()->GetDevice();
    //頂点
    D3D12_RESOURCE_DESC resourceDesc{};
    ComPtr<ID3D12Resource> resource;
    resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
    D3D12_HEAP_PROPERTIES heapProperies{};
    heapProperies.Type = D3D12_HEAP_TYPE_DEFAULT;
    D3D12_CLEAR_VALUE clearValue;
    clearValue.Format = format;
    clearValue.Color[0] = clearClolor.x;
    clearValue.Color[1] = clearClolor.y;
    clearValue.Color[2] = clearClolor.z;
    clearValue.Color[3] = clearClolor.w;

    device->CreateCommittedResource(
        &heapProperies,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_RENDER_TARGET,
        &clearValue,
        IID_PPV_ARGS(&resource));

    return resource;
}
