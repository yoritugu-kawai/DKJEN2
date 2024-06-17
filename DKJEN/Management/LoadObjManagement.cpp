#include "LoadObjManagement.h"
LoadObjManagement* LoadObjManagement::GetInstance()
{
	static LoadObjManagement instance;

	return &instance;
}
ModelData LoadObjManagement::NewLoadObjFile(const std::string& directoryPath, const std::string& filename)
{

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
		modelData.vertices.resize(mesh->mNumVertices);
		for (uint32_t vertexIndex = 0; vertexIndex < mesh->mNumVertices; ++vertexIndex) {
			aiVector3D& position = mesh->mVertices[vertexIndex];
			aiVector3D& normal = mesh->mNormals[vertexIndex];
			aiVector3D& texcoord = mesh->mTextureCoords[0][vertexIndex];
			//
			modelData.vertices[vertexIndex].position={ -position.x,position.y,position.z,1.0f };
			modelData.vertices[vertexIndex].normal = { -normal.x ,normal.y,normal.z };
			modelData.vertices[vertexIndex].texcoord = { texcoord.x,texcoord.y };
		}
		for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex) {
			aiFace& face = mesh->mFaces[faceIndex];
			assert(face.mNumIndices == 3);

			for (uint32_t element = 0; element < face.mNumIndices; ++element) {
				uint32_t vertexIndex = face.mIndices[element];
				modelData.indices.push_back(vertexIndex);
			}
		}
		for (uint32_t materialIndex = 0; materialIndex < scene->mNumMaterials; ++materialIndex) {
			aiMaterial* material = scene->mMaterials[materialIndex];
			if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
				aiString textureFilePath;
				material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);
				modelData.material.textureFilePath = directoryPath + "/" + textureFilePath.C_Str();
			}
		}

		for (uint32_t boneIndex = 0; boneIndex < mesh->mNumBones;++boneIndex) {
			aiBone* bone = mesh->mBones[boneIndex];
			std::string jointName = bone->mName.C_Str();
			JointWeightData& jointWeightData = modelData.skinClusterData[jointName];

			aiMatrix4x4 bindPosMatrixAssimp = bone->mOffsetMatrix.Inverse();
			aiVector3D scale, translate;
			aiQuaternion rotate;
			bindPosMatrixAssimp.Decompose(scale, rotate, translate);
			Matrix4x4 bindPoseMatrix = MakeAffineMatrix({ scale.x,scale.y,scale.z }, { rotate.x,-rotate.y,rotate.z,rotate.w }, { -translate.x,translate.y,translate.z });
			jointWeightData.inversBindPoseMatrix = Inverse(bindPoseMatrix);

			for (uint32_t weightIndex = 0; weightIndex < bone->mNumWeights; ++weightIndex) {
				jointWeightData.vertexWeights.push_back({bone->mWeights[weightIndex].mWeight, bone->mWeights[weightIndex].mVertexId});
			}

		}
	}
	
	modelData.tex= TexManager::LoadTexture(modelData.material.textureFilePath);
	return modelData;
	
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
	//aiMatrix4x4 aiLocalMatrix = node->mTransformation;
	//aiLocalMatrix.Transpose();
	//result.localMatrix.m[0][0] = aiLocalMatrix[0][0];

	
	aiVector3D scale, tranalte;
	aiQuaternion rotate;
	node->mTransformation.Decompose(scale, rotate, tranalte);
	result.transform.scale = {scale.x,scale .y,scale .z};
	result.transform.rotate = { rotate.x,-rotate.y,-rotate.z,rotate.w};
	result.transform.tranalte = { -tranalte.x,tranalte.y,tranalte.z };

	Matrix4x4 scaleMatrix = MakeTranslateMatrix(result.transform.tranalte);
	Matrix4x4 rotateMatrix = MakeRotateMatrix(result.transform.rotate);
	Matrix4x4 translateMatrix = MakeScaleMatrix(result.transform.scale);


	result.localMatrix = Multiply(scaleMatrix, Multiply(rotateMatrix, translateMatrix));


	result.name = node->mName.C_Str();
	result.chidren.resize(node->mNumChildren);
	for (uint32_t childIndex = 0; childIndex < node->mNumChildren; ++childIndex) {
		result.chidren[childIndex] = ReadNode(node->mChildren[childIndex]);
	}

	return result;
}

