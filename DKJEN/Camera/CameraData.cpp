#include "CameraData.h"

void CameraData::Create()
{
	this->view_ = MakeIdentity4x4();
	this->projection_ = MakeIdentity4x4();
	buffer_ = CreateBufferResource(sizeof(CameraMatrixData));
	
}

void CameraData::Update()
{
	Matrix4x4 rx = MakeRotateXMatrix(rotate_.x);
	Matrix4x4 ry = MakeRotateYMatrix(rotate_.y);
	Matrix4x4 rz = MakeRotateZMatrix(rotate_.z);

	Matrix4x4 rxyz = Multiply(rx, Multiply(ry, rz));
	Matrix4x4 t = MakeTranslateMatrix(translate_);

	Matrix4x4 s = MakeScaleMatrix({ 1.0f,1.0f,1.0f });
	Matrix4x4 w = Multiply(s, Multiply(rxyz, t));

	view_ = Multiply(Inverse(rxyz), Inverse(t));
	projection_ = MakePerspectiveFovMatrix(fov_, aspectRiot_, nearClip_, farClip_);
	buffer_.Get()->Map(0, nullptr, reinterpret_cast<void**>(&data_));
	data_->viewMatrix_ = view_;
	data_->projectionMatrix_ = projection_;
	data_->orthographicMatrix_= MakeOrthographicMatrix(0, 0, float(WinApp::GetInstance()->Width()), float(WinApp::GetInstance()->Height()), 0.0f, 100.0f);
	buffer_.Get()->Unmap(0, nullptr);
}

