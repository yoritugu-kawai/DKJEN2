#pragma once
#include"../../../DKJEN/Base/DxCommon.h"
struct SImageData {
    uint32_t index;
    ComPtr<ID3D12Resource> resource;
    Vector2 size;

};
class ImageData
{
public:
    ImageData(string Path, SImageData data);
    ~ImageData() {};
    uint32_t GetImageIndex() { return imageData.index; }
    Vector2 GetImageSize() { return imageData.size; }
    ComPtr<ID3D12Resource>GetResource() { return imageData.resource; }

private:
    SImageData imageData;
    string filePath;
};