#pragma once
#include<Windows.h>
#include <cstdint>
#include<string>
#include<format>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<dxgidebug.h>
#include<dxcapi.h>
#include <cassert>
#include <cmath>
#include <numbers>

#include"../Base/Log.h"

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxcompiler.lib")

struct PSOProperty
{
	ID3D12PipelineState* GraphicsPipelineState = nullptr;
	ID3D12RootSignature* rootSignature = nullptr;
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

};
struct PSO
{
	PSOProperty Texture;
	PSOProperty polygon;

};
struct  ShaderMode
{
	IDxcBlob* vertexBlob;
	IDxcBlob* pixelBlob;
};
struct Shaders {
	ShaderMode shape;
};

struct Vector2 {
	float x;
	float y;
};
struct  Vector3
{
	float x;
	float y;
	float z;

};
struct Vector4
{
	float x;
	float y;
	float z;
	float w;
};
struct   Matrix4x4 {
	float m[4][4];
};

struct  Transform
{
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
	Matrix4x4 matWorld;
};
struct Coordinate {

	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
	Vector4 color;
	Matrix4x4 matWorld;

	void UpdateMatrix();
	//void TransferMatrix();

};
struct ParticleTransform {
	Transform transform;
	Vector3 Velocity;
};


struct Camera {
	Vector3 cameraPos;
};

struct Quaternion {
	float x;
	float y;
	float z;
	float w;
};
/// <summary>
/// 数学
/// </summary>
/// <returns></returns>
Vector3 Add(const Vector3& v1, const Vector3& v2);

Vector3 TransFormNormal(const Vector3& v, const Matrix4x4& m);
Matrix4x4 MakeIdentity4x4();
Matrix4x4 MakeScaleMatrix(const Vector3 scale);
Matrix4x4 MakeRotateXMatrix(float radian);
Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 MakeRotateXYZMatrix(float radianX, float radianY, float radianZ);
Matrix4x4 MakeTranslateMatrix(const Vector3 translate);
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
Matrix4x4 MakePerspectiveFovMatrix(
	float fovY, float aspecrRatio, float nearClip, float farClip);
Matrix4x4 Inverse(const Matrix4x4& m);
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float neaCrlip, float farClip);
float Length(const Vector3& v);
Vector3 Normalize(const Vector3& v);
Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle);
Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to);
Vector3 DotVector3(const Vector3& v1, const Vector3& v2);
Vector3 Cross(const Vector3 v1, const Vector3 v2);
Vector3 TransformRot(const Vector3& vector, const Matrix4x4& matrix);

Vector3 Subract(const Vector3& v1, const Vector3& v2);
float Dot(const Vector3& v1, const Vector3& v2);
Vector3 SlerpFanc(const Vector3& v1, const Vector3& v2,float f);
Matrix4x4 MakeViewportMatrix(
	float left, float top, float width, float height, float minDepth, float maxDepth);
Vector3 Transform3(const Vector3& vector, const Matrix4x4& matrix);

Quaternion MultiplyQuaternion(const Quaternion& lhs, const Quaternion& rhs);

Quaternion IdentityQuaternion();

Quaternion Conjugate(const Quaternion& quaternion);


float Norm(const Quaternion& quaternion);

Quaternion NormalizeQuaternion(const Quaternion& quaternion);

Quaternion InverseQuaternion(const Quaternion& quaternion);

Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle);

Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion);

Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion);
Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);