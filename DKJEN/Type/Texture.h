#include"../Math/Math.h"
#include"../Base/DxCommon.h"
#include"../Base/TexturePSO.h"
#include"../Base/ImageLoading.h"
class Texture
{
public:
	void Initialize(TexProeerty  tex);
	void Draw(Vector3 scale, Vector3 rotate, Vector3 translate, Vector4 Color);
	void Release();
	//
	static ID3D12Resource* CreateBufferResource(size_t sizeInbyte);
	static D3D12_VERTEX_BUFFER_VIEW VertexCreateBufferView(size_t sizeInbyte, ID3D12Resource* Resource, int size);

private:


	Vector4 lefe_ = {-0.5f, -0.5f, 0.0f, 1.0f};
	Vector4 top_ = { 0.0f,0.5f,0.0f,1.0f };
	Vector4 right_ = { 0.5f,-0.5f,0.0f,1.0f };

	//Vector4 Color_ = { 0.0f,0.0f,1.0f,1.0f };
	Transform transfom{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	const float size = 0.1f;
	DxCommon dxCommmon_;
	//
	ID3D12Resource* Vertex;

	ID3D12Resource* materialResource;
	ID3D12Resource* wvpResource;
	//
	D3D12_VERTEX_BUFFER_VIEW bufferView_;
	//
	Transform cameratransform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-5.0f} };
	///
	Matrix4x4 matrix;
	TexProeerty  tex_;
};
