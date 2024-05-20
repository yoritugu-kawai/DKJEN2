#include "WorldTransform.h"

void WorldTransform::Create()
{
	matWorld_= MakeIdentity4x4();
	buffer_ = CreateBufferResource(sizeof(TransformationMatrix));
}

void WorldTransform::UpdateMatrix(CameraData* cameraData, Matrix4x4 mtrix)
{
	matWorld_ = MakeAffineMatrix(scale_, rotate_, translate_);
	
	//view変換
	Matrix4x4 vP = Multiply(cameraData->GetView(), cameraData->GetProjection());
	matWorld_ = Multiply(matWorld_, vP);

	buffer_.Get()->Map(0, nullptr, reinterpret_cast<void**>(&data_));
	data_->World = Multiply(mtrix, matWorld_);
	data_->WVP = Multiply(mtrix, matWorld_);

}