Animation LoadObjManagement::LoadAnimationFile(const std::string& directoryPath, const std::string& filename)
{
	
	Animation animation=LoadObjManagement::GetInstance()->animation;
	Assimp::Importer importer;
	std::string filePath = directoryPath + "/" + filename;
	const aiScene* scene = importer.ReadFile(filePath.c_str(), 0);
	assert(scene->mNumAnimations != 0);
	aiAnimation* animationAssimp = scene->mAnimations[0];
	animation.duration = float(animationAssimp->mDuration / animationAssimp->mTicksPerSecond);
	//
	


	for (uint32_t channelIndex = 0; channelIndex < animationAssimp->mNumChannels; ++channelIndex) {
		aiNodeAnim* nodeAimationAssimp = animationAssimp->mChannels[channelIndex];
		NodeAnimation& nodeAnimation = animation.nodeAnimations[nodeAimationAssimp->mNodeName.C_Str()];

		for (uint32_t keyIndex = 0; keyIndex < nodeAimationAssimp->mNumPositionKeys; ++keyIndex) {
			aiVectorKey& keyAssimp = nodeAimationAssimp->mPositionKeys[keyIndex];
			KeyframeVector3 keyframe;
			keyframe.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);
			keyframe.value = { -keyAssimp.mValue.x,keyAssimp.mValue.y,keyAssimp.mValue.z };
			nodeAnimation.translate.keyframes.push_back(keyframe);
		}
		for (uint32_t keyIndex = 0; keyIndex < nodeAimationAssimp->mNumRotationKeys; ++keyIndex)
		{
			aiQuatKey& keyAssimp = nodeAimationAssimp->mRotationKeys[keyIndex];
			KeyframeQuaternion keyFlame;
			keyFlame.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);
			keyFlame.value = { keyAssimp.mValue.x,-keyAssimp.mValue.y,-keyAssimp.mValue.z,keyAssimp.mValue.w };
			nodeAnimation.rotate.keyframes.push_back(keyFlame);
		}

		for (uint32_t keyIndex = 0; keyIndex < nodeAimationAssimp->mNumScalingKeys; ++keyIndex)
		{
			aiVectorKey keyAssimp = nodeAimationAssimp->mScalingKeys[keyIndex];
			KeyframeVector3 keyFlame;
			keyFlame.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);
			keyFlame.value = { keyAssimp.mValue.x,keyAssimp.mValue.y,keyAssimp.mValue.z, };
			nodeAnimation.scale.keyframes.push_back(keyFlame);
		}


	}
	
	 LoadObjManagement::GetInstance()->animation = animation;
												
	return animation;
}

Vector3 LoadObjManagement::Calculatevalue(const std::vector<KeyframeVector3>& keyframes, float time)
{
	assert(!keyframes.empty());
	if (keyframes.size() == 1 || time <= keyframes[0].time) {
		return keyframes[0].value;
	}
	for (size_t index = 0; index < keyframes.size() - 1; ++index) {
		size_t nextIndex = index + 1;
		if (keyframes[index].time <= time && time <= keyframes[nextIndex].time) {
			float t = (time - keyframes[index].time) / (keyframes[nextIndex].time, keyframes[index].time);
			return Lerp(keyframes[index].value, keyframes[nextIndex].value, t);
		}
	}
	return (*keyframes.rbegin()).value;
}
Quaternion LoadObjManagement::QCalculatevalue(const std::vector<KeyframeQuaternion>& keyframes, float time)
{
	assert(!keyframes.empty());
	if (keyframes.size() == 1 || time <= keyframes[0].time) {
		return keyframes[0].value;
	}

	for (size_t index = 0; index < keyframes.size() - 1; ++index) {
		size_t nextIndex = index + 1;
	
		if (keyframes[index].time <= time && time <= keyframes[nextIndex].time) {
			
			float t = (time - keyframes[index].time) / (keyframes[nextIndex].time - keyframes[index].time);
			
			return Slerp(keyframes[index].value, keyframes[nextIndex].value, t);
		}
	}
	
	return (*keyframes.rbegin()).value;
}

