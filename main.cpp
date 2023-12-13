#include <Novice.h>
#include <math/Math.h>

const char kWindowTitle[] = "LE2B_14_トダユウスケ";

using namespace LWP::Math;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ** 変数宣言 ** //
	Quaternion rotation = Quaternion::CreateRotateAxisAngleQuaternion(
		Vector3{1.0f,0.4f,-0.2f}.Normalize(), 0.45f);
	Vector3 pointY = { 2.1f,-0.9f,1.3f };
	Matrix4x4 rotateMatrix = Matrix4x4::CreateRotateMatrix(rotation);
	Vector3 rotateByQuaternion = pointY.Rotate(rotation);
	Vector3 rotateByMatrix = pointY * rotateMatrix;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// 描画
		rotation.DrawDisplay("rotation", 0, 0);
		rotateMatrix.DrawDisplay("rotateMatrix", 0, 20);
		rotateByQuaternion.DrawDisplay("rotateByQuaternion", 0, 120);
		rotateByMatrix.DrawDisplay("rotateByMatrix", 0, 140);


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
