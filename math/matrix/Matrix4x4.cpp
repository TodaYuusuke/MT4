#include "Matrix4x4.h"
#include "Novice.h"
#include "../vector/Vector3.h"
#include "../Quaternion.h"

using namespace LWP::Math;

// *** オペーレーターオーバーロード *** //

// Matrix4x4 Add(+) Matrix4x4
Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const {
	Matrix4x4 result{};
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			result.m[y][x] = m[y][x] + other.m[y][x];
		}
	}
	return result;
}

// Matrix4x4 Subtract(-) Matrix4x4
Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const {
	Matrix4x4 result{};
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			result.m[y][x] = m[y][x] - other.m[y][x];
		}
	}
	return result;
}

// Matrix4x4 Multiply(*) Matrix4x4
Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const {
	Matrix4x4 result{};
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			result.m[y][x] = (m[y][0] * other.m[0][x]) +
				(m[y][1] * other.m[1][x]) +
				(m[y][2] * other.m[2][x]) +
				(m[y][3] * other.m[3][x]);
		}
	}
	return result;
}
// Matrix4x4 Multiply(*) float
Matrix4x4 Matrix4x4::operator*(const float& other) const {
	Matrix4x4 result{};
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			result.m[y][x] = m[y][x] * other;
		}
	}
	return result;
}

void Matrix4x4::DrawDisplay(const char* label, int posX, int posY) {
	const int kRowSize = 20;	// 縦幅
	
	Novice::ScreenPrintf(posX, posY, label);
	for (int y = 0; y < 4; y++) {
		Novice::ScreenPrintf(posX, posY + (kRowSize * (y + 1)), "%6.3f  %6.3f  %6.3f  %6.3f", m[y][0], m[y][1], m[y][2], m[y][3]);
	}
}

