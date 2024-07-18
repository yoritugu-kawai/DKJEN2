#pragma once
#include <string>
#include"../Utilipy/Pch.h"
#include<json.hpp>


class JsonLoad
{
public:
	JsonLoad();
	~JsonLoad();
	void Load();
	void RecursiveJson(nlohmann::json& objects);
private:
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
	LevelData* levelData;
};

