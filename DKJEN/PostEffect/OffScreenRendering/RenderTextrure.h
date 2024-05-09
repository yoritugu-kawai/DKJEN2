#pragma once
#include"../../Utilipy/Pch.h"
#include"../../Math/Math.h"
#include"../../Base/DxCommon.h"

	ComPtr<ID3D12Resource> CreateRenderTextrureResource( uint32_t width, uint32_t height, DXGI_FORMAT format, const Vector4& clearClolor);
