#include "Obj3D.h"

void Obj3D::Initialize( const std::string& directoryPath,const std::string& filename)
{
	
	modelData = LoadObjFile(directoryPath, filename);

	vetexResource = CreateBufferResource(sizeof(VertexData) * modelData.vertices.size());
	materialResource = CreateBufferResource(sizeof(Vector4));
	
	lightResource = CreateBufferResource(sizeof(DirectionalLight));

	
	vertxBufferView.BufferLocation = vetexResource.Get()->GetGPUVirtualAddress();
	vertxBufferView.SizeInBytes = UINT(sizeof(VertexData) * modelData.vertices.size());
	vertxBufferView.StrideInBytes = sizeof(VertexData);
    matrix = MakeIdentity4x4();

	pos = { 0.0f,0.0f,5.0f };
	//tex_ = tex;
}

void Obj3D::Draw( Vector4 Color,CameraData*cameraData, WorldTransform* worldTransform)
{
	
	
	
	//
	VertexData* vertexData = nullptr;
	Vector4* materialData = nullptr;
	TransformationMatrix* matrixData = nullptr;
	DirectionalLight* lightData = nullptr;


	vetexResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	materialResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&materialData));	
	lightResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&lightData));

	std::memcpy(vertexData, modelData.vertices.data(), sizeof(VertexData)*modelData.vertices.size());
	//
	// 
	Matrix4x4 ProjectionMatrix = MakePerspectiveFovMatrix(0.45f, float(1280.0f / 720.0f), 0.1f, 100.0f);

	Matrix4x4 CameraMatrix = MakeIdentity4x4();

	
	*materialData = Color;
	//lightData->direction = { 0.0f,1.0f,0.0f };
	lightData->color = { 1.0f,1.0f,1.0f,1.0f };
	lightData->intensity = 1.0f;
	ImGui::Begin("direction");
	ImGui::SliderFloat3("t", &direction_.x, -1.0f, 1.0f);
	ImGui::End();
	lightData->direction = direction_;
	//
	ID3D12GraphicsCommandList* commandList = DxCommon::GetInstance()->GetCommandList();
	PSOProperty pso_ = LightPSO::GetInstance()->GetPSO().Texture;
	commandList->SetGraphicsRootSignature(pso_.rootSignature);
	commandList->SetPipelineState(pso_.GraphicsPipelineState);//


	commandList->IASetVertexBuffers(0, 1, &vertxBufferView);

	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	commandList->SetGraphicsRootConstantBufferView(0, materialResource.Get()->GetGPUVirtualAddress());
	commandList->SetGraphicsRootConstantBufferView(1, worldTransform->GetColl()->GetGPUVirtualAddress());
	commandList->SetGraphicsRootConstantBufferView(3, lightResource.Get()->GetGPUVirtualAddress());
	commandList->SetGraphicsRootConstantBufferView(4, cameraData->GetColl()->GetGPUVirtualAddress());

	DescriptorManagement::rootParamerterCommand(2, tex_);
	commandList->DrawInstanced(UINT(modelData.vertices.size()), 1, 0, 0);
}



ModelData Obj3D::LoadObjFile(const std::string& directoryPath, const std::string& filename)
{
	ModelData modelData = {};
	std::vector<Vector4> positions;
	std::vector<Vector3> normals;
	std::vector<Vector2> texcoords;
	std::string line;
	std::ifstream file(directoryPath + "/" + filename);
	assert(file.is_open());

	while (std::getline(file, line))
	{
		std::string identifier;
		std::istringstream s(line);
		s >> identifier;

		if (identifier == "v")
		{   //v頂点位置
			Vector4 position;
			s >> position.x >> position.y >> position.z;

			position.z *= -1.0f;
			position.w = 1.0f;
			positions.push_back(position);
		}
		else if (identifier == "vt")
		{	//vt頂点テクスチャの座標
			Vector2 texcoord;
			s >> texcoord.x >> texcoord.y;
			texcoord.y *= -1.0f;

			texcoords.push_back(texcoord);
		}
		else if (identifier == "vn")
		{   //vn頂点法線
			Vector3 normal;

			s >> normal.x >> normal.y >> normal.z;
			normal.z *= -1.0f;
			normals.push_back(normal);
		}
		else if (identifier == "f") {
			VertexData triangle[3];
			for (int32_t faceVertex = 0; faceVertex < 3; ++faceVertex) {
				std::string vertexDefinition;
				s >> vertexDefinition;
				//頂点の要素へのIndexは「位置/UV/法線」で格納されているので、分解してIndexを取得する
				std::istringstream v(vertexDefinition);
				uint32_t elementIndices[3];
				for (int32_t element = 0; element < 3; ++element) {
					std::string index;
					std::getline(v, index, '/');
					elementIndices[element] = std::stoi(index);
				}

				Vector4 position = positions[elementIndices[0] - 1];
				Vector2 texcoord = texcoords[elementIndices[1] - 1];
				Vector3 normal = normals[elementIndices[2] - 1];
				triangle[faceVertex] = { position,texcoord,normal };
			}
			//頂点を逆順で登録することで、回り順を逆にする
			modelData.vertices.push_back(triangle[2]);
			modelData.vertices.push_back(triangle[1]);
			modelData.vertices.push_back(triangle[0]);
		}
		else if (identifier == "mtllib") {
			//tex
			std::string materialFilename;
			s >> materialFilename;
			modelData.material = LoadMaterialTemplateFile(directoryPath, materialFilename);
		}

	}

	tex_= TexManager::LoadTexture(modelData.material.textureFilePath);

	return modelData;
}

MaterialData Obj3D::LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename)
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

