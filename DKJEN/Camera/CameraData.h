#pragma once
#include"../Base/TexManager.h"
#include"../CameraProjection/CameraProjection.h"
class CameraData
{
public:
	
	void Create();
	void Update();
	
#pragma region Get
	Matrix4x4 GetView() { return view_; }
	Matrix4x4 GetProjection() {return projection_;}
	Vector3 GetRotate() { return rotate_; }
	Vector3 GetTranslate() {return translate_;}
	ID3D12Resource* GetColl() {return buffer_.Get();}
#pragma endregion

#pragma region Set
	void SetView(Matrix4x4 view) { view_ = view; }
	void SetProjection(Matrix4x4 projection) { projection_ = projection; }
	void SetRotate(Vector3 rotate) { rotate_ = rotate; }
	void SetTranslate(Vector3 translate) { translate_ = translate; }
#pragma endregion


	ID3D12Resource* CreateBufferResource(size_t sizeInbyte);

private:
	Matrix4x4 view_;
	Matrix4x4 projection_;
	Vector3 rotate_;
	Vector3 translate_;
	ComPtr<ID3D12Resource> buffer_ = nullptr;
	CameraCBuffer* data_ = nullptr;
	float aspectRiot_ = 1280.0f / 720.0f;
	float fov_ = 0.45f;

	float nearClip_ = 0.1f;
	float farClip_ = 1000.0f;
};