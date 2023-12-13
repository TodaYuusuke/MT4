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
		Quaternion Conjugate();

		/// <summary>
		/// クォータニオンのNormを返す
		/// </summary>
		float Norm();

		/// <summary>
		/// 正規化したクォータニオンを返す
		/// </summary>
		Quaternion Normalize();

		/// <summary>
		/// 逆クォータニオンを返す
		/// </summary>
		Quaternion Inverse();


		/// <summary>
		/// 値を画面に表示
		/// </summary>
		void DrawDisplay(const char* label, int posX, int posY);


	public: // ** 生成系関数 ** //

		/// <summary>
		/// 単位クォータニオンを返す
		/// </summary>
		static Quaternion Identity();

	public: // *** オペーレーターオーバーロード *** //

		// Quaternion Subtract(*) Quaternion
		Quaternion operator*(const Quaternion& other) const;
		Quaternion& operator*=(const Quaternion& other);
		
	};
}