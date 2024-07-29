#include "JsonLoad.h"

void JsonLoad::Load(const std::string& directoryPath, const std::string& fileName)
{
	const std::string fullpath = directoryPath + fileName;

	std::ifstream file;

	file.open(fullpath);
	if (file.fail()) {
		assert(0);
	}

	nlohmann::json deserialized;

	file >> deserialized;

	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());

	std::string name = deserialized["name"].get<std::string>();
	assert(name.compare("scene") == 0);

	RecursiveJson(deserialized["objects"]);
}

void JsonLoad::RecursiveJson(nlohmann::json& objects)
{
	for (nlohmann::json& object : objects) {
		assert(object.contains("type"));

		std::string objectName = object["name"].get<std::string>();
		std::string type = object["type"].get<std::string>();
		ObjectData objectData;


		objectData.object_ = make_shared<Obj3D>();
		objectData.worldTransform_ = make_shared<WorldTransform>();

		objectData.worldTransform_->Create();

		if (type.compare("MESH") == 0) {
			if (object.contains("file_name")) {
				objectData.fileName = object["file_name"];
				ModelData boxData_ = LoadObjManagement::NewLoadObjFile("resource/",objectData.fileName);
				objectData.object_->Initialize(boxData_);
			}
			nlohmann::json& transform = object["transform"];
			//トランスフォームのパラメータ
			Transform transformEular;
			//tを入れる
			transformEular.translate.x = (float)transform["translation"][0];
			transformEular.translate.y = (float)transform["translation"][2];
			transformEular.translate.z = (float)transform["translation"][1];

			//rを入れる
			const float DEREES_TO_RADIUS_ = (float)std::numbers::pi / 180.0f;
			transformEular.rotate.x = -(float)transform["rotation"][0]*DEREES_TO_RADIUS_;
			transformEular.rotate.y = -(float)transform["rotation"][2]*DEREES_TO_RADIUS_;
			transformEular.rotate.z = -(float)transform["rotation"][1]*DEREES_TO_RADIUS_;

			//sを入れる
			transformEular.scale.x = (float)transform["scaling"][0];
			transformEular.scale.y = (float)transform["scaling"][2];
			transformEular.scale.z = (float)transform["scaling"][1];

			//srtを入れる
			objectData.worldTransform_->SetScale(transformEular.scale);
			objectData.worldTransform_->SetRotate(transformEular.rotate);
			objectData.worldTransform_->SetTranslate(transformEular.translate);

			models_[objectName] = move(objectData);


		}

	}

}

void JsonLoad::Initialize(const std::string& directoryPath)
{

}


void JsonLoad::Update(CameraData* cameraData) {
	//ワールドトランスフォームの更新
	for (auto& object : models_) {
		auto& it = object.second;
		it.worldTransform_->UpdateMatrix(cameraData);
	}

}

void JsonLoad::Draw(CameraData* cameraData) {
	for (auto& object : models_) {
		auto& it = object.second;
		it.object_->Draw({1,1,1,1}, cameraData, it.worldTransform_.get());
	}

}

