#include "RenderTextrure.h"

void RenderTextrure::RTV()
{
    D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = DxCommon::GetInstance()->rtvDescGet();
    //RTV
    ID3D12Device* device = DxCommon::GetInstance()->GetDevice();
    const Vector4 kRenderTargetClearValue{ 1.0f,0.0f,0.0f,1.0f };
    auto renderTextureResource = CreateRenderTextrureResource(WinApp::GetInstance()->Width(), WinApp::GetInstance()->Height(),DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,);
    device->CreateRenderTargetView(renderTextureResource.Get(),&rtvDesc,);
    //SRV
    D3D12_SHADER_RESOURCE_VIEW_DESC renderTextureSrvDesc{};
    renderTextureSrvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    renderTextureSrvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    renderTextureSrvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    renderTextureSrvDesc.Texture2D.MipLevels = 1;
    device->CreateShaderResourceView(renderTextureResource.Get(), &renderTextureSrvDesc, );
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
