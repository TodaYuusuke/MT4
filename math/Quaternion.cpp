#include "Quaternion.h"
#include "vector/Vector3.h"
#include <string>
#include <format>
#include <Novice.h>

using namespace LWP::Math;

Quaternion Quaternion::operator+(const Quaternion& other) const {
	return { x + other.x, y + other.y, z + other.z, w + other.w };
}
Quaternion& Quaternion::operator+=(const Quaternion& other) {
	return *this = *this + other;
}
Quaternion Quaternion::operator*(const float& other) const {
	return { x * other, y * other, z * other, w * other };
}
Quaternion& Quaternion::operator*=(const float& other) {
	return *this = *this * other;
}

Vector3& Quaternion::xyz() { return *reinterpret_cast<Vector3*>(&x); }
const Vector3& Quaternion::xyz() const { return *reinterpret_cast<const Vector3*>(&x); }


Quaternion Quaternion::Conjugate() const {
	return { -x,-y,-z,w };
}

float Quaternion::Norm() const {
	return std::sqrtf(x * x + y * y + z * z + w * w);
}

Quaternion Quaternion::Normalize() const {
	float norm = Norm();
	return { x / norm,y / norm,z / norm,w / norm };
}

Quaternion Quaternion::Inverse() const {
	Quaternion q = Conjugate();
	float norm = Norm() * Norm();
	return { q.x / norm,q.y / norm,q.z / norm,q.w / norm };
}

void Quaternion::DrawDisplay(const char* label, int posX, int posY) {
	std::string str = "%6.2f, %6.2f, %6.2f, %6.2f  :" + static_cast<std::string>(label);
	Novice::ScreenPrintf(posX, posY, str.c_str(), x, y, z, w);
}

Quaternion Quaternion::operator*(const Quaternion& other) const {
	Quaternion result;
	result.xyz() = Vector3::Cross(xyz(), other.xyz()) + (xyz() * other.w) + (other.xyz() * w);
	result.w = w * other.w - Vector3::Dot(xyz(), other.xyz());
	return result;
}
Quaternion& Quaternion::operator*=(const Quaternion& other) {
	return *this = *this * other;
}

Quaternion Quaternion::Identity() {
	return { 0.0f,0.0f,0.0f,1.0f };
}

float Quaternion::Dot(const Quaternion& q1, const Quaternion& q2) {
	return (q1.x * q2.x) + (q1.y * q2.y) + (q1.z * q2.z);
}


Quaternion Quaternion::CreateRotateAxisAngleQuaternion(const Vector3& axis, float angle) {
	Quaternion result{};
	result.w = std::cos(angle / 2.0f);
	result.xyz() = std::sin(angle / 2.0f) * axis;
	return result;
}

Quaternion Quaternion::Slerp(Quaternion q1, Quaternion q2, float t) {
	// 内積を求める
	float dot = Dot(q1, q2);
	if (dot < 0) {
		q1 = q1 * -1.0f;
		dot = -dot;
	}

	// なす角を求める
	float theta = std::acos(dot);

	// thetaを使って補間係数scale1とscale2を求める
	float scale1 = std::sin((1.0f - t) * theta) / std::sin(theta);
	float scale2 = std::sin(t * theta) / std::sin(theta);
	
	// それぞれの補間係数を利用して補間後のクォータニオンを求める
	return scale1 * q1 + scale2 * q2;
}
