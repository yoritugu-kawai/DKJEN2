#include "CameraProjection.h"

void CameraOperation::Initialize()
{
	view = MakeIdentity4x4();

}

void CameraOperation::Update()
{
	Matrix4x4 rx = MakeRotateXMatrix(rotate.x);
	Matrix4x4 ry = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rz = MakeRotateZMatrix(rotate.z);

	Matrix4x4 rxyz = Multiply(rx, Multiply(ry, rz));
	Matrix4x4 t = MakeTranslateMatrix(translate);
	view = Multiply(Inverse(rxyz),Inverse(t));
	projection = MakePerspectiveFovMatrix(fov_, aspectRiot_, nearClip_, farClip_);

}