// 行列式を返す関数
float Matrix4x4::Determinant() {
	// 行列式
	return (m[0][0] * m[1][1] * m[2][2] * m[3][3]) +
		(m[0][0] * m[1][2] * m[2][3] * m[3][1]) +
		(m[0][0] * m[1][3] * m[2][1] * m[3][2]) -

		(m[0][0] * m[1][3] * m[2][2] * m[3][1]) -
		(m[0][0] * m[1][2] * m[2][1] * m[3][3]) -
		(m[0][0] * m[1][1] * m[2][3] * m[3][2]) -

		(m[0][1] * m[1][0] * m[2][2] * m[3][3]) -
		(m[0][2] * m[1][0] * m[2][3] * m[3][1]) -
		(m[0][3] * m[1][0] * m[2][1] * m[3][2]) +

		(m[0][3] * m[1][0] * m[2][2] * m[3][1]) +
		(m[0][2] * m[1][0] * m[2][1] * m[3][3]) +
		(m[0][1] * m[1][0] * m[2][3] * m[3][2]) +

		(m[0][1] * m[1][2] * m[2][0] * m[3][3]) +
		(m[0][2] * m[1][3] * m[2][0] * m[3][1]) +
		(m[0][3] * m[1][1] * m[2][0] * m[3][2]) -

		(m[0][3] * m[1][2] * m[2][0] * m[3][1]) -
		(m[0][2] * m[1][1] * m[2][0] * m[3][3]) -
		(m[0][1] * m[1][3] * m[2][0] * m[3][2]) -

		(m[0][1] * m[1][2] * m[2][3] * m[3][0]) -
		(m[0][2] * m[1][3] * m[2][1] * m[3][0]) -
		(m[0][3] * m[1][1] * m[2][2] * m[3][0]) +

		(m[0][3] * m[1][2] * m[2][1] * m[3][0]) +
		(m[0][2] * m[1][1] * m[2][3] * m[3][0]) +
		(m[0][1] * m[1][3] * m[2][2] * m[3][0]);
}
// 逆行列を返す関数
Matrix4x4 Matrix4x4::Inverse() {
	Matrix4x4 result{};

	result.m[0][0] = (m[1][1] * m[2][2] * m[3][3]) + (m[1][2] * m[2][3] * m[3][1]) + (m[1][3] * m[2][1] * m[3][2])
		- (m[1][3] * m[2][2] * m[3][1]) - (m[1][2] * m[2][1] * m[3][3]) - (m[1][1] * m[2][3] * m[3][2]);
	result.m[0][1] = -(m[0][1] * m[2][2] * m[3][3]) - (m[0][2] * m[2][3] * m[3][1]) - (m[0][3] * m[2][1] * m[3][2])
		+ (m[0][3] * m[2][2] * m[3][1]) + (m[0][2] * m[2][1] * m[3][3]) + (m[0][1] * m[2][3] * m[3][2]);
	result.m[0][2] = (m[0][1] * m[1][2] * m[3][3]) + (m[0][2] * m[1][3] * m[3][1]) + (m[0][3] * m[1][1] * m[3][2])
		- (m[0][3] * m[1][2] * m[3][1]) - (m[0][2] * m[1][1] * m[3][3]) - (m[0][1] * m[1][3] * m[3][2]);
	result.m[0][3] = -(m[0][1] * m[1][2] * m[2][3]) - (m[0][2] * m[1][3] * m[2][1]) - (m[0][3] * m[1][1] * m[2][2])
		+ (m[0][3] * m[1][2] * m[2][1]) + (m[0][2] * m[1][1] * m[2][3]) + (m[0][1] * m[1][3] * m[2][2]);

	result.m[1][0] = -(m[1][0] * m[2][2] * m[3][3]) - (m[1][2] * m[2][3] * m[3][0]) - (m[1][3] * m[2][0] * m[3][2])
		+ (m[1][3] * m[2][2] * m[3][0]) + (m[1][2] * m[2][0] * m[3][3]) + (m[1][0] * m[2][3] * m[3][2]);
	result.m[1][1] = (m[0][0] * m[2][2] * m[3][3]) + (m[0][2] * m[2][3] * m[3][0]) + (m[0][3] * m[2][0] * m[3][2])
		- (m[0][3] * m[2][2] * m[3][0]) - (m[0][2] * m[2][0] * m[3][3]) - (m[0][0] * m[2][3] * m[3][2]);
	result.m[1][2] = -(m[0][0] * m[1][2] * m[3][3]) - (m[0][2] * m[1][3] * m[3][0]) - (m[0][3] * m[1][0] * m[3][2])
		+ (m[0][3] * m[1][2] * m[3][0]) + (m[0][2] * m[1][0] * m[3][3]) + (m[0][0] * m[1][3] * m[3][2]);
	result.m[1][3] = (m[0][0] * m[1][2] * m[2][3]) + (m[0][2] * m[1][3] * m[2][0]) + (m[0][3] * m[1][0] * m[2][2])
		- (m[0][3] * m[1][2] * m[2][0]) - (m[0][2] * m[1][0] * m[2][3]) - (m[0][0] * m[1][3] * m[2][2]);

	result.m[2][0] = (m[1][0] * m[2][1] * m[3][3]) + (m[1][1] * m[2][3] * m[3][0]) + (m[1][3] * m[2][0] * m[3][1])
		- (m[1][3] * m[2][1] * m[3][0]) - (m[1][1] * m[2][0] * m[3][3]) - (m[1][0] * m[2][3] * m[3][1]);
	result.m[2][1] = -(m[0][0] * m[2][1] * m[3][3]) - (m[0][1] * m[2][3] * m[3][0]) - (m[0][3] * m[2][0] * m[3][1])
		+ (m[0][3] * m[2][1] * m[3][0]) + (m[0][1] * m[2][0] * m[3][3]) + (m[0][0] * m[2][3] * m[3][1]);
	result.m[2][2] = (m[0][0] * m[1][1] * m[3][3]) + (m[0][1] * m[1][3] * m[3][0]) + (m[0][3] * m[1][0] * m[3][1])
		- (m[0][3] * m[1][1] * m[3][0]) - (m[0][1] * m[1][0] * m[3][3]) - (m[0][0] * m[1][3] * m[3][1]);
	result.m[2][3] = -(m[0][0] * m[1][1] * m[2][3]) - (m[0][1] * m[1][3] * m[2][0]) - (m[0][3] * m[1][0] * m[2][1])
		+ (m[0][3] * m[1][1] * m[2][0]) + (m[0][1] * m[1][0] * m[2][3]) + (m[0][0] * m[1][3] * m[2][1]);

	result.m[3][0] = -(m[1][0] * m[2][1] * m[3][2]) - (m[1][1] * m[2][2] * m[3][0]) - (m[1][2] * m[2][0] * m[3][1])
		+ (m[1][2] * m[2][1] * m[3][0]) + (m[1][1] * m[2][0] * m[3][2]) + (m[1][0] * m[2][2] * m[3][1]);
	result.m[3][1] = (m[0][0] * m[2][1] * m[3][2]) + (m[0][1] * m[2][2] * m[3][0]) + (m[0][2] * m[2][0] * m[3][1])
		- (m[0][2] * m[2][1] * m[3][0]) - (m[0][1] * m[2][0] * m[3][2]) - (m[0][0] * m[2][2] * m[3][1]);
	result.m[3][2] = -(m[0][0] * m[1][1] * m[3][2]) - (m[0][1] * m[1][2] * m[3][0]) - (m[0][2] * m[1][0] * m[3][1])
		+ (m[0][2] * m[1][1] * m[3][0]) + (m[0][1] * m[1][0] * m[3][2]) + (m[0][0] * m[1][2] * m[3][1]);
	result.m[3][3] = (m[0][0] * m[1][1] * m[2][2]) + (m[0][1] * m[1][2] * m[2][0]) + (m[0][2] * m[1][0] * m[2][1])
		- (m[0][2] * m[1][1] * m[2][0]) - (m[0][1] * m[1][0] * m[2][2]) - (m[0][0] * m[1][2] * m[2][1]);

	float constant = 1.0f / Determinant();
	return result * constant;
}
// 転置行列を返す関数
Matrix4x4 Matrix4x4::Transpose() {
	Matrix4x4 result{};
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			result.m[y][x] = m[x][y];
		}
	}
	return result;
}

