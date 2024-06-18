#include"Math.h"



void Coordinate::UpdateMatrix()
{
	matWorld = MakeAffineMatrix(scale, rotate, translate);
	//TransferMatrix();
}

Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

Vector3 TransFormNormal(const Vector3& v, const Matrix4x4& m) {
	Vector3 result{
		v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] };
	return result;
}


Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 result =
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f

	};
	return result;

}

Matrix4x4 MakeScaleMatrix(const Vector3 scale)
{
	Matrix4x4 result{};

	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;


	return result;
}




Matrix4x4 MakeRotateXMatrix(float radian)
{
	Matrix4x4 result{};

	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = -std::sin(radian);
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}

Matrix4x4 MakeRotateYMatrix(float radian)
{
	Matrix4x4 result{};

	result.m[0][0] = std::cos(radian);
	result.m[0][1] = 0;
	result.m[0][2] = -std::sin(radian);
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = std::sin(radian);
	result.m[2][1] = 0;
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;

}

Matrix4x4 MakeRotateZMatrix(float radian)
{
	Matrix4x4 result{};

	result.m[0][0] = std::cos(radian);
	result.m[0][1] = std::sin(radian);
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = -std::sin(radian);
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;

}


Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result{};

	result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] +
		m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];

	result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] +
		m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];

	result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] +
		m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];

	result.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] +
		m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];


	result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] +
		m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];

	result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] +
		m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];

	result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] +
		m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];

	result.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] +
		m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];


	result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] +
		m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];

	result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] +
		m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];

	result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] +
		m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];

	result.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] +
		m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];


	result.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] +
		m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];

	result.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] +
		m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];

	result.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] +
		m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];

	result.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] +
		m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];


	return result;
}



Matrix4x4 MakeRotateXYZMatrix(float radianX, float radianY, float radianZ)
{
	Matrix4x4 result;

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(radianX);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(radianY);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(radianZ);

	result = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	return result;
}




Matrix4x4 MakeTranslateMatrix(const Vector3 translate)
{
	Matrix4x4 result{};

	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;


	return result;
}



Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	Matrix4x4 result;

	// Scale
	Matrix4x4 scaleMatrix;
	scaleMatrix = MakeScaleMatrix(scale);

	// Rotate
	Matrix4x4 rotateMatrix;
	rotateMatrix = MakeRotateXYZMatrix(rotate.x, rotate.y, rotate.z);

	// Translate
	Matrix4x4 translateMatrix;
	translateMatrix = MakeTranslateMatrix(translate);


	result = Multiply(scaleMatrix, Multiply(rotateMatrix, translateMatrix));

	return result;
}
//
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspecrRatio, float nearClip, float farClip) {

	Matrix4x4 result;

	result.m[0][0] = (1 / aspecrRatio) * 1 / std::tan(fovY / 2);
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1 / std::tan(fovY / 2);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = -nearClip * farClip / (farClip - nearClip);
	result.m[3][3] = 0.0f;

	return result;
}
//
Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 result{};
	float as = m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] +
		m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] +
		m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2] -

		m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] -
		m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] -
		m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2] -

		m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] -
		m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] -
		m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2] +

		m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] +
		m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] +
		m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2] +

		m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] +
		m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] +
		m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2] -

		m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] -
		m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] -
		m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2] -

		m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] -
		m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] -
		m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0] +

		m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] +
		m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] +
		m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];

	assert(as != 0.0f);
	float determinantRecp = 1.0f / as;

	result.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] +
		m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] -
		m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]

		) *
		determinantRecp;
	result.m[0][1] = (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] -
		m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] +
		m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]) *
		determinantRecp;

	result.m[0][2] = (

		m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] +
		m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] -
		m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]) *
		determinantRecp;

	result.m[0][3] = (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] -
		m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] +
		m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]) *
		determinantRecp;
	// 二行目

	result.m[1][0] = (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] -
		m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] +
		m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]

		) *
		determinantRecp;
	result.m[1][1] = (

		m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] +
		m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] -
		m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]) *
		determinantRecp;

	result.m[1][2] = (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] -
		m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] +
		m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]) *
		determinantRecp;

	result.m[1][3] = (

		m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] +
		m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] -
		m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]) *
		determinantRecp;
	// 三行目

	result.m[2][0] = (

		m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] +
		m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][3] * m.m[2][1] * m.m[3][0] -
		m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]

		) *
		determinantRecp;
	result.m[2][1] = (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] -
		m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[2][1] * m.m[3][0] +
		m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]) *
		determinantRecp;

	result.m[2][2] = (

		m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] +
		m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][3] * m.m[1][1] * m.m[3][0] -
		m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]) *
		determinantRecp;

	result.m[2][3] = (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] -
		m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] +
		m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]) *
		determinantRecp;
	// 四行目

	result.m[3][0] = (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] -
		m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][2] * m.m[2][1] * m.m[3][0] +
		m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]

		) *
		determinantRecp;
	result.m[3][1] = (

		m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] +
		m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[2][1] * m.m[3][0] -
		m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]) *
		determinantRecp;

	result.m[3][2] = (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] -
		m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][2] * m.m[1][1] * m.m[3][0] +
		m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]) *
		determinantRecp;

	result.m[3][3] = (

		m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] +
		m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] -
		m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]) *
		determinantRecp;

	return result;
}


Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float neaCrlip, float farClip)
{
	Matrix4x4 result = {};
	result.m[0][0] = 2.0f / (right - left);
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = (1 / farClip - neaCrlip);
	result.m[2][3] = 0;

	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = neaCrlip / (neaCrlip - farClip);
	result.m[3][3] = 1;

	return result;
}

