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
		/// 任意軸回転を表すクォータニオンを生成して返す
		/// </summary>
		static Quaternion CreateRotateAxisAngleQuaternion(const Vector3& axis, float angle);


	public: // *** オペーレーターオーバーロード *** //

		// Quaternion Subtract(*) Quaternion
		Quaternion operator*(const Quaternion& other) const;
		Quaternion& operator*=(const Quaternion& other);
		
	};
}