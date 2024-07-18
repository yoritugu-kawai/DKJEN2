#pragma once
#include <string>
#include"../Utilipy/Pch.h"
#include"../Utilipy/rektyk.h"
#include<json.hpp>
#include"../Type/Animation3D.h"
#include"DKJEN/Type/Obj3D.h"
#include"DKJEN/Management/LoadObjManagement.h"

struct ObjectData {
	/// <summary>
	/// ファイル名
	/// </summary>
	std::string fileName;

	shared_ptr<WorldTransform> worldTransform_;
	shared_ptr<Obj3D>object_;

	///コライダー
	std::string colliderType;
	Vector3 center;
	Vector3 size;

};

struct LevelData {

	std::vector<ObjectData>objects;
	std::string filePath;

};
class JsonLoad
{
public:

	void Initialize(const std::string& directoryPath);
	void Update(CameraData* cameraData);
	void Draw(CameraData* cameraData);
	//~JsonLoad();
	void Load(const std::string& directoryPath, const std::string& fileName);
	void RecursiveJson(nlohmann::json& objects);

private:

	std::map<std::string,ObjectData> models_;
	std::vector<WorldTransform*> worldTransforms_;
	

};