//float Length(const Vector3& v)
//{
//	float result;
//	result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
//
//	return result;
//}
//Vector3 Normalize(const Vector3& v)
//{
//	Vector3 result;
//	result.x = v.x / Length(v);
//	result.y = v.y / Length(v);
//	result.z = v.z / Length(v);
//
//
//
//	return result;
//}
Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle)
{
	Matrix4x4 result{};
	float sinAngle = sinf(angle);
	float cosAngle = cosf(angle);

	result = MakeIdentity4x4();

	result.m[0][0] = (axis.x * axis.x) * (1 - cosAngle) + cosAngle;
	result.m[0][1] = (axis.x * axis.y) * (1 - cosAngle) - axis.z * sinAngle;
	result.m[0][2] = (axis.x * axis.z) * (1 - cosAngle) + axis.y * sinAngle;

	result.m[1][0] = (axis.x * axis.y) * (1 - cosAngle) + axis.z * sinAngle;
	result.m[1][1] = (axis.y * axis.y) * (1 - cosAngle) + cosAngle;
	result.m[1][2] = (axis.y * axis.z) * (1 - cosAngle) - axis.x * sinAngle;

	result.m[2][0] = (axis.x * axis.z) * (1 - cosAngle) - axis.y * sinAngle;
	result.m[2][1] = (axis.y * axis.z) * (1 - cosAngle) + axis.x * sinAngle;
	result.m[2][2] = (axis.z * axis.z) * (1 - cosAngle) + cosAngle;
	return result;
}
//減算 
Vector3 Subract(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}
float Dot(const Vector3& v1, const Vector3& v2) {
	float result{};
	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

	return result;
}
Vector3 SlerpFanc(const Vector3& v1, const Vector3& v2, float f)
{
	float dot = Dot(v1, v2);
	float theta = std::acos(dot) * f;
	Vector3 relaive = { v2.x - v1.x * dot,v2.y - v1.y * dot, v2.z - v1.z * dot };
	relaive = Normalize(relaive);
	Vector3 result = {
		v1.x * cosf(theta) + relaive.x * sinf(theta),
		v1.y * cosf(theta) + relaive.y * sinf(theta),
		v1.z * cosf(theta) + relaive.z * sinf(theta)

	};
	return result;
}
float Length(const Vector3& v) {
	float result{};
	result = sqrt(Dot(v, v));
	return result;
}
Vector3 Normalize(const Vector3& v) {
	Vector3 result{};
	float length = Length(v);
	if (length != 0.0f) {
		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;
	}
	return result;
}
Matrix4x4 MakeViewportMatrix(
	float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result;
	result.m[0][0] = width / 2;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = -(height / 2);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = maxDepth - minDepth;
	result.m[2][3] = 0;

	result.m[3][0] = left + (width / 2);
	result.m[3][1] = top + (height / 2);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1;

	return result;
}
Vector3 Transform3(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;

	result.x = (vector.x * matrix.m[0][0]) + (vector.y * matrix.m[1][0]) +
		(vector.z * matrix.m[2][0]) + (1.0f * matrix.m[3][0]);

	result.y = (vector.x * matrix.m[0][1]) + (vector.y * matrix.m[1][1]) +
		(vector.z * matrix.m[2][1]) + (1.0f * matrix.m[3][1]);

	result.z = (vector.x * matrix.m[0][2]) + (vector.y * matrix.m[1][2]) +
		(vector.z * matrix.m[2][2]) + (1.0f * matrix.m[3][2]);

	float w = (vector.x * matrix.m[0][3]) + (vector.y * matrix.m[1][3]) +
		(vector.z * matrix.m[2][3]) + (1.0f * matrix.m[3][3]);

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}
Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to) {

	Vector3 normalizeFrom = from;
	Vector3 normalizeTo = to;


	Vector3 uvCross = Cross(normalizeFrom, normalizeTo);
	Vector3 n = Normalize(uvCross);

	if (from.x == -to.x || from.y == -to.y || from.z == -to.z) {
		if (from.x != 0 || from.y != 0) {
			n = { from.y,-from.x,0 };
		}
		else if (from.x != 0 || from.z != 0)
		{
			n = { from.z,0,-from.x };
		}
	}

	//内積で求めてね
	float cos = Dot(normalizeFrom, normalizeTo);

	//外積で求めてね
	float sin = Length(Cross(normalizeFrom, normalizeTo));


	Matrix4x4 resultR = {};
	resultR.m[0][0] = n.x * n.x * (1 - cos) + cos;
	resultR.m[0][1] = n.x * n.y * (1 - cos) + n.z * sin;
	resultR.m[0][2] = n.x * n.z * (1 - cos) - n.y * sin;
	resultR.m[0][3] = 0.0f;

	resultR.m[1][0] = n.y * n.x * (1 - cos) - n.z * sin;
	resultR.m[1][1] = n.y * n.y * (1 - cos) + cos;
	resultR.m[1][2] = n.y * n.z * (1 - cos) + n.x * sin;
	resultR.m[1][3] = 0.0f;

	resultR.m[2][0] = n.z * n.x * (1 - cos) + n.y * sin;
	resultR.m[2][1] = n.z * n.y * (1 - cos) - n.x * sin;
	resultR.m[2][2] = n.z * n.z * (1 - cos) + cos;
	resultR.m[2][3] = 0.0f;

	resultR.m[3][0] = 0.0f;
	resultR.m[3][1] = 0.0f;
	resultR.m[3][2] = 0.0f;
	resultR.m[3][3] = 1.0f;

	return resultR;
}

