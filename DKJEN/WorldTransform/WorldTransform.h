#pragma once
#include"../Imgui/imguiManager.h"
#include"../Base/CreateBufferResource.h"
#include"../Math/Math.h"
#include"../Base/TexManager.h"
#include"../Camera/CameraData.h"
class WorldTransform
{
public:
	void Create();
	void UpdateMatrix(CameraData*cameraData, Matrix4x4 mtrix);
	
	

#pragma region Get
	Matrix4x4 GetMatWorld_() { return matWorld_; }
	Vector3 GetScale() { return scale_; }
	Vector3 GetRotate() { return rotate_; }
	Vector3 GetTranslate() { return translate_; }
	Vector4 GetColor() {return color_;}
	ID3D12Resource* GetColl() { return buffer_.Get(); }
#pragma endregion

#pragma region Set
	void SetScale(Vector3 scale) { scale_ = scale; }
	void SetRotate(Vector3 rotate) { rotate_ = rotate; }
	void SetTranslate(Vector3 translate) { translate_ = translate; }
	void SetColor(Vector4 color) { color_ = color; }
	void SetDeta(TransformationMatrix* data) { data_ = data; };
#pragma endregion
private:
	Vector3 scale_ = { 1.0f,1.0f,1.0f };
	Vector3 rotate_ = { 0.0f,0.0f,0.0f };
	Vector3 translate_ = {0.0f,0.0f,0.0f};
	Vector4 color_ = { 1,1,1,1 };
	Matrix4x4 matWorld_;
	TransformationMatrix *data_ ;
	ComPtr<ID3D12Resource> buffer_ = nullptr;
};