Matrix4x4 LoadObjManagement::AnimationUpdate(ModelData modelData,Animation animation)
{
	
	
	float animaionTime = LoadObjManagement::GetInstance()->animaionTime;
	TransformationMatrix* data_=LoadObjManagement::GetInstance()->data_;
	Skeleton skeleton = CreateSkeleton(modelData.rootNode);
	animaionTime += 1.0f / 60.0f;
	animaionTime = std::fmod(animaionTime, animation.duration);
	NodeAnimation& rootNodeAnimation = animation.nodeAnimations[modelData.rootNode.name];
	Vector3 translate = Calculatevalue(rootNodeAnimation.translate.keyframes, animaionTime);
	Quaternion rotate = QCalculatevalue(rootNodeAnimation.rotate.keyframes, animaionTime);
	Vector3 scale = Calculatevalue(rootNodeAnimation.scale.keyframes, animaionTime);
	Matrix4x4 localMtrix = MakeAffineMatrix(scale, rotate, translate);

	/*Matrix4x4 vP = Multiply(cameraData->GetView(), cameraData->GetProjection());

	data_->World = Multiply(localMtrix, Multiply(worldTransform->GetMatWorld_(), vP));
	data_->WVP = Multiply(localMtrix,worldTransform->GetMatWorld_());
	worldTransform->SetDeta(data_);*/
	/*ApplyAnimation(skeleton, animation, animaionTime);
	Update(skeleton);*/

	LoadObjManagement::GetInstance()->animaionTime = animaionTime;
	LoadObjManagement::GetInstance()->data_ = data_;
	return localMtrix;
	
}

Skeleton LoadObjManagement::CreateSkeleton(const Node& rootNode)
{
	Skeleton skeleton;
	skeleton.root = CreateJoint(rootNode, {}, skeleton.joints);

	for (const Joint& joint : skeleton.joints) {
		skeleton.jointMap.emplace(joint.name, joint.index);
	}

	return skeleton;
}

int32_t LoadObjManagement::CreateJoint(const Node& node, const optional<int32_t>& parent, vector<Joint>& joints)
{
	Joint joint;

	joint.name = node.name;
	joint.localMatrix = node.localMatrix;
	joint.skeletonSpaceMatrix = MakeIdentity4x4();
	joint.transform = node.transform;
	joint.index = int32_t(joints.size());
	joint.parent = parent;
	joints.push_back(joint);
	for (const Node& child : node.chidren) {
		int32_t childIndex = CreateJoint(child, joint.index, joints);
		joints[joint.index].children.push_back(childIndex);
	}

	return joint.index;
}

void LoadObjManagement::Update(Skeleton& skeleton)
{


	//skeletonSpacematrixに値が入っていない
	for (Joint joint :skeleton.joints) {

		Vector3 scale = joint.transform.scale;
		Quaternion rotate = joint.transform.rotate;
		Vector3 translate = joint.transform.tranalte;

		Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
		Matrix4x4 rotateMatrix = MakeRotateMatrix(rotate);
		Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

		joint.localMatrix = Multiply(scaleMatrix, Multiply(rotateMatrix, translateMatrix));
		if (joint.parent) {
			//3週目にjoint.localMatrixの値が入らない。nad。
			joint.skeletonSpaceMatrix = Multiply( joint.localMatrix ,skeleton.joints[*joint.parent].skeletonSpaceMatrix);
		}
		else {
			joint.skeletonSpaceMatrix = joint.localMatrix;
			
		}
	}

	//1...else
	//2...parent
	//3...parent
	//4...parent

	//3,4番目値が-infだった
	skeleton.joints;


}

