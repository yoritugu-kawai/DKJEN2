#pragma once
#include"../../Utilipy/Pch.h"
#include"../../Math/Math.h"
class RenderTextrure
{
public:
	void Initialize();
	ComPtr<ID3D12Resource> CreateRenderTextrureResource(ComPtr<ID3D12Device> device,uint32_t width ,uint32_t height, DXGI_FORMAT format ,const Vector4& clearClolor);
private:

};