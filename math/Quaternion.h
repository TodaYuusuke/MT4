#pragma once

/// <summary>
/// クォータニオン
/// </summary>
namespace LWP::Math {
	class Vector3;

	class Quaternion final {
	public:
		float x;
		float y;
		float z;
		float w;

	public:	// *** オペーレーターオーバーロード *** //

		// Quaternion Add(+) Quaternion
		Quaternion operator+(const Quaternion& other) const;
		Quaternion& operator+=(const Quaternion& other);

		// Quaternion Multiply(*) float
		Quaternion operator*(const float& other) const;
		Quaternion& operator*=(const float& other);
		friend Quaternion operator*(float scalar, const Quaternion& vec) { return vec * scalar; }

	public: // ** パブリックなメンバ関数 ** //

		// XYZをVector3のように扱う
		Vector3& xyz();
		const Vector3& xyz() const;
		
		/// <summary>
		/// 共役クォータニオンを返す
		/// </summary>
		Quaternion Conjugate() const;

		/// <summary>
		/// クォータニオンのNormを返す
		/// </summary>
		float Norm() const;

		/// <summary>
		/// 正規化したクォータニオンを返す
		/// </summary>
		Quaternion Normalize() const;

		/// <summary>
		/// 逆クォータニオンを返す
		/// </summary>
		Quaternion Inverse() const;


		/// <summary>
		/// 値を画面に表示
		/// </summary>
		void DrawDisplay(const char* label, int posX, int posY);


	public: // ** 生成系関数 ** //

		/// <summary>
		/// 単位クォータニオンを返す
		/// </summary>
		static Quaternion Identity();

		/// <summary>
		/// 内積を求める
		/// </summary>
		/// <param name="q1">... クォータニオン1</param>
		/// <param name="q2">... クォータニオン2</param>
		/// <returns>内積</returns>
		static float Dot(const Quaternion& q1, const Quaternion& q2);

		/// <summary>
		/// 任意軸回転を表すクォータニオンを生成して返す
		/// </summary>
		static Quaternion CreateRotateAxisAngleQuaternion(const Vector3& axis, float angle);

		/// <summary>
		///	球面線形補間
		/// </summary>
		/// <param name="q1"></param>
		/// <param name="q2"></param>
		/// <param name="t"></param>
		/// <returns></returns>
		static Quaternion Slerp(Quaternion q1, Quaternion q2, float t);

	public: // *** オペーレーターオーバーロード *** //

		// Quaternion Subtract(*) Quaternion
		Quaternion operator*(const Quaternion& other) const;
		Quaternion& operator*=(const Quaternion& other);
		
	};
}