Vector3 DotVector3(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};
	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;

	return result;
}
Vector3 Cross(const Vector3 v1, const Vector3 v2) {
	Vector3 result;
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;
}
Vector3 TransformRot(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;

	result.x = (vector.x * matrix.m[0][0]) + (vector.y * matrix.m[1][0])
		+ (vector.z * matrix.m[2][0]) + (1.0f * matrix.m[3][0]);

	result.y = (vector.x * matrix.m[0][1]) + (vector.y * matrix.m[1][1])
		+ (vector.z * matrix.m[2][1]) + (1.0f * matrix.m[3][1]);

	result.z = (vector.x * matrix.m[0][2]) + (vector.y * matrix.m[1][2])
		+ (vector.z * matrix.m[2][2]) + (1.0f * matrix.m[3][2]);

	float w = (vector.x * matrix.m[0][3]) + (vector.y * matrix.m[1][3]) + (vector.z * matrix.m[2][3]) + (1.0f * matrix.m[3][3]);


	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;


}
Quaternion MultiplyQuaternion(const Quaternion& lhs, const Quaternion& rhs)
{
	return Quaternion();
}

Quaternion IdentityQuaternion() {


	Quaternion result = {};

	result.w = 1.0f;
	result.x = 0.0f;
	result.y = 0.0f;
	result.z = 0.0f;





	return result;
}
Quaternion Conjugate(const Quaternion& quaternion) {


	Quaternion result = {};
	result.x = -quaternion.x;
	result.y = -quaternion.y;
	result.z = -quaternion.z;
	result.w = quaternion.w;


	return result;
}

float Norm(const Quaternion& quaternion) {

	//q=sqrtf(qq)
	float result = 0.0f;
	result = sqrtf(
		quaternion.w * quaternion.w +
		quaternion.x * quaternion.x +
		quaternion.y * quaternion.y +
		quaternion.z * quaternion.z);

	return result;
}
Quaternion NormalizeQuaternion(const Quaternion& quaternion) {
	Quaternion result = {};


	float length = sqrtf(
		quaternion.x * quaternion.x +
		quaternion.y * quaternion.y +
		quaternion.z * quaternion.z +
		quaternion.w * quaternion.w
	);


	Quaternion preResult = {};
	preResult.x = quaternion.x;
	preResult.y = quaternion.y;
	preResult.z = quaternion.z;
	preResult.w = quaternion.w;

	if (length != 0.0f) {
		preResult.x = quaternion.x / length;
		preResult.y = quaternion.y / length;
		preResult.z = quaternion.z / length;
		preResult.w = quaternion.w / length;

	}

	result.x = preResult.x;
	result.y = preResult.y;
	result.z = preResult.z;
	result.w = preResult.w;


	return result;
}

