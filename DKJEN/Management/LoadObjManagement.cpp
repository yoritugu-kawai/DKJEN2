#include "LoadObjManagement.h"
LoadObjManagement* LoadObjManagement::GetInstance()
{
	static LoadObjManagement instance;

	return &instance;
}
ModelData LoadObjManagement::NewLoadObjFile(const std::string& directoryPath, const std::string& filename)
{
	uint32_t tex_=LoadObjManagement::GetInstance()->tex_;
	ModelData modelData = {};
	Assimp::Importer importer;
	std::string file = directoryPath + "/" + filename;
	const aiScene* scene = importer.ReadFile(file.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs);
	assert(scene->HasMeshes());
	//Node
	modelData.rootNode = ReadNode(scene->mRootNode);

	for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
		aiMesh* mesh = scene->mMeshes[meshIndex];
		assert(mesh->HasNormals());
		assert(mesh->HasTextureCoords(0));

		for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex) {
			aiFace& face = mesh->mFaces[faceIndex];
			assert(face.mNumIndices == 3);

			for (uint32_t element = 0; element < face.mNumIndices; ++element) {
				uint32_t vertexIndex = face.mIndices[element];
				aiVector3D& position = mesh->mVertices[vertexIndex];
				aiVector3D& normal = mesh->mNormals[vertexIndex];
				aiVector3D& texcoord = mesh->mTextureCoords[0][vertexIndex];
				VertexData vertex;
				vertex.position = { position.x,position.y,position.z,1.0f };
				vertex.normal = { normal.x ,normal.y,normal.z };
				vertex.texcoord = { texcoord.x,texcoord.y };
				vertex.position.x *= -1.0f;
				vertex.normal.x *= -1.0f;
				modelData.vertices.push_back(vertex);

				for (uint32_t materialIndex = 0; materialIndex < scene->mNumMaterials; ++materialIndex) {
					aiMaterial* material = scene->mMaterials[materialIndex];
					if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
						aiString textureFilePath;
						material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);
						modelData.material.textureFilePath = directoryPath + "/" + textureFilePath.C_Str();
					}
				}
			}
		}
	}
	tex_ = TexManager::LoadTexture(modelData.material.textureFilePath);
	return modelData;
	LoadObjManagement::GetInstance()->tex_ = tex_;
}

MaterialData LoadObjManagement::LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename)
{
	MaterialData materialData;
	std::string line;
	std::ifstream file(directoryPath + "/" + filename);
	assert(file.is_open());
	while (std::getline(file, line))
	{
		std::string identifier;
		std::istringstream s(line);
		s >> identifier;

		if (identifier == "map_Kd")
		{
			std::string texfilename;
			s >> texfilename;
			materialData.textureFilePath = directoryPath + "/" + texfilename;

		}

	}

	return materialData;
}

Node LoadObjManagement::ReadNode(aiNode* node)
{
	Node result;
	aiMatrix4x4 aiLocalMatrix = node->mTransformation;
	aiLocalMatrix.Transpose();
	result.localMatrix.m[0][0] = aiLocalMatrix[0][0];

	result.name = node->mName.C_Str();
	result.chidren.resize(node->mNumChildren);
	for (uint32_t childIndex = 0; childIndex < node->mNumChildren; ++childIndex) {
		result.chidren[childIndex] = ReadNode(node->mChildren[childIndex]);
	}

	return result;
}