// *** 行列作成機 *** //

// 平行移動行列
Matrix4x4 Matrix4x4::CreateTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result{};
	result.m[0][0] = 1;
	result.m[1][1] = 1;
	result.m[2][2] = 1;
	result.m[3][3] = 1;
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	return result;
}
// X軸回転行列
Matrix4x4 Matrix4x4::CreateRotateXMatrix(const float& radian) {
	Matrix4x4 result{};
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[2][1] = -std::sin(radian);
	result.m[2][2] = std::cos(radian);

	result.m[0][0] = 1;
	result.m[3][3] = 1;
	return result;
}
// y軸回転行列
Matrix4x4 Matrix4x4::CreateRotateYMatrix(const float& radian) {
	Matrix4x4 result{};
	result.m[0][0] = std::cos(radian);
	result.m[0][2] = -std::sin(radian);
	result.m[2][0] = std::sin(radian);
	result.m[2][2] = std::cos(radian);

	result.m[1][1] = 1;
	result.m[3][3] = 1;
	return result;
}
// z軸回転行列
Matrix4x4 Matrix4x4::CreateRotateZMatrix(const float& radian) {
	Matrix4x4 result{};
	result.m[0][0] = std::cos(radian);
	result.m[0][1] = std::sin(radian);
	result.m[1][0] = -std::sin(radian);
	result.m[1][1] = std::cos(radian);

	result.m[2][2] = 1;
	result.m[3][3] = 1;
	return result;
}
// 合成された回転行列を返す
Matrix4x4 Matrix4x4::CreateRotateXYZMatrix(const Vector3& rotate) {
	Matrix4x4 x = CreateRotateXMatrix(rotate.x);
	Matrix4x4 y = CreateRotateYMatrix(rotate.y);
	Matrix4x4 z = CreateRotateZMatrix(rotate.z);
	return x * y * z;
}
// 拡大縮小行列
Matrix4x4 Matrix4x4::CreateScaleMatrix(const Vector3& scale) {
	Matrix4x4 result{};
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1;
	return result;
}

// 3次元アフィン変換行列
Matrix4x4 Matrix4x4::CreateAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 s = CreateScaleMatrix(scale);
	Matrix4x4 r = CreateRotateXYZMatrix(rotate);
	Matrix4x4 t = CreateTranslateMatrix(translate);
	return s * r * t;
}

// 透視射影行列
Matrix4x4 Matrix4x4::CreatePerspectiveFovMatrix(const float& fovY, const float& aspectRatio, const float& nearClip, const float& farClip) {
	Matrix4x4 result{};

	result.m[0][0] = (1.0f / aspectRatio) * (1.0f / std::tan(fovY / 2.0f));

	result.m[1][1] = (1.0f / std::tan(fovY / 2.0f));

	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1;

	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);

	return result;
}
// 正射影行列
Matrix4x4 Matrix4x4::CreateOrthographicMatrix(const float& left, const float& top, const float& right, const float& bottom, const float& nearClip, const float& farClip) {
	Matrix4x4 result{};

	result.m[0][0] = 2.0f / (right - left);
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[2][2] = 1.0f / (farClip - nearClip);

	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1;
	//result.m[3][0] = - ((right + left) / (right - left));
	//result.m[3][1] = (top + bottom) / (top - bottom);
	//result.m[3][2] =  - ((farClip + nearClip) / (farClip - nearClip));
	//result.m[3][3] = 1;

	return result;
}
// ビューポート変換行列
Matrix4x4 Matrix4x4::CreateViewportMatrix(const float& left, const float& top, const float& width, const float& height, const float& minDepth, const float& maxDepth) {
	Matrix4x4 result{};

	result.m[0][0] = width / 2.0f;
	result.m[1][1] = -(height / 2.0f);
	result.m[2][2] = maxDepth - minDepth;

	result.m[3][0] = left + (width / 2.0f);
	result.m[3][1] = top + (height / 2.0f);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1;

	return result;
}

