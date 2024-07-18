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
	levelData = new LevelData;
	RecursiveJson(deserialized["objects"]);
}

void JsonLoad::RecursiveJson(nlohmann::json& objects)
{


	
	

	for (nlohmann::json& object : objects) {
		assert(object.contains("type"));

		std::string type = object["type"].get<std::string>();

		if (type.compare("MESH") == 0) {
			levelData->objects.push_back(LevelData::ObjectData{});
			LevelData::ObjectData& objectData = levelData->objects.back();
			if (object.contains("file_name")) {
				objectData.fileName = object["file_name"];
			}
			nlohmann::json& transform = object["transform"];
			//トランスフォームのパラメータ
			objectData.translation.x = (float)transform["translation"][1];
			objectData.translation.y = (float)transform["translation"][2];
			objectData.translation.z = (float)transform["translation"][0];

			///
			const float DEREES_TO_RADIUS_ = (float)std::numbers::pi / 180.0f;
			objectData.rotation.x = -(float)transform["rotation"][1]*DEREES_TO_RADIUS_;
			objectData.rotation.y = -(float)transform["rotation"][2]*DEREES_TO_RADIUS_;
			objectData.rotation.z = -(float)transform["rotation"][0] * DEREES_TO_RADIUS_;

			//
			objectData.scaling.x = (float)transform["scaling"][1];
			objectData.scaling.y = (float)transform["scaling"][2];
			objectData.scaling.z = (float)transform["scaling"][0];

			//コライダー
			nlohmann::json& collider = object["collider"];

			objectData.colliderType = object["type"];
			//
			objectData.center.x = (float)collider["center"][1];
			objectData.center.y = (float)collider["center"][2];
			objectData.center.z = -(float)collider["center"][0];
			//
			objectData.size.x = (float)collider["size"][1];
			objectData.size.y = (float)collider["size"][2];
			objectData.size.z = (float)collider["size"][0];

			if (object.contains("children")) {
				RecursiveJson(object["children"]);
			}

		}
		
	}

}

void JsonLoad::Initialize(const std::string& directoryPath)
{

	for (auto& objectData : levelData->objects) {
		
		decltype(models_)::iterator it = models_.find(objectData.fileName);

	
		if (it == models_.end()) {
			ModelData* model = nullptr;
			uint32_t modelHandle = ModelManager::GetInstance()->LoadModelFileForLevelData(directoryPath, objectData.fileName);
			model = Model::Create(modelHandle);
			models_[objectData.fileName] = model;
		}

		
		WorldTransform* worldTransform = new WorldTransform();

		worldTransform->Create();
		worldTransform->SetTranslate(objectData.translation);
		worldTransform->SetRotate(objectData.rotation);
		worldTransform->SetScale( objectData.scaling);



		worldTransforms_.push_back(worldTransform);
	}
}


void JsonLoad::Update() {
	//ワールドトランスフォームの更新
	for (WorldTransform* object : worldTransforms_) {
		object->Update();
	}

}

void JsonLoad::Draw(Camera& camera) {
	uint32_t count = 0;
	for (auto& objectData : levelData->objects) {
		//ファイル名から登録済みモデルを検索
		Model* model = nullptr;
		decltype(models_)::iterator it = models_.find(objectData.fileName);
		//見つかったらmodelに入れる
		if (it != models_.end()) {
			model = it->second;
		}

		model->Draw(*worldTransforms_[count], camera);

		//数を増やしていく
		count++;
	}

}



JsonLoad::~JsonLoad() {

	for (auto& pair : models_) {
		delete pair.second;
	}
	models_.clear();

	for (WorldTransform* object : worldTransforms_) {
		delete object;
	}
	worldTransforms_.clear();

	delete levelData;
}