//Animation LoadObjManagement::LoadAnimationFile(const std::string& directoryPath, const std::string& filename)
//{
//	float animaionTime = 0.0f;
//
//	ModelData modelData;
//	Animation animation;
//
//	Assimp::Importer importer;
//	std::string filePath = directoryPath + "/" + filename;
//	const aiScene* scene = importer.ReadFile(filePath.c_str(), 0);
//	assert(scene->mNumAnimations != 0);
//	aiAnimation* animationAssimp = scene->mAnimations[0];
//	animation.duration = float(animationAssimp->mDuration / animationAssimp->mTicksPerSecond);
//	//
//	animaionTime += 1.0f / 60.0f;
//	animaionTime = std::fmod(animaionTime, animation.duration);
//	NodeAnimation& rootNodeAnimation = animation.nodeAnimations[modelData.rootNode.name];
//	Vector3 translate = Calculatevalue(rootNodeAnimation.translate.keyframes, animaionTime);
//	Quaternion rotate = QCalculatevalue(rootNodeAnimation.rotate.keyframes, animaionTime);
//	Vector3 scale = Calculatevalue(rootNodeAnimation.scale.keyframes, animaionTime);
//	Matrix4x4 localMtrix = MakeAffineMatrix(scale, rotate, translate);
//
//
//	for (uint32_t channelIndex = 0; channelIndex < animationAssimp->mNumChannels; ++channelIndex) {
//		aiNodeAnim* nodeAimationAssimp = animationAssimp->mChannels[channelIndex];
//		NodeAnimation& nodeAnimation = animation.nodeAnimations[nodeAimationAssimp->mNodeName.C_Str()];
//
//		for (uint32_t keyIndex = 0; keyIndex < nodeAimationAssimp->mNumPositionKeys; ++keyIndex) {
//			aiVectorKey& keyAssimp = nodeAimationAssimp->mPositionKeys[keyIndex];
//			KeyframeVector3 keyframe;
//			keyframe.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);
//			keyframe.value = { -keyAssimp.mValue.x,keyAssimp.mValue.y,keyAssimp.mValue.z };
//			nodeAnimation.translate.keyframes.push_back(keyframe);
//		}
//		for (uint32_t keyIndex = 0; keyIndex < nodeAimationAssimp->mNumRotationKeys; ++keyIndex)
//		{
//			aiQuatKey& keyAssimp = nodeAimationAssimp->mRotationKeys[keyIndex];
//			KeyframeQuaternion keyFlame;
//			keyFlame.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);
//			keyFlame.value = { keyAssimp.mValue.x,-keyAssimp.mValue.y,-keyAssimp.mValue.z,keyAssimp.mValue.w };
//			nodeAnimation.rotate.keyframes.push_back(keyFlame);
//		}
//
//		for (uint32_t keyIndex = 0; keyIndex < nodeAimationAssimp->mNumScalingKeys; ++keyIndex)
//		{
//			aiVectorKey keyAssimp = nodeAimationAssimp->mScalingKeys[keyIndex];
//			KeyframeVector3 keyFlame;
//			keyFlame.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);
//			keyFlame.value = { keyAssimp.mValue.x,keyAssimp.mValue.y,keyAssimp.mValue.z, };
//			nodeAnimation.scale.keyframes.push_back(keyFlame);
//		}
//
//
//	}
//
//
//	return animation;
//}
//
//Vector3 LoadObjManagement::Calculatevalue(const std::vector<KeyframeVector3>& keyframes, float time)
//{
//	assert(!keyframes.empty());
//	if (keyframes.size() == 1 || time <= keyframes[0].time) {
//		return keyframes[0].value;
//	}
//	for (size_t index = 0; index < keyframes.size() - 1; ++index) {
//		size_t nextIndex = index + 1;
//		if (keyframes[index].time <= time && time <= keyframes[nextIndex].time) {
//			float t = (time - keyframes[index].time) / (keyframes[nextIndex].value, t);
//			return Lerp(keyframes[index].value, keyframes[nextIndex].value, t);
//		}
//	}
//	return (*keyframes.rbegin()).value;
//}
//Quaternion LoadObjManagement::QCalculatevalue(const std::vector<KeyframeQuaternion>& keyframes, float time)
//{
//	assert(!keyframes.empty());
//	if (keyframes.size() == 1 || time <= keyframes[0].time) {
//		return keyframes[0].value;
//	}
//	for (size_t index = 0; index < keyframes.size() - 1; ++index) {
//		size_t nextIndex = index + 1;
//		if (keyframes[index].time <= time && time <= keyframes[nextIndex].time) {
//			float t = (time - keyframes[index].time) / (keyframes[nextIndex].value, t);
//			return Slerp(keyframes[index].value, keyframes[nextIndex].value, t);
//		}
//	}
//	return (*keyframes.rbegin()).value;
//}