Matrix4x4 Matrix4x4::CreateLookAtMatrix(const Vector3& eye, const Vector3& at, const Vector3& up) {
	Vector3 forward = (at - eye).Normalize();
	Vector3 right = Vector3::Cross(up, forward).Normalize();
	Vector3 newUp = Vector3::Cross(forward, right).Normalize();

	Matrix4x4 result;

	result.m[0][0] = right.x;
	result.m[0][1] = newUp.x;
	result.m[0][2] = -forward.x;
	result.m[0][3] = 0.0f;

	result.m[1][0] = right.y;
	result.m[1][1] = newUp.y;
	result.m[1][2] = -forward.y;
	result.m[1][3] = 0.0f;

	result.m[2][0] = right.z;
	result.m[2][1] = newUp.z;
	result.m[2][2] = -forward.z;
	result.m[2][3] = 0.0f;

	result.m[3][0] = Vector3::Dot(-1 * right, eye);
	result.m[3][1] = Vector3::Dot(-1 * newUp, eye);
	result.m[3][2] = Vector3::Dot(forward, eye);
	result.m[3][3] = 1.0f;

	return result;
}

Matrix4x4 Matrix4x4::CreateRotateMatrix(const Quaternion& q) {
	return {
		(q.w*q.w) + (q.x*q.x) - (q.y*q.y) - (q.z*q.z),
		2.0f * (q.x*q.y + q.w*q.z),
		2.0f * (q.x*q.z - q.w*q.y),
		0.0f,
		2.0f * (q.x*q.y - q.w*q.z),
		(q.w*q.w) - (q.x*q.x) + (q.y*q.y) - (q.z*q.z),
		2.0f * (q.y*q.z + q.w*q.x),
		0.0f,
		2.0f * (q.x*q.z + q.w*q.y),
		2.0f * (q.y*q.z - q.w*q.x),
		(q.w*q.w) - (q.x*q.x) - (q.y*q.y) + (q.z*q.z),
		0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
}

// 単位行列作成
Matrix4x4 Matrix4x4::CreateIdentity4x4() {
	Matrix4x4 result{};
	for (int i = 0; i < 4; i++) {
		result.m[i][i] = 1;
	}
	return result;
}

// 座標変換
Vector3 Matrix4x4::TransformCoord(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

Matrix4x4 Matrix4x4::CreateRotateAxisAngle(const Vector3& axis, float radian) {
	// 拡大縮小
	Matrix4x4 s{};
	s.m[0][0] = std::cos(radian);
	s.m[1][1] = std::cos(radian);
	s.m[2][2] = std::cos(radian);

	// ベクトル射影
	Matrix4x4 p{};
	p.m[0][0] = axis.x * axis.x;
	p.m[0][1] = axis.x * axis.y;
	p.m[0][2] = axis.x * axis.z;
	p.m[1][0] = axis.y * axis.x;
	p.m[1][1] = axis.y * axis.y;
	p.m[1][2] = axis.y * axis.z;
	p.m[2][0] = axis.z * axis.x;
	p.m[2][1] = axis.z * axis.y;
	p.m[2][2] = axis.z * axis.z;
	p = (1.0f - std::cos(radian)) * p;

	// クロス積
	Matrix4x4 c{};
	c.m[0][1] = -axis.z;
	c.m[0][2] = axis.y;
	c.m[1][0] = axis.z;
	c.m[1][2] = -axis.x;
	c.m[2][0] = -axis.y;
	c.m[2][1] = axis.x;
	c = (-1 * std::sin(radian)) * c;


	// 結果
	Matrix4x4 result = s + p + c;
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 Matrix4x4::DirectionToDirection(const Vector3& from, const Vector3& to) {
	float c = Vector3::Dot(from, to);
	float s = Vector3::Cross(from, to).Length();
	Vector3 n = Vector3::Cross(from, to).Normalize();
	n = c == -1.0f ? Vector3{ from.y, -from.x, 0.0f } : n;

	Matrix4x4 result{};
	result.m[0][0] = (n.x * n.x) * (1.0f - c) + c;
	result.m[0][1] = (n.x * n.y) * (1.0f - c) + n.z * s;
	result.m[0][2] = (n.x * n.z) * (1.0f - c) - n.y * s;
	
	result.m[1][0] = (n.y * n.x) * (1.0f - c) - n.z * s;
	result.m[1][1] = (n.y * n.y) * (1.0f - c) + c;
	result.m[1][2] = (n.y * n.z) * (1.0f - c) + n.x * s;
	
	result.m[2][0] = (n.z * n.x) * (1.0f - c) + n.y * s;
	result.m[2][1] = (n.z * n.y) * (1.0f - c) - n.x * s;
	result.m[2][2] = (n.z * n.z) * (1.0f - c) + c;

	result.m[3][3] = 1.0f;
	
	return result;
}