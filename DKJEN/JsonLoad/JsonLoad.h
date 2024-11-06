#pragma once
#include <string>
#include"../Utilipy/AdditionInclude.h"
#include"../Utilipy/D3DResourceLeaker.h"
#include<json.hpp>
#include"../Type/Animation3D.h"
#include"../../Type/Obj3D.h"
#include"../../Management/LoadObjManagement.h"
#include"DKJEN/Collder/CollisionManager.h"
#include"ObjectData.h"

//#include"DKJEN/Collision/ABB/ABB.h"


struct LevelData {

	unique_ptr<ObjectData>objects;
	std::string filePath;

};
class JsonLoad :public Collider
{
public:

	
	void Update(CameraData* cameraData);
	void Draw(CameraData* cameraData);
	//~JsonLoad();
	void Load(const std::string& directoryPath, const std::string& fileName);
	void RecursiveJson(nlohmann::json& objects);
	const std::map<std::string, ObjectData*>& GetObjects() const { return models_; }
	void SetRotate(Vector3 rotate) { rotate_ = rotate; }
private:
	//std::unordered_map<std::string, ABB> models_;
	std::map<std::string,ObjectData*> models_;
	Vector3 rotate_;
	

};

