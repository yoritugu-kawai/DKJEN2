#pragma once
#include <string>
#include"../Utilipy/Pch.h"
#include"../Utilipy/rektyk.h"
#include<json.hpp>
#include"../Type/Animation3D.h"

struct LevelData {
	struct ObjectData {
		/// <summary>
		/// ファイル名
		/// </summary>
		std::string fileName;
		Vector3 translation;
		Vector3 rotation;
		Vector3 scaling;
		///コライダー
		std::string colliderType;
		Vector3 center;
		Vector3 size;

	};
	std::vector<ObjectData>objects;
	std::string filePath;

};
class JsonLoad
{
public:
	
	
	void Update();
	void Draw(Camera& camera);
	~JsonLoad();
	void Load(const std::string& directoryPath, const std::string& fileName);
	void RecursiveJson(nlohmann::json& objects);
	void Initialize(const std::string& directoryPath);
private:
	std::map<std::string, Model*> models_;
	std::vector<WorldTransform*> worldTransforms_;
	
	LevelData* levelData;
};