Quaternion InverseQuaternion(const Quaternion& quaternion) {



	Quaternion result = {};


	float norm = Norm(quaternion);
	Quaternion conjugate = Conjugate(quaternion);

	float t = norm * norm;

	result.x = conjugate.x / t;
	result.y = conjugate.y / t;
	result.z = conjugate.z / t;
	result.w = conjugate.w / t;


	return result;
}

Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle)
{
	Quaternion result;
	result = IdentityQuaternion();

	float halfAngle = angle / 2;

	result.x = axis.x * sinf(halfAngle);
	result.y = axis.y * sinf(halfAngle);
	result.z = axis.z * sinf(halfAngle);
	result.w = cosf(halfAngle);

	return result;
}

Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion)
{
	Vector3 result;

	Quaternion fromVector;
	fromVector.x = vector.x;
	fromVector.y = vector.y;
	fromVector.z = vector.z;
	fromVector.w = 0.0f;

	Quaternion conj = Conjugate(quaternion);

	Quaternion rot;
	rot = MultiplyQuaternion(quaternion, MultiplyQuaternion(fromVector, conj));

	result.x = rot.x;
	result.y = rot.y;
	result.z = rot.z;

	return result;
}
Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion)
{
	Matrix4x4 result;
	result.m[0][0] = (quaternion.w * quaternion.w) + (quaternion.x * quaternion.x) - (quaternion.y * quaternion.y) - (quaternion.z * quaternion.z);
	result.m[0][1] = 2.0f * ((quaternion.x * quaternion.y) + (quaternion.w * quaternion.z));
	result.m[0][2] = 2.0f * ((quaternion.x * quaternion.z) - (quaternion.w * quaternion.y));
	result.m[0][3] = 0.0f;

	result.m[1][0] = 2.0f * ((quaternion.x * quaternion.y) - (quaternion.w * quaternion.z));
	result.m[1][1] = (quaternion.w * quaternion.w) - (quaternion.x * quaternion.x) + (quaternion.y * quaternion.y) - (quaternion.z * quaternion.z);
	result.m[1][2] = 2.0f * ((quaternion.y * quaternion.z) + (quaternion.w * quaternion.x));
	result.m[1][3] = 0.0f;

	result.m[2][0] = 2.0f * ((quaternion.x * quaternion.z) + (quaternion.w * quaternion.y));
	result.m[2][1] = 2.0f * ((quaternion.y * quaternion.z) - (quaternion.w * quaternion.x));
	result.m[2][2] = (quaternion.w * quaternion.w) - (quaternion.x * quaternion.x) - (quaternion.y * quaternion.y) + (quaternion.z * quaternion.z);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}
Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t)
{

	//// クォータニオンの内積を計算
	//float dot = DotQuaternion(q1, q2);
	//Quaternion qn1 = q1;//q1のnew
	//Quaternion qn2 = q2;//q2のnew
	//if (dot < 0.0f)
	//{
	//	qn1 = { -qn1.x,-qn1.y,-qn1.z,-qn1.w };
	//	dot = -dot;
	//}
	//
	//// q1とq2の間の角度を計算
	//float theta = std::acos(dot);
	//
	//float sinTheta = std::sin(theta);
	//float scale0 = std::sin((1 - t) * theta) / sinTheta;
	//float scale1 = std::sin(t * theta) / sinTheta;
	//
	//// 補間されたクォータニオンを計算して返す
	//return Quaternion(
	//	scale0 * qn1.x + scale1 * qn2.x,
	//	scale0 * qn1.y + scale1 * qn2.y,
	//	scale0 * qn1.z + scale1 * qn2.z,
	//	scale0 * qn1.w + scale1 * qn2.w
	//);




	//q0・q1=||q0||・||q1||*cosθ
	//今は単位Quaternionを求めたいのでノルムは1なので
	//q0・q1 = cosθでOK!!
	float dot =
		q0.x * q1.x +
		q0.y * q1.y +
		q0.z * q1.z +
		q0.w * q1.w;

	//dotが限りなく1に近い場合
	const float EPSILON = 0.0005f;
	if (dot > 1.0f - EPSILON) {
		// 直線補間を行う
		Quaternion result = {};
		result.x = (1.0f - t) * q0.x + t * q1.x;
		result.y = (1.0f - t) * q0.y + t * q1.y;
		result.z = (1.0f - t) * q0.z + t * q1.z;
		result.w = (1.0f - t) * q0.w + t * q1.w;
		return result;
	}

	//最短が良いよね
	//角度を求める
	float theta = std::acosf(dot);

	//Quaternionの前にある係数
	//scale...係数
	float scale0 = float(std::sin((1 - t) * theta) / std::sin(theta));
	float scale1 = float(std::sin(t * theta) / std::sin(theta));

	Quaternion result = {};
	result.x = scale0 * q0.x + scale1 * q1.x;
	result.y = scale0 * q0.y + scale1 * q1.y;
	result.z = scale0 * q0.z + scale1 * q1.z;
	result.w = scale0 * q0.w + scale1 * q1.w;

	return result;

}
float DotQuaternion(const Quaternion& q1, const Quaternion& q2)
{
	return float(q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z);
}
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) {
	Vector3 result{};
	result.x = v1.x + t * (v2.x - v1.x);
	result.y = v1.y + t * (v2.y - v1.y);
	result.z = v1.z + t * (v2.z - v1.z);
	return result;
}
float FLerp(float t, const float& s, const float& e) {
	float result;
	float es = e - s;
	result = s + t * es;
	return result;
}
Quaternion QLerp(float t, const Quaternion& s, const Quaternion& e) {
	Quaternion result;
	Quaternion es = e - s;
	result = s + t * es;
	return result;
}
Quaternion Slerp(float t, const Quaternion& s, const Quaternion& e) {
	Quaternion ns = Normalize(s);
	Quaternion ne = Normalize(e);
	float dot = ns.x * ne.x + ns.y * ne.y + ns.z * ne.z + ns.w * ne.w;
	if (std::abs(dot) > 0.999f) {
		return QLerp(t, ns, ne);
	}
	if (dot < 0.0f) {
		ns = -1 * ns;
		dot = -1.0f;
	}

	float theta = std::acos(dot);
	float sinTheta = std::sin(theta);
	float t1 = std::sin((1.0f - t) * theta) / sinTheta;
	float t2 = std::sin(t * theta) / sinTheta;

	return (t1 * ns + t2 * ne);
}
Quaternion Normalize(const Quaternion& q) {
	float len = LengthQuaternion(q);
	Quaternion result;
	if (len != 0.0f) {
		result.w = q.w / len;
		result.x = q.x / len;
		result.y = q.y / len;
		result.z = q.z / len;
		return result;
	}
	else {
		return q;
	}
}
float LengthQuaternion(const Quaternion& q) {
	return std::sqrtf(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
}
Matrix4x4 MakeQuatAffineMatrix(const Vector3& scale, const Matrix4x4& rotate, const Vector3& translate) {
	Matrix4x4 result;

	result.m[0][0] = scale.x * rotate.m[0][0];
	result.m[0][1] = scale.x * rotate.m[0][1];
	result.m[0][2] = scale.x * rotate.m[0][2];
	result.m[0][3] = 0;
	result.m[1][0] = scale.y * rotate.m[1][0];
	result.m[1][1] = scale.y * rotate.m[1][1];
	result.m[1][2] = scale.y * rotate.m[1][2];
	result.m[1][3] = 0;
	result.m[2][0] = scale.z * rotate.m[2][0];
	result.m[2][1] = scale.z * rotate.m[2][1];
	result.m[2][2] = scale.z * rotate.m[2][2];
	result.m[2][3] = 0;
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1;
	return result;
}
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Quaternion& quaternion, const Vector3& translate) {
	Matrix4x4 result{};

	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	Matrix4x4 rotateMatrix = MakeRotateMatrix(quaternion);
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

	result = Multiply(scaleMatrix, Multiply(rotateMatrix, translateMatrix));

	return result;
}
Matrix4x4 MakeTransposeMatrix(const Matrix4x4 m) {
	Matrix4x4 result = {};

	result.m[0][0] = m.m[0][0];
	result.m[0][1] = m.m[1][0];
	result.m[0][2] = m.m[2][0];
	result.m[0][3] = m.m[3][0];

	result.m[1][0] = m.m[0][1];
	result.m[1][1] = m.m[1][1];
	result.m[1][2] = m.m[2][1];
	result.m[1][3] = m.m[3][1];

	result.m[2][0] = m.m[0][2];
	result.m[2][1] = m.m[1][2];
	result.m[2][2] = m.m[2][2];
	result.m[2][3] = m.m[3][2];

	result.m[3][0] = m.m[0][3];
	result.m[3][1] = m.m[1][3];
	result.m[3][2] = m.m[2][3];
	result.m[3][3] = m.m[3][3];


	return result;
}