void LoadObjManagement::ApplyAnimation(Skeleton& skeleton, const Animation& animation, float animatiionTime)
{

	for (Joint& joint : skeleton.joints) {
		if (auto it = animation.nodeAnimations.find(joint.name);it !=animation.nodeAnimations.end()) {
			animatiionTime = std::fmod(animatiionTime, animation.duration);
			const NodeAnimation& rootNodeAnimation = (*it).second;
			joint.transform.tranalte=Calculatevalue(rootNodeAnimation.translate.keyframes, animatiionTime);
			joint.transform.rotate = QCalculatevalue(rootNodeAnimation.rotate.keyframes, animatiionTime);
			joint.transform.scale = Calculatevalue(rootNodeAnimation.scale.keyframes, animatiionTime);
	
		}
	}
	
}
SkinCluster  LoadObjManagement::CreateSkinCluster(const Skeleton& skeleton, const ModelData& modelData) {
	SkinCluster skinCluster ;
	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();
	ID3D12DescriptorHeap* srvDescriptorHeap = DxCommon::GetInstance()->GetsrvDescriptorHeap();
	uint32_t descriptorSizeSRV = TexManager::GetInstance()->GetDescriptorSizeSRV();

	skinCluster.paletteResource= CreateBufferResource(sizeof(WellForGPU) * skeleton.joints.size());
	WellForGPU* mappedPalette = nullptr;
	skinCluster.paletteResource->Map(0, nullptr, reinterpret_cast<void**>(&mappedPalette));
	skinCluster.mappedPalette= { mappedPalette,skeleton.joints.size() };
	skinCluster.paletteSrvHandle.first = GetCPUDescriptorHandle(srvDescriptorHeap, descriptorSizeSRV, DescriptorManagement:: GetIndex());
	skinCluster.paletteSrvHandle.second = GetGPUDescriptorHandle(srvDescriptorHeap, descriptorSizeSRV, DescriptorManagement::GetIndex());

	D3D12_SHADER_RESOURCE_VIEW_DESC paletteSrvDesc{};
	paletteSrvDesc.Format = DXGI_FORMAT_UNKNOWN;
	paletteSrvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	paletteSrvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	paletteSrvDesc.Buffer.FirstElement = 0;
	paletteSrvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
	paletteSrvDesc.Buffer.NumElements = UINT(skeleton.joints.size());
	paletteSrvDesc.Buffer.StructureByteStride = sizeof(WellForGPU);
	device->CreateShaderResourceView(skinCluster.paletteResource.Get(),&paletteSrvDesc, skinCluster.paletteSrvHandle.first);
	
	skinCluster.influenceResource = CreateBufferResource(sizeof(VertexInfluence) * modelData.vertices.size());
	VertexInfluence* mappedInfluence = nullptr;
	skinCluster.influenceResource->Map(0, nullptr, reinterpret_cast<void**>(&mappedInfluence));
	std::memset(mappedInfluence, 0, sizeof(VertexInfluence) * modelData.vertices.size());
	skinCluster.mappedInfluence = { mappedInfluence,modelData.vertices.size() };

	skinCluster.influenceBufferView.BufferLocation = skinCluster.influenceResource->GetGPUVirtualAddress();
	skinCluster.influenceBufferView.SizeInBytes = UINT(sizeof(VertexInfluence) * modelData.vertices.size());
	skinCluster.influenceBufferView.StrideInBytes = sizeof(VertexInfluence);

	skinCluster.inverseBindPoseMatrices.resize(skeleton.joints.size());
	std::generate(skinCluster.inverseBindPoseMatrices.begin(), skinCluster.inverseBindPoseMatrices.end(), MakeIdentity4x4);


	for (const auto& jointWeight : modelData.skinClusterData) {
		
		auto it = skeleton.jointMap.find(jointWeight.first);
		if (it == skeleton.jointMap.end()) {
			
			continue;
		}
		
		skinCluster.inverseBindPoseMatrices[(*it).second] = jointWeight.second.inversBindPoseMatrix;
		for (const auto& vertexWeight : jointWeight.second.vertexWeights) {
			
			auto& currentInfluence = skinCluster.mappedInfluence[vertexWeight.vertexIndex];

			
			for (uint32_t index = 0; index < NUM_MAX_INFLUENCE; ++index) {
				
				if (currentInfluence.weights[index] == 0.0f) {
					currentInfluence.weights[index] = vertexWeight.weight;
					currentInfluence.jointIndices[index] = (*it).second;
					break;
				}

			}
		}


	}


	return skinCluster;
}

void LoadObjManagement::SkinUpdate(SkinCluster& skinCluster, const Skeleton& skeleton)
{
	//skeletonSpacematrixの値が違う件
	for (size_t jointIndex = 0; jointIndex < skeleton.joints.size(); ++jointIndex)
	{
		assert(jointIndex < skinCluster.inverseBindPoseMatrices.size());
		skinCluster.mappedPalette[jointIndex].skeletonSpaceMatrix =
			Multiply(skinCluster.inverseBindPoseMatrices[jointIndex], skeleton.joints[jointIndex].skeletonSpaceMatrix);

		skinCluster.mappedPalette[jointIndex].skeletonSpaceIncerseTransposeMatrix=
			MakeTransposeMatrix(Inverse(skinCluster.mappedPalette[jointIndex].skeletonSpaceMatrix));

	}
}
