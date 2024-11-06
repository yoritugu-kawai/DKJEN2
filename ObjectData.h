#pragma once
#include <string>
#include<json.hpp>
#include"../../Type/Obj3D.h"
#include"../../Management/LoadObjManagement.h"
#include"DKJEN/Collder/CollisionManager.h"
class ObjectData :public Collider
{
public:
	void Initialize();
	void ObjectInitialize(ModelData modelData);
	
#pragma region Get
	std::string GetFileName() { return fileName_; }
#pragma endregion

#pragma region Set
	void SetFileName(std::string fileName) { fileName_ = fileName; }
	void SetScale(Vector3 scale) { worldTransform_->SetScale(scale); }
	void SetRotate(Vector3 rotate) { worldTransform_->SetScale(rotate); }
	void SetTranslate(Vector3 translate) { worldTransform_->SetScale(translate); }
	void SetColliderType(std::string colliderType) { colliderType_ = colliderType; }

	void SetCenterX(float x) { center.x = x; }
	void SetCenterY(float y) { center.y = y; }
	void SetCenterZ(float z) { center.z = z; }

	void SetizeX(float x) { center.x = x; }
	void SetizeY(float y) { center.y = y; }
	void SetizeZ(float z) { center.z = z; }
#pragma endregion
private:
	/// <summary>
	/// ファイル名
	/// </summary>
	std::string fileName_;

	unique_ptr<WorldTransform> worldTransform_;
	unique_ptr<Obj3D>object_;

	///コライダー
	std::string colliderType_;
	Vector3 center;
	Vector3 size;

};