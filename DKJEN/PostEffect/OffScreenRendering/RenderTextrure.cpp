#include "RenderTextrure.h"

void RenderTextrure::Initialize()
{
}

ComPtr<ID3D12Resource> RenderTextrure::CreateRenderTextrureResource(ComPtr<ID3D12Device> device, uint32_t width, uint32_t height, DXGI_FORMAT format, const Vector4& clearClolor)
{
    return ComPtr<ID3D12Resource>();
}
