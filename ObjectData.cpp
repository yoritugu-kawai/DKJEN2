#include "ObjectData.h"

void ObjectData::Initialize()
{
	object_= make_unique<Obj3D>();
	
	worldTransform_= make_unique<WorldTransform>();
	worldTransform_->Create();
	
	center;
	size;
}

void ObjectData::ObjectInitialize(ModelData modelData)
{
	object_->Initialize(modelData);
}
