#include "Quaternion.h"
#include "vector/Vector3.h"
#include <string>
#include <format>
#include <Novice.h>

using namespace LWP::Math;

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

Quaternion Quaternion::CreateRotateAxisAngleQuaternion(const Vector3& axis, float angle) {
	Quaternion result{};
	result.w = std::cos(angle / 2.0f);
	result.xyz() = std::sin(angle / 2.0f) * axis;
	return result;
}
