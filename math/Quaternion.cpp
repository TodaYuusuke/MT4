#include "Quaternion.h"
#include "vector/Vector3.h"
#include <string>
#include <format>
#include <Novice.h>

using namespace LWP::Math;

Vector3& Quaternion::xyz() { return *reinterpret_cast<Vector3*>(&x); }
const Vector3& Quaternion::xyz() const { return *reinterpret_cast<const Vector3*>(&x); }


Quaternion Quaternion::Conjugate() {
    return { -x,-y,-z,w };
}

float Quaternion::Norm() {
    return std::sqrtf(x*x + y*y + z*z + w*w);
}

Quaternion Quaternion::Normalize() {
    float norm = Norm();
    return { x / norm,y / norm,z / norm,w / norm };
}

Quaternion Quaternion::Inverse() {